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