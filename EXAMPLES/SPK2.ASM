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

		mov	bx, 120h
		mov	dx, Port_A
		mov	al, 1
sound:		xor	al, 1
		out	dx, al
		mov	cx, bx

		loop	$

		push	ax
		mov	ah, 1
		int	16h
		jz	nokey
		mov	ah, 0
		int	16h
		and	al, 11011111B
		cmp	al, 'U'
		jnz	ne
		sub	bx, 20
		jmp	SHORT nokey
next:		cmp	al, 'D'
		jnz	nokey
		add	bx, 20
nokey:
		pop	ax
		jmp	sound

		.STACK
		END
