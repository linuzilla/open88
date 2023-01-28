Port_Ctrl	EQU	0FF13h		; 8255A Control Port
Port_A		EQU	0FF10h		; 8255A Port A
Port_B		EQU	0FF11h		; 8255A Port B
Port_C		EQU	0FF12h		; 8255A Port C

		.MODEL	SMALL
		.CODE
		mov	dx, Port_Ctrl
		mov	al, 80h
		out	dx, al

		mov	al, 0
		mov	dx, Port_A
		out	dx, al

		mov	bx, 2
repeat: 	mov	cx, 15
loop00:
		mov	dx, Port_C
		mov	al, bl
		out	dx, al
		mov	dx, Port_B
		mov	al, bh
		out	dx, al
		rol	bx, 1
		call	delay		; �I�s�ɶ����𪺰Ƶ{��
		loop	loop00

		mov	cx, 15
loop01: 	ror	bx, 1
		mov	dx, Port_C
		mov	al, bl
		out	dx, al
		mov	dx, Port_B
		mov	al, bh
		out	dx, al
		call	delay		; �I�s�ɶ����𪺰Ƶ{��
		loop	loop01

		mov	ah, 1
		int	16h		; �ˬd��L���A
		jz	repeat		; �Y Z �X�� = 1, ����L�w�İϬO�Ū�
		mov	ah, 0
		int	16h		; Ū����L�w�İϸ��

		mov	ah, 4Ch
		int	21h		; �{������, ��^ DOS

;
;  �� �� �� �� �� �{ ��
;

delay:		push	cx
		push	dx
		mov	dx, 10
delay01:	mov	cx, 0FFFFh
		loop	$
		dec	dx
		jnz	delay01
		pop	dx
		pop	cx
		ret			; ��^�I�s�{��

		.STACK
		END
