/*[]  asm.c    --  February 23, written by  Jiann-Ching Liu          []*/

/* Open 88 LED module simulation assembler */


#include <stdio.h>
#include <io.h>
#include <dos.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>
#include <sys/stat.h>


//   #define DEBUG

#define STDINnum        (0)
#define STDOUTnum       (1)
#define LIBFILE         "_SIMU.LIB"

#ifdef __TURBOC__
#   include <dir.h>
#else
#   define MAXPATH             (80)
#   define MAXDRIVE            (3)
#   define MAXDIR              (66)
#   define MAXFILE             (9)
#   define MAXEXT              (5)
#ifdef __ZTC__
#   define findfirst(x,y,z)    _dos_findfirst(x,y,z)
#   define findnext(x)         _dos_findnext(x)
#endif
#ifdef __WATCOMC__
#   define findfirst(x,y,z)    _dos_findfirst(x,z,y)
#   define findnext(x)         _dos_findnext(x)
#endif
#endif

typedef struct _FileLink {
        char *name;
        struct _FileLink *next;
        } FileLink;

struct lineDiff {
    int    line;
    int    diff;
    struct lineDiff *next;
} *lined_head, *lined_tail;



int convert(char *, char *, int option);
int assemble(char *, char *, char *, char *);
int linking(char *, char *, char *);
int get_token(const char *string, char *target);

int verbose = 0, asmerrmsg = 0;

main(int argc, char *argv[])
{
    char            filename[MAXPATH], drive[MAXDRIVE], directory[MAXDIR];
    char            fname[MAXFILE], ext[MAXEXT];
#ifdef __TURBOC__
    struct ffblk    ff;
#else
    struct find_t   ff;
#endif
    FileLink        *root, *ptr, *n;
    int             done;
    char            asmtmp[13], objtmp[13];
    char            *assembler[] = { "masm.exe", "tasm.exe"  };
    char            *linker[]    = { "link.exe", "tlink.exe" };
    int             sel = 0, optionSection = 1, fcounter = 0;
    int             aecount = 0, lecount = 0, option = 0;

    printf("\niAPX 286/386 Assembler 0.03  (á-release) (c) 1995, written by  Jiann-Ching Liu.\n\n");

    if (argc == 1) {
        printf("Syntax is: asm [ options ] file[.asm] ...\t\t(*%s*)\n", __DATE__);
        printf("  -a   Alternate assembler and linker\n");
        printf("  -v   Verbose assembling\n");
        printf("  -s   Enable PC speaker emulation\n");
        printf("  -p   Patch 7's segment (A to F)\n");
        printf("  -e   error messages display\n");
        return 1;
    }

    for (argc--, argv++; argc; argc--, argv++) {
        if ((*argv)[0] == '-' && optionSection) {
            int  i = 0;
            while((*argv)[++i] != '\0') {
                switch((*argv)[i]) {
                case 'A':
                case 'a':
                    sel = 1;
                    break;
                case 'v':
                    verbose = 1;
                    break;
                case 's': /*   Speaker enable    : 0000 0001  */
                    option |= 0x01;
                    break;
                case 'p': /*   Patch 7's segment : 0000 0010  */
                    option |= 0x02;
                    break;
                case 'e': /*   disable detial error messages */
                    asmerrmsg = 1;
                    break;
                default :
                    printf("Fatal: unknow option %s\n", *argv);
                    return 1;
                }
            }
        } else {
            optionSection = 0;
            fnsplit(*argv, drive, directory, fname, ext);
            if (ext[0] == '\0')
                strcpy(ext, ".asm");
            fnmerge(filename, drive, directory, fname, ext);

            if ((done = findfirst(filename, &ff, 0)) != 0) {
                printf("No match \'%s\'\n", filename);
            }
            ptr = root = (FileLink *) malloc(sizeof(FileLink));

            while (! done) {
                n = (FileLink *) malloc(sizeof(FileLink));

#ifdef __TURBOC__
                n->name = (char *) malloc(strlen(ff.ff_name) +
                                 strlen(drive)+strlen(directory)+5);
                fnmerge(n->name, drive, directory, ff.ff_name, "");
#else
                n->name = (char *) malloc(strlen(ff.name) +
                                 strlen(drive)+strlen(directory)+5);
                fnmerge(n->name, drive, directory, ff.name, "");
#endif
                ptr = (ptr->next = n);
                done = findnext(&ff);
            }

            ptr->next = NULL;
            ptr = root->next;
            free(root);

            while (ptr) {
                tmpnam(asmtmp);
                fcounter++;
                if (convert(ptr->name, asmtmp, option)) {
                    tmpnam(objtmp);

                    if (! verbose)
                        printf("file: %s, *** Assembling ...", ptr->name);
                    else
                        printf("file: %s\n", ptr->name);
                    if (assemble(assembler[sel], asmtmp, objtmp, ptr->name) == 0) {

                        if (! verbose)
                            printf("\rfile: %s, *** Linking ......", ptr->name);
                        if (linking(linker[sel], objtmp, ptr->name) == 0) {
                            if (! verbose)
                                printf("\rfile: %s, *** End of assembly ***\n", ptr->name);
                        } else {
                            lecount++;
                            if (! verbose)
                                printf("error!%c\n", 7);
                        }
                        remove(objtmp);
                    } else {
                        aecount++;
                        if (! verbose && ! asmerrmsg)
                            printf("error!%c\n", 7);
                    }
#ifndef  DEBUG
                    remove(asmtmp);
#endif
                }
                if (asmerrmsg) {
//                 printf("\n\n");
                   while (lined_head != NULL) {
//                     printf("%3d %3d\n", lined_head->line, lined_head->diff);
                       lined_tail = lined_head->next;
                       free(lined_head);
                       lined_head = lined_tail;
                   }
                }

                n = ptr->next;
                free((void*) ptr->name);
                free(ptr);
                ptr = n;
            }
        }
    }
    if (fcounter)
        printf("\nFiles assembled: %d   Assemble errors: %d   Link errors:  %d\n", fcounter, aecount, lecount);
    return 0;
}

