#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define Port_Ctrl       (0xFF13)        /*  8255A Control Port  */
#define Port_A          (0xFF10)        /*  8255A Port A        */
#define Port_B          (0xFF11)        /*  8255A Port B        */
#define Port_C          (0xFF12)        /*  8255A Port C        */

#define Duration        (300)

main()
{
    int  i;
    long pattern;

    outportb(Port_Ctrl, 0x80);

    while (! kbhit()) {
        for (i = 0; i < 5; i++) {
            outportb(Port_A, 0);
            outportb(Port_B, 0);
            outportb(Port_C, 0);
            delay(Duration);
            outportb(Port_A, 0xFF);
            outportb(Port_B, 0xFF);
            outportb(Port_C, 0xFF);
            delay(Duration);
        }

        for (i = 1; i <= 256; i <<= 1) {
            outportb(Port_A,  i);
            outportb(Port_B,  i);
            outportb(Port_C,  i);
            delay(Duration);
        }

        for (i = 1; i <= 256; i <<= 1, i++) {
            outportb(Port_A,  i);
            outportb(Port_B,  i);
            outportb(Port_C,  i);
            delay(Duration);
        }

        for (i = 1; i <= 256; i <<= 1, i++) {
            outportb(Port_A,  0xFF & ~i);
            outportb(Port_B,  0xFF & ~i);
            outportb(Port_C,  0xFF & ~i);
            delay(Duration);
        }

        for (pattern = 1L, i = 0; i < 24; i++) {
            outportb(Port_A,    pattern & 0xFF);
            outportb(Port_B,    (pattern >>  8) & 0xFF);
            outportb(Port_C,    (pattern >> 16) & 0xFF);
            delay(Duration / 2);
            pattern <<= 1;
        }

        for (pattern >>= 1, i = 0; i < 24; i++) {
            pattern >>= 1;
            outportb(Port_A,    pattern & 0xFF);
            outportb(Port_B,    (pattern >>  8) & 0xFF);
            outportb(Port_C,    (pattern >> 16) & 0xFF);
            delay(Duration / 2);
        }

        for (pattern = 1L, i = 0; i < 24; i++) {
            outportb(Port_A,    pattern & 0xFF);
            outportb(Port_B,    (pattern >>  8) & 0xFF);
            outportb(Port_C,    (pattern >> 16) & 0xFF);
            delay(Duration / 2);
            pattern <<= 1;
            if (i % 2) pattern++;
        }

        for (pattern &= 0xFF ,i = 1; i < 20; i++) {
            outportb(Port_A, pattern);
            outportb(Port_B, pattern);
            outportb(Port_C, pattern);
            delay(Duration / 2);
            outportb(Port_A, pattern << 1);
            outportb(Port_B, pattern << 1);
            outportb(Port_C, pattern << 1);
            delay(Duration / 2);
        }

        for (i = 1; i < 20; i++) {
            outportb(Port_A, pattern);
            outportb(Port_B, pattern << 1);
            outportb(Port_C, pattern);
            delay(Duration / 2);
            outportb(Port_A, pattern << 1);
            outportb(Port_B, pattern);
            outportb(Port_C, pattern << 1);
            delay(Duration / 2);
        }
    }

    return 0;
}
