#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

#define Port_Ctrl       (0xFF13)                /*  8255A Control Port  */
#define Port_A          (0xFF10)                /*  8255A Port A        */
#define Port_B          (0xFF11)                /*  8255A Port B        */
#define Port_C          (0xFF12)                /*  8255A Port C        */


int buffer[16];
void getfont(int code);

main()
{
    int  i, j, k, len, flag = 1;
    char *string = "　歡迎光臨資訊科微控實驗室　\0";
    int  *ptr = (int *) string;
    char *c_ptr, *b_ptr;

    outportb(Port_Ctrl, 0x80);
    len = strlen(string);

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

    while (! kbhit()) {
        for (i = 0; i < len * 8 - 14; i++) {
            for (j = 1; j < 10; j++) {
                for (k = 0; k < 14; k++) {
                     outportb(Port_A, 14);
                     outportb(Port_B, flag>0 ? *(b_ptr+i+k) : ~*(b_ptr+i+k));
                     outportb(Port_C, flag>0 ? *(c_ptr+i+k) : ~*(c_ptr+i+k));
                     outportb(Port_A, k);
                     delay(1);
                }
            }
            if (kbhit()) break;
        }
        flag = -flag;
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