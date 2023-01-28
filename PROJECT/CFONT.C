#include <dos.h>
#include "cfont.h"

void getfont24(int code, char *buffer)
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