/*
   ８２５５Ａ 應用於 ＬＥＤ 動態展示的基本實驗

   一、實驗目的
       應用 8255A 工作模式，控制發光二極體 L1 ~ L24 亮暗狀態

   二、實驗條件

*/


#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define Port_Ctrl       (0xFF13)                /*  8255A Control Port  */
#define Port_A          (0xFF10)                /*  8255A Port A        */
#define Port_B          (0xFF11)                /*  8255A Port B        */
#define Port_C          (0xFF12)                /*  8255A Port C        */

main()
{
    do {
        outportb(Port_Ctrl, 0x80);
        outportb(Port_A,    0x0F);  delay(500);
        outportb(Port_B,    0xF0);  delay(500);
        outportb(Port_C,    0x0F);  delay(500);

        outportb(Port_Ctrl, 0x80);
        outportb(Port_C,    0xF0);  delay(500);
        outportb(Port_B,    0x0F);  delay(500);
        outportb(Port_A,    0xF0);  delay(500);
    } while (! kbhit());

    return 0;
}
