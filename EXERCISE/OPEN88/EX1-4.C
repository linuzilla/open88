/*
   ���������� ���Ω� �ڢӢ� �ʺA�i�ܪ��򥻹���

   �@�B����ت�
       ���� 8255A �u�@�Ҧ��A����o���G���� L1 ~ L24 �G�t���A

   �G�B�������

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