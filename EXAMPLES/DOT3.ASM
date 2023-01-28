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
		out	dx, al


		cld
forever:
		lea	di, pattern
		mov	cx, 3
loop00: 	push	cx

		mov	cx, 20
loop01: 	push	cx

		mov	si, di
		xor	bx, bx
		mov	cx, 14

loop02:
		mov	al, 14
		mov	dx, Port_A
		out	dx, al

		lodsb
		inc	dx
		out	dx, al
		lodsb
		inc	dx
		out	dx, al

		mov	al, bl
		mov	dx, Port_A
		out	dx, al
		inc	bx
		loop	loop02

		pop	cx
		loop	loop01

		add	di, patternLEN
		pop	cx
		loop	loop00

		mov	ah, 1
		int	16h
		jz	forever
		mov	ah, 0
		int	16h
		mov	ah, 4Ch
		int	21h

		.DATA

pattern 	LABEL	BYTE
		DB	  0, 128
		DB	124, 254
		DB	  1,  18
		DB	124,  40
		DB	  0,  68
		DB	 31, 242
		DB	 16,  16
		DB	 31, 240
		DB	 16,  16
		DB	 31, 240
		DB	 16,  16
		DB	 31, 240
		DB	 32,   8
		DB	 64,   4
patternLEN	EQU	$ - pattern
		DB	 32,   0
		DB	 17, 248
		DB	252, 136
		DB	  0, 136
		DB	120, 136
		DB	  0, 136
		DB	123, 248
		DB	  0, 136
		DB	120, 136
		DB	 72, 136
		DB	 72, 136
		DB	 72, 138
		DB	120, 138
		DB	 72, 142

		DB	  4,  16
		DB	 14,  16
		DB	248, 144
		DB	  8,  80
		DB	254, 144
		DB	  8,  80
		DB	 28,  16
		DB	 26,  30
		DB	 41, 240
		DB	 40,  16
		DB	 72,  16
		DB	136,  16
		DB	  8,  16
		DB	  8,  16
		.STACK
		END
