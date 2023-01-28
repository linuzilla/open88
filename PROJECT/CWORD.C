#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>

#define XX      (30)
#define YY      (70)

void getfont(int code, char *buffer);

main()
{
    int     gdriver = DETECT, gmode, errorcode;
    char    *str = "資料處理";
    char    pattern[24][3];
    int     *ptr = (int *) str;
    int     i, j, k, m, xx = XX, yy = YY, len, mask;


    initgraph(&gdriver, &gmode, "");
    if ((errorcode = graphresult()) != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        return 1;
    }

    len = strlen(str);
    for (m = 0; m < len; m += 2, xx += 50) {
        getfont(*ptr++, (char *) pattern);
        for (i = 0; i < 24; i++) {
            for (j = 0; j < 3; j++) {
                for (k = 0, mask = 0x80; k < 8; k++, mask >>= 1) {
                    putpixel(xx+j*8+k, yy+i, pattern[i][j] & mask ? 1 : 2);
                }
            }
        }
    }
    getch();

    closegraph();
    return 0;
}

void getfont(int code, char *buffer)
{
    union  REGS   regs;
    struct SREGS  sregs;

    regs.x.ax = 0x9000;
    regs.x.dx = code;
    regs.x.bx = FP_OFF(buffer);
    sregs.ds  = FP_SEG(buffer);
    int86x(0x10, &regs, &regs, &sregs);
}
