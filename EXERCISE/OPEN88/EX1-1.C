/*
   ���������� ���Ω� �ڢӢ� �ʺA�i�ܪ��򥻹���

   �@�B����ت�
       ���� 8255A �u�@�Ҧ��A����o���G���� L1 ~ L24 �G�t���A

   �G�B�������

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