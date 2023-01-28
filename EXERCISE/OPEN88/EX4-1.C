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

#define Duration        (500)

static const int numb[] = {  0, 1, 2, 4, 8, 16, 32, 64, 128 };

int analy(const int n)
{
     int   i, j, k = 0;


     for (i = 8, j = n; i > 0; i--) {
         if (numb[i] <= j) {
             j -= numb[i];
             k += i;
             printf("<%d, %d, %d, %d>", i, j, k, numb[i]);
         }
     }
     return k;
}

main()
{
    int   i, k;


    while(! kbhit()) {

        outportb(Port_Ctrl, 0x82);
        outportb(Port_A, k = inportb(Port_B));
        i = analy(k);
        outportb(Port_C, i / 10 * 16 + i % 10);
        printf("(%d, %d)\n", k, i);
        delay(Duration);

    }

    return 0;
}