int assemble(char *asmlr, char *asmfile, char *objfile, char *orgfile)
{
    int    r;
#ifndef DEBUG
    FILE   *fp;
    int    fd;
    int    save_stdout, new_stdout;
    char   tmpfile[13];


    if (! verbose) {
        if (asmerrmsg)
            tmpnam(tmpfile);
        save_stdout = dup(STDOUTnum);
        if (asmerrmsg) {
            if ((fd = open(tmpfile, O_CREAT|O_TRUNC|O_RDWR|O_BINARY, S_IWRITE|S_IREAD)) == -1) {
                 fprintf(stderr, "\n");
                 perror(tmpfile);
                 return -1;
            }
        } else {
            if ((fd = open("NUL", O_RDWR|O_BINARY)) == -1) {
                 fprintf(stderr, "\n");
                 perror("NULL device");
                 return -1;
            }
        }

        close(STDOUTnum);
        new_stdout = dup(fd);
    }
#endif

    if ((r=spawnlp(P_WAIT, asmlr, asmlr, "/mx", asmfile, ",", objfile, ";", NULL))==-1) {
        fprintf(stderr, "\n");
        perror(asmlr);
    }
#ifndef DEBUG
    if (! verbose) {
        close(new_stdout);
        dup(save_stdout);
        close(save_stdout);
        close(fd);
        if (asmerrmsg) {
            if (r != 0) {
                if ((fp = fopen(tmpfile, "r")) == NULL) {
                     printf("\nerror: cannot open input file %s\n\n", tmpfile);
                } else {
                     char *ptr, fmt[10], fmt2[10], buffer[512];
                     int  line= 0, i, j;
                     struct lineDiff  *lptr = lined_head;

                     printf("error!%c\n\n", 7);
                     while (fgets(buffer, 512, fp) != NULL) {
                         if (line++ > 2) {
                             if ((ptr = strchr(buffer, '(')) != NULL) {
                                 i = j = 0;
                                 while (ptr[i+1] != ')') {
                                     j = j * 10 + (ptr[++i] - '0');
                                 }
                                 sprintf(fmt, "(%c%dd", '%', i);
                                 while (lptr->line < j && lptr != NULL) {
                                     lptr=lptr->next;
                                 }
                                 j = j - lptr->diff;
                                 sprintf(fmt2, fmt, j);
                                 memcpy(ptr, fmt2, strlen(fmt2));
                                 printf("%s %s", orgfile, ptr);
                             } else {
                                 break;
                             }
                         }
                     }
                     fclose(fp);
                     printf("\n");
                }
            }
            remove(tmpfile);
        }
    }
#endif

    return r;
}

int linking(char *lnk, char *objfile, char *srcfile)
{
    int    r;
    char   exefile[MAXPATH], drive[MAXDRIVE], directory[MAXDIR];
    char   fname[MAXFILE], ext[MAXEXT];
#ifndef DEBUG
    int    fd;
    int    save_stdout, new_stdout;
#endif

    fnsplit(srcfile, drive, directory, fname, ext);
    strcpy(ext, ".exe");
    fnmerge(exefile, drive, directory, fname, ext);

#ifndef DEBUG
    if (! verbose) {
        save_stdout = dup(STDOUTnum);
        if ((fd = open("NUL", O_RDWR|O_BINARY)) == -1) {
             fprintf(stderr, "\n");
             perror("NULL device");
             return -1;
        }
        close(STDOUTnum);
        new_stdout = dup(fd);
    }
#endif

//  if ((r=spawnlp(P_WAIT, lnk, lnk, "/batch", "/noi", objfile, ",", exefile, ";", NULL))==-1) {
    if ((r=spawnlp(P_WAIT, lnk, lnk, "/batch", objfile, ",", exefile, ";", NULL))==-1) {
        fprintf(stderr, "\n");
        perror(lnk);
    }
#ifndef DEBUG
    if (! verbose) {
        close(new_stdout);
        dup(save_stdout);
        close(save_stdout);
        close(fd);
    }
#endif

    return r;
}

