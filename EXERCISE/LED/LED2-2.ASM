; ==================================================================== ;
;  ２∼２							       ;
;								       ;
;      實驗： ８２５５Ａ 應用於 ＬＥＤ 動態展示的基本實驗	       ;
;								       ;
;      一、實驗目的：						       ;
;	   應用 8255A 工作模式，控制發光二極體 Ｌ1 ∼ Ｌ8 亮暗狀態     ;
;								       ;
;      二、開關狀態： SW3: -234 				       ;
;								       ;
;      三、實驗條件： 寫一程式控制 LED 使其如霹靂燈般來回跑動	       ;
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
		out	dx, al		; 設定 8255 工作模式（寫入模式）

		mov	dx, Port_A	; 將 Port_A 的位址放在 dx 暫存器
loop00:
		mov	al, 00000001b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●●●●○
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00000010b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●●●○●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00000100b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●●○●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00001000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●○●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00010000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●○●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00100000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●○●●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 01000000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●○●●●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 10000000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ○●●●●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 01000000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●○●●●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00100000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●○●●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00010000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●○●●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00001000b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●○●●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00000100b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●●○●●
		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00000010b	; 送資料到 Port_A 使 LED 狀態如
		out	dx, al		; ●●●●●●○●
		call	delay		; 呼叫時間延遲的副程式

		mov	ah, 1
		int	16h		; 檢查鍵盤狀態
		jz	loop00		; 若 Z 旗標 = 1, 表鍵盤緩衝區是空的

		mov	ah, 0
		int	16h		; 讀取鍵盤緩衝區資料

		cmp	al, 27		;
		jnz	loop00		; 若所按的鍵不是 ESC 鍵, 則跳到 loop00

		mov	ah, 4Ch
		int	21h		; 程式結束, 返回 DOS

;
;  時 間 延 遲 副 程 式
;

delay:		push	cx		; 將 cx 暫存器的內容保存在堆疊
		push	dx		; 將 dx 暫存器的內容保存在堆疊

		mov	dx, 30
delay01:	mov	cx, 0FFFFh
		loop	$
		dec	dx
		jnz	delay01

		pop	dx		; 將 dx 暫存器的內容從堆疊取回
		pop	cx		; 將 cx 暫存器的內容從堆疊取回
		ret			; 返回呼叫程式

		.STACK
		END
