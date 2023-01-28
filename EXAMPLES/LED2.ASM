; ==================================================================== ;
;  ２～１							       ;
;								       ;
;      實驗： ８２５５Ａ 應用於 ＬＥＤ 動態展示的基本實驗	       ;
;								       ;
;      一、實驗目的：						       ;
;	   應用 8255A 工作模式，控制發光二極體 Ｌ1 ～ Ｌ24 亮暗狀態    ;
;								       ;
;      二、開關狀態： SW3: -234 				       ;
;								       ;
;      三、實驗條件： 寫一程式控制 LED 使其全亮全暗交替直到鍵盤桉      ;
;		      下 ESC 鍵後停止				       ;
;								       ;
;		      ○○○○○○○○		  ●●●●●●●●     ;
;		      ○○○○○○○○	←──→  ●●●●●●●●     ;
;		      ○○○○○○○○		  ●●●●●●●●     ;
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

loop00:
		mov	al, 11111111b	; 分別送 (11111111)b 的資料
		mov	dx, Port_A	; 到 Port_A, Port_B 及 Port_C
		out	dx, al		; 使接到這些 Port 的 LED 亮起來
		mov	dx, Port_B
		out	dx, al
		mov	dx, Port_C
		out	dx, al

		call	delay		; 呼叫時間延遲的副程式

		mov	al, 00000000b	; 分別送 (00000000)b 的資料
		mov	dx, Port_A	; 到 Port_A, Port_B 及 Port_C
		out	dx, al		; 使接到這些 Port 的 LED 全暗
		mov	dx, Port_B
		out	dx, al
		mov	dx, Port_C
		out	dx, al

		call	delay		; 呼叫時間延遲的副程式

		mov	ah, 1
		int	16h		; 檢查鍵盤狀態
		jz	loop00		; 若 Z 旗標 = 1, 表鍵盤緩衝區是空的
		mov	ah, 0
		int	16h		; 讀取鍵盤緩衝區資料

		mov	ah, 4Ch
		int	21h		; 程式結束, 返回 DOS

;
;  時 間 延 遲 副 程 式
;

delay:		mov	dx, 30
delay01:	mov	cx, 0FFFFh
		loop	$
		dec	dx
		jnz	delay01
		ret			; 返回呼叫程式

		.STACK
		END
