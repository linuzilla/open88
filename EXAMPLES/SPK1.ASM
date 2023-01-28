		.286
Port_Ctrl	EQU	0FF13h		; 8255A Control Port
Port_A		EQU	0FF10h		; 8255A Port A
Port_B		EQU	0FF11h		; 8255A Port B
Port_C		EQU	0FF12h		; 8255A Port C

		.MODEL	SMALL
		.CODE
		mov	dx, Port_Ctrl
		mov	al, 80h
		out	dx, al

		mov	dx, Port_A
		mov	al, 1
sound:		xor	al, 1
		out	dx,al
		mov	cx, 120h

		loop	$
		jmp	sound

		.STACK
		END