int convert(char *fname, char *newname, int option)
{
    FILE    *fp, *out;
    int     i, j, found;
    char    buffer[512];
    char    token[256];
    char    *match[4] = {"out", "dx", ",", "al" };
    int     line;

    if ((fp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "\nerror: cannot open input file %s\n\n", fname);
        return 0;
    }

    if ((out = fopen(newname, "w")) == NULL) {
        fprintf(stderr, "\nerror: cannot create output file\n\n");
        return 0;
    }

    if (asmerrmsg) {
        struct lineDiff *ptr = malloc(sizeof(struct lineDiff));
        lined_head = lined_tail = ptr;
        ptr->line = 4;
        ptr->diff = 3;
        ptr->next = NULL;
    }
    fprintf(out, "\t\t.286\n");
    fprintf(out, "\t\tINCLUDELIB\t%s\n", LIBFILE);
    fprintf(out, "\t\tEXTRN\t_$outdxal$: NEAR\n");
    line = 3;

//  printf("\nFile: %s\n", fname);
    while (fgets(buffer, 512, fp) != NULL) {
         char *label = NULL;
         j = 0;
         if (buffer[0] != ' ' && buffer[0] != '\t') {
             get_token(buffer, token);
             label = strdup(token);
             j = strlen(token);
         }

         if (buffer[0] != ';') {
             for (found = 1, i = 0; i < 4; i++) {
                 j += get_token(&buffer[j], token);
                 j += strlen(token);
                 if (stricmp(token, match[i]) != 0) {
                     found = 0;
                     break;
                 }
             }
             if (found) {
                 int dif = 0, xline = 0;
                 fprintf(out, ";%s", buffer);

/*
 *               fprintf(out, "\t\tpush\tbp\n"          // push bp
 *                            "\t\tmov\tbp,sp\n"        // mov  bp, sp
 *                            "\t\tpush\tax\n"          // push ax
 *                            "\t\tmov\tax,%d\n"        // mov  ax, option
 *                            "\t\txchg\tax,[bp][-2]\n" // xchg ax, [bp][-2]
 *                            "\t\tmov\tbp,[bp]\n"      // mov  bp, [bp]
 *                            , option);
 */
                 fprintf(out, "\t\tpush\t%d\n", option);

                 if (label != NULL) {
                     fprintf(out, "%s:\n", label);
                     dif++;
                     xline++;
                 }
                 fprintf(out, "\t\tcall\t_$outdxal$\n"); /* call _$outdxal$  */

                 fprintf(out, "\t\tadd\tsp, 2\n");
/*
 *               fprintf(out, "\t\tpop\tbp\n"                // pop bp
 *                            "\t\tpop\tbp\n");              // pop bp
 */
//               dif += 9;
                 dif += 3;
                 xline += 4;

                 if (asmerrmsg) {
                     struct lineDiff *ptr = malloc(sizeof(struct lineDiff));
                     lined_tail->line = line;
                     line += xline;
                     ptr->line = line;
                     ptr->diff = lined_tail->diff + dif;
                     lined_tail = (lined_tail->next = ptr);
                     ptr->next = NULL;
                 }
             } else {
                 fprintf(out, "%s", buffer);
                 line++;
             }
         } else {
             fprintf(out, ";\n");
             line++;
         }
         if (label != NULL)
             free(label);
    }
    if (asmerrmsg)
        lined_tail->line = line;

    fclose(fp);
    fclose(out);
    return 1;
}

int get_token(const char *string, char *target)
{
    static char delim[] = "\t\n\r ~`!@#$%^&*()-+=/<>\"\'\\;:,.";
    static char token_del[] = ",;";
    int   fn = -1, idx = 0, i, j, found;


    for (i = 0; i < strlen(string); i++) {
        for (j = found = 0; j < strlen(delim); j++) {
            if (string[i] == delim[j]) {
                found = 1;
                break;
            }
        }
        if (! found) {
            target[idx++] = string[i];
            if (fn == -1)
                fn = i;
        } else {
            if (fn != -1) {
                break;
            } else {
                if (strchr(token_del, string[i]) != NULL) {
                    fn = i;
                    target[idx++] = string[i];
                    break;
                }
            }
        }
    }
    target[idx] = '\0';
    return fn;
}
