#include <stdio.h>
#include <io.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int  etfont_init(char *path);
void etfont_close(void);
void getfont(unsigned char hb, unsigned char lb);

unsigned char buffer[24][3];

main(int argc, char *argv[])
{
    int   i, j, k;

    if (argc == 1) {
        printf("\nusage: getfont string...\n\n");
        return 1;
    }

    if (! etfont_init("c:/et3")) {
        printf("Can not initialize ET font system\n");
        return 1;
    }

    for (argc--, argv++; argc; argc--, argv++) {
        for (i = 0; i < strlen(*argv); i+=2) {
            printf("\n\t/* %c%c */ \n", *(*argv+i), *(*argv+i+1));
            getfont(*(*argv+i), *(*argv+i+1));
            for (j = 0; j < 24; j++) {
                for (k = 0; k < 3; k++) {
                    printf("0x%02x,", buffer[j][k]);
                }
                printf("\n");
            }
        }
    }

    etfont_close();
    return 0;
}


static unsigned char pat1[24][2], pat2[24][2];
static int           ffont24 = 0, hfont24 = 0;
static const char    *std24 = "/stdfont.24";
static const char    *asc24 = "/ascfont.24";

int etfont_init(char *path)
{
    char  *std, *asc;
    std = malloc(strlen(path) + strlen(std24) + 1);
    asc = malloc(strlen(path) + strlen(asc24) + 1);
    strcpy(std, path);
    strcpy(&std[strlen(path)], std24);
    strcpy(asc, path);
    strcpy(&asc[strlen(path)], asc24);
    ffont24 = open(std, O_RDONLY|O_BINARY);
    hfont24 = open(asc, O_RDONLY|O_BINARY);

    return (ffont24 != -1 && hfont24 != -1) ? 1 : 0;
}

void etfont_close(void)
{
    close(ffont24);
}

static int chcode(unsigned char hbp, unsigned char lbp)
{
    int   codep;
    int   lt, ht;

    lt = (int)(lbp);
    ht = (int)(hbp);

    if (ht < 129) {
        codep = ht;
    } else {
        if (ht < 164) {
            codep = 157 * (ht - 161) + lt - 64;
        } else {
            if (lt > 161)
                lt -= 34;

            codep = 157 * (ht - 164) + lt - 64;

            if (codep >= 5809)
               codep -= 408;
        }
    }
    return(codep);
}

static void ffont24get(unsigned char hbp, unsigned char lbp)
{
   lseek(ffont24, 72L * (long) (chcode(hbp, lbp)), SEEK_SET);
   read (ffont24, buffer, 72);
}

static void hfont24get(unsigned char hbp, unsigned char lbp)
{
   int  i;

   lseek(hfont24, 48L * (long) hbp, SEEK_SET);
   read (hfont24, pat1, 48);
   lseek(hfont24, 48L * (long) lbp, SEEK_SET);
   read (hfont24, pat2, 48);
   for (i = 0; i < 24; i++) {
       buffer[i][0] = pat1[i][0];
       buffer[i][1] = pat1[i][1] + (pat2[i][0] >> 4);
       buffer[i][2] = ((pat2[i][0] & 0x0F) << 4) + (pat2[i][1] >> 4);
   }
}

void getfont(unsigned char hb, unsigned char lb)
{
    if (hb > 127) {
        ffont24get(hb, lb);
    } else {
        hfont24get(hb, lb);
    }
}
