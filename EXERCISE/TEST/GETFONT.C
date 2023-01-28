#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>


int buffer[16];
void getfont(int code);

main(int argc, char *argv[])
{
    int  i, j, k, len;
    int  *ptr;
    unsigned char *c_ptr, *b_ptr;

    if (argc == 1) {
        printf("\nusage: getfont string...\n\n");
        return 1;
    }



    for (argc--, argv++; argc; argc--, argv++) {
        ptr = (int *) (*argv);
        len = strlen(*argv);
        if ((b_ptr = malloc(len * 8)) == NULL) {
            printf("memory allocation error!\n");
            exit(1);
        }
        if ((c_ptr = malloc(len * 8)) == NULL) {
            printf("memory allocation error!\n");
            exit(1);
        }

        for (i = k = 0; i < len; i += 2) {

            getfont(*ptr++);
            for (j = 0; j < 16; j++, k++) {
                c_ptr[k] = (char) (buffer[j] >> 8) & 0xFF;
                b_ptr[k] = (char) buffer[j] & 0xFF;
            }
        }

        for (i = 0; i < len/2; i++) {
            for (k = 0; k < 14; k++) {
                 printf("\t\tDB\t%3u, %3u\n", *(b_ptr+i*16+k), *(c_ptr+i*16+k));
            }
            printf("\n");
        }
    }
    return 0;



}

void getfont(int code)
{
    union  REGS   regs;
    struct SREGS  sregs;

    regs.x.ax = 0x9080;
    regs.x.dx = code;
    regs.x.bx = FP_OFF(buffer);
    sregs.ds  = FP_SEG(buffer);
    int86x(0x10, &regs, &regs, &sregs);
}
