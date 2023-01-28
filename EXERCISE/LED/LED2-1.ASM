; ==================================================================== ;
;  ���㢰							       ;
;								       ;
;      ����G ���������� ���Ω� �ڢӢ� �ʺA�i�ܪ��򥻹���	       ;
;								       ;
;      �@�B����ت��G						       ;
;	   ���� 8255A �u�@�Ҧ��A����o���G���� ��1 �� ��24 �G�t���A    ;
;								       ;
;      �G�B�}�����A�G SW3: -234 				       ;
;								       ;
;      �T�B�������G �g�@�{������ LED �Ϩ���G���t���������L��      ;
;		      �U ESC ��ᰱ��				       ;
;								       ;
;		      ����������������		  ����������������     ;
;		      ����������������	���w�w��  ����������������     ;
;		      ����������������		  ����������������     ;
;								       ;
; ==================================================================== ;


Port_Ctrl	EQU	0FF13h		; 8255A Control Port
Port_A		EQU	0FF10h		; 8255A Port A
Port_B		EQU	0FF11h		; 8255A Port B
Port_C		EQU	0FF12h		; 8255A Port C

		.MODEL	SMALL
		.CODE
		mov	dx, Port_Ctrl
		mov	al, 80h
		out	dx, al		; �]�w 8255 �u�@�Ҧ��]�g�J�Ҧ��^

loop00:
		mov	al, 11111111b	; ���O�e (11111111)b �����
		mov	dx, Port_A	; �� Port_A, Port_B �� Port_C
		out	dx, al		; �ϱ���o�� Port �� LED �G�_��
		mov	dx, Port_B
		out	dx, al
		mov	dx, Port_C
		out	dx, al

		call	delay		; �I�s�ɶ����𪺰Ƶ{��

		mov	al, 00000000b	; ���O�e (00000000)b �����
		mov	dx, Port_A	; �� Port_A, Port_B �� Port_C
		out	dx, al		; �ϱ���o�� Port �� LED ���t
		mov	dx, Port_B
		out	dx, al
		mov	dx, Port_C
		out	dx, al

		call	delay		; �I�s�ɶ����𪺰Ƶ{��

		mov	ah, 1
		int	16h		; �ˬd��L���A
		jz	loop00		; �Y Z �X�� = 1, ����L�w�İϬO�Ū�

		mov	ah, 0
		int	16h		; Ū����L�w�İϸ��

		cmp	al, 27		;
		jnz	loop00		; �Y�ҫ����䤣�O ESC ��, �h���� loop00

		mov	ah, 4Ch
		int	21h		; �{������, ��^ DOS

;
;  �� �� �� �� �� �{ ��
;

delay:		mov	dx, 30
delay01:	mov	cx, 0FFFFh
		loop	$
		dec	dx
		jnz	delay01
		ret			; ��^�I�s�{��

		.STACK
		END
