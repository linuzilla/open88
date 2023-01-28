/*
   ８２５５Ａ 應用於 ＬＥＤ 動態展示的基本實驗

   一、實驗目的
       應用 8255A 工作模式，控制發光二極體 L1 ~ L24 亮暗狀態

   二、實驗條件

*/


#include <stdio.h>
#include <dos.h>

#define Port_Ctrl       (0xFF13)                /*  8255A Control Port  */
#define Port_A          (0xFF10)                /*  8255A Port A        */
#define Port_B          (0xFF11)                /*  8255A Port B        */
#define Port_C          (0xFF12)                /*  8255A Port C        */

#define Duration        (200)

main()
{
    int    i;
    long   pattern;

    for (pattern = 1L, i = 0; i < 24; i++) {
        outportb(Port_Ctrl, 0x80);
        outportb(Port_A,    pattern & 0xFF);
        outportb(Port_B,    (pattern >>  8) & 0xFF);
        outportb(Port_C,    (pattern >> 16) & 0xFF);
        delay(Duration);
        pattern <<= 1;
    }

    for (pattern = 1L, i = 0; i < 24; i++) {
        outportb(Port_Ctrl, 0x80);
        outportb(Port_A,    pattern & 0xFF);
        outportb(Port_B,    (pattern >>  8) & 0xFF);
        outportb(Port_C,    (pattern >> 16) & 0xFF);
        delay(Duration);
        pattern <<= 1;
        pattern++;
    }

    for (pattern >>= 1, i = 0; i < 24; i++) {
        pattern >>= 1;
        outportb(Port_Ctrl, 0x80);
        outportb(Port_A,    pattern & 0xFF);
        outportb(Port_B,    (pattern >>  8) & 0xFF);
        outportb(Port_C,    (pattern >> 16) & 0xFF);
        delay(Duration);
    }

    return 0;
}
