/*
   ８２５５Ａ 應用於 ＬＥＤ 動態展示的基本實驗

   一、實驗目的
       應用 8255A 工作模式，控制發光二極體 L1 ~ L24 亮暗狀態

   二、實驗條件

*/


#include <stdio.h>
#include <dos.h>
#include <conio.h>

#define Port_Ctrl       (0xFF13)                /*  8255A Control Port  */
#define Port_A          (0xFF10)                /*  8255A Port A        */
#define Port_B          (0xFF11)                /*  8255A Port B        */
#define Port_C          (0xFF12)                /*  8255A Port C        */

#define Duration        (20)

main()
{
    int    i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < 256; i++) {
            outportb(Port_Ctrl, 0x80);
            outportb(Port_A, i);
            outportb(Port_B, j);
            outportb(Port_C, j);
            delay(Duration);

            if (kbhit())
                return 1;
        }
    }

    return 0;
}
