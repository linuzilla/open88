;
;
o2c		EQU	 65
o2cu		EQU	 69
o2d		EQU	 73
o2du		EQU	 78
o2e		EQU	 82
o2f		EQU	 87
o2fu		EQU	 93
o2g		EQU	 98
o2gu		EQU	104
o2a		EQU	110
o2au		EQU	116
o2b		EQU	123
;
o3c		EQU	131
o3cu		EQU	139
o3d		EQU	147
o3du		EQU	156
o3e		EQU	165
o3f		EQU	175
o3fu		EQU	185
o3g		EQU	196
o3gu		EQU	208
o3a		EQU	220
o3au		EQU	233
o3b		EQU	247
;
o4c		EQU	262
o4cu		EQU	277
o4d		EQU	294
o4du		EQU	311
o4e		EQU	330
o4f		EQU	349
o4fu		EQU	370
o4g		EQU	392
o4gu		EQU	415
o4a		EQU	440
o4au		EQU	466
o4b		EQU	494
;
o5c		EQU	532
o5cu		EQU	554
o5d		EQU	587
o5du		EQU	622
o5e		EQU	659
o5f		EQU	698
o5fu		EQU	740
o5g		EQU	784
o5gu		EQU	831
o5a		EQU	880
o5au		EQU	932
o5b		EQU	988
;
o6c		EQU	1047
o6cu		EQU	1109
o6d		EQU	1175
o6du		EQU	1245
o6e		EQU	1319
o6f		EQU	1397
o6fu		EQU	1480
o6g		EQU	1568
o6gu		EQU	1661
o6a		EQU	1760
o6au		EQU	1865
o6b		EQU	1976
rest		EQU	0
final		EQU	-1
repeat		EQU	-2

l0		EQU	128
l1_5		EQU	 96
l1		EQU	 64
l2_5		EQU	 48
l2		EQU	 32
l4_5		EQU	 24
l4		EQU	 16
l8_5		EQU	 12
l8		EQU	  8
l16_5		EQU	  6
l16		EQU	  4
l32_5		EQU	  3
l32		EQU	  2
l64		EQU	  1



Port_Ctrl	EQU	0FF13h		; 8255A Control Port
Port_A		EQU	0FF10h		; 8255A Port A
Port_B		EQU	0FF11h		; 8255A Port B
Port_C		EQU	0FF12h		; 8255A Port C

Port_Ctl_8253	EQU	0FF03h
Channel2_8253	EQU	0FF02H



		.MODEL	SMALL
		.CODE
		mov	ax, @data
		mov	ds, ax

		mov	dx, Port_Ctrl
		mov	al, 80h
		out	dx, al		; 設定 8255 工作模式（寫入模式）

		cld
replay:
		lea	si, table
next:
		lodsw
		cmp	ax, repeat
		jz	replay
		cmp	ax, final
		jz	exit
		cmp	ax, rest
		jz	rest_pause
		mov	bx, ax

		mov	al, 0B6h
		mov	dx, Port_Ctl_8253
		out	dx, al

		mov	dx, 14h
		mov	ax, 4F38h	; dx:ax = 144F38h = 1331000
		div	bx		; 1331000 / frequency

		mov	dx, Channel2_8253
		out	dx, al
		mov	al, ah
		out	dx, al
;
		mov	al, 3
		mov	dx, Port_A
		out	dx, al
;
rest_pause:
		lodsw
		mov	dx, ax
delay:		mov	cx, 0
delay00:	nop
		nop
		loop	delay00
		dec	dx
		jnz	delay
;
		mov	al, 0
		mov	dx, Port_A
		out	dx, al

		jmp	next
exit:
		mov	ah, 4Ch
		int	21h

		.DATA

;   Yesterday  Once  More  -------------------------------------

table		LABEL	BYTE
		DW	rest, l2+l8, o5c,l8, o5c,l8, o5d,l8
		DW	o5e,l4, o5e,l8, o5g,l8, o5g,l8, o5g,l8, o5e,l8, o5g,l8, o5e, l8
		DW	o5a,l8, o5g,l4, o5e,l4_5, o5e,l8, o5g,l8
		DW	o5a,l4, o5a,l16,o5b,l8_5, o5e,l8,o5g,l4
		DW	o5a,l2_5+l8,o5e,l8,o5g,l8
		DW	o5a,l4, o6e,l4, o6d,l8, o6c,l4_5, o5b,l4 + l4_5
		DW	o5g,l8, o5e,l8, o5g,l4, o5e,l8
		DW	o5d,l1

		DW	rest, l2+l8, o5c,l8, o5c,l8, o5d,l8
		DW	o5e,l4, o5e,l8, o5g,l8, o5g,l8, o5g,l8, o5e,l8, o5g,l8, o5e, l8
		DW	o5a,l8, o5g,l4, o5e,l4_5, o5e,l8, o5g,l8
		DW	o5a,l4, o5a,l16,o5b,l8_5, o5e,l8,o5g,l4
		DW	o5a,l2+l8, o5b,l4, o6d,l4
		DW	o6c,l8, o5b,l8, o5a,l8, o5a,l4, o5b,l8, o6c,l8, o5b,l8
		DW	o6c,l8, o5b,l4, o5a,l4_5, o5a,l8, o5b,l8
		DW	o6c,l4, o6c,l8, o5a,l8, o5a, l8, o6c,l4, o6d, l8+l2
		DW	o6c,l4, o6d,l4
		DW	o6e,l8, o6e,l8, o6e,l8, o6e,l4_5, o6d,l8, o6c,l8
		DW	o5b,l8, o6c,l8, o5b,l8, o5a, l4_5, o5e,l8, o5e,l16, o5g,l16
		DW	o5g,l1

		DW	rest, l2_5, o6c,l8, o6d,l8
		DW	o6e,l8, o6e,l8, o6e,l8, o6e,l8, o6e,l4, o6d,l8, o6c,l8
		DW	o5b,l8, o6c,l8, o5b,l8, o5a,l4_5, o5e,l8, o5e,l16, o5g,l16
		DW	o5g,l1

		DW	rest, l2_5, o5a,l8, o5b,l8
		DW	o6c,l8, o5b,l8, o6c,l8, o6c,l16, o6d,l16, o6d,l4, o6c,l8, o5b,l8
		DW	o6c,l8, o5b,l8, o6c,l8, o6c,l16, o6d,l16, o6d,l4, o6c,l8, o6d,l8
		DW	o6e,l4, o6d,l16, o6e,l8_5, o6d,l8, o6c, l4_5, o5a,l2
		DW	o5e,l4, o5e,l8, o5a,l8, o5e,l8, o5e,l16, o5g,l16+l1
		DW	rest,l4_5, o5e,l8, o5e,l8, o5d,l16, o5c,l8_5, o5d,l4
		DW	o5e,l2, o5f,l4, o5d,l8+l1
		DW	repeat
		DW	final

		.STACK
		END
