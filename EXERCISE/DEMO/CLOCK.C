#include <stdio.h>
#include <conio.h>
#include <dos.h>

#define Port_Ctrl       (0xFF13)                /*  8255A Control Port  */
#define Port_A          (0xFF10)                /*  8255A Port A        */
#define Port_B          (0xFF11)                /*  8255A Port B        */
#define Port_C          (0xFF12)                /*  8255A Port C        */

main()
{
    struct time  timep;


    outportb(Port_Ctrl, 0x80);

    while(! kbhit()) {
        gettime(&timep);

        outportb(Port_A, ((timep.ti_hour / 10) * 16) + timep.ti_hour % 10);
        outportb(Port_B, ((timep.ti_min  / 10) * 16) + timep.ti_min  % 10);
        outportb(Port_C, ((timep.ti_sec  / 10) * 16) + timep.ti_sec  % 10);
    }

    return 0;
}
