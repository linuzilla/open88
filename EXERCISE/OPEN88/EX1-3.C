/*
   ���������� ���Ω� �ڢӢ� �ʺA�i�ܪ��򥻹���

   �@�B����ت�
       ���� 8255A �u�@�Ҧ��A����o���G���� L1 ~ L24 �G�t���A

   �G�B�������

*/


#include <stdio.h>
#include <dos.h>

#define Port_Ctrl       (0xFF13)                /*  8255A Control Port  */
#define Port_A          (0xFF10)                /*  8255A Port A        */
#define Port_B          (0xFF11)                /*  8255A Port B        */
#define Port_C          (0xFF12)                /*  8255A Port C        */

#define Duration        (500)


char  pattern[] = {
             0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
             0x7D, 0x27, 0x7F, 0x6F, 0x90, 0x90
                  };


main()
{
    int    i;

    for (i = 0; i < 256; i++) {
        outportb(Port_Ctrl, 0x80);
        outportb(Port_B, i);
        delay(Duration);
    }

    return 0;
}
