; ==================================================================== ;
;  ���㢳							       ;
;								       ;
;      ����G ���������� ���Ω� �ڢӢ� �ʺA�i�ܪ��򥻹���	       ;
;								       ;
;      �@�B����ت��G						       ;
;	 ���B���� 8255A �u�@�Ҧ��A����o���G���� ��1 �� ��8 �G�t���A   ;
;	 ���B�Q���޽r������O ror/rol ���� LED			       ;
;								       ;
;      �G�B�}�����A�G SW3: -234 				       ;
;								       ;
;      �T�B�������G �g�@�{������ LED �Ϩ�p�R�E�O��Ӧ^�]��	       ;
;								       ;
; ==================================================================== ;


Port_Ctrl	EQU	0FF13h		; 8255A Control Port
Port_A		EQU	0FF10h		; 8255A Port A
Port_B		EQU	0FF11h		; 8255A Port B
Port_C		EQU	0FF12h		; 8255A Port C

		.MODEL	SMALL
		.CODE
		mov	ax, @data
		mov	ds, ax

		mov	dx, Port_Ctrl
		mov	al, 80h
		out	dx, al		; �]�w 8255 �u�@�Ҧ�
		cld
		mov	dx, Port_A
repeat: 	lea	si, table
loop00: 	lodsb
		cmp	al, 0
		jz	repeat
		out	dx, al

		call	delay

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

delay:		push	cx		; �N cx �Ȧs�������e�O�s�b���|
		push	dx		; �N dx �Ȧs�������e�O�s�b���|

		mov	dx, 10
delay01:	mov	cx, 0FFFFh
		loop	$
		dec	dx
		jnz	delay01

		pop	dx		; �N dx �Ȧs�������e�q���|���^
		pop	cx		; �N cx �Ȧs�������e�q���|���^
		ret			; ��^�I�s�{��

		.DATA
Table		DB	00000001B
		DB	00000010B
		DB	00000100B
		DB	00001000B
		DB	00010000B
		DB	00100000B
		DB	01000000B
		DB	10000000B
		DB	01000000B
		DB	00100000B
		DB	00010000B
		DB	00001000B
		DB	00000100B
		DB	00000010B
		DB	0
		.STACK
		END
