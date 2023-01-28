; ==================================================================== ;
;  １～２							       ;
;								       ;
;      實驗： ８２５５Ａ 應用於 ＬＥＤ 的基本實驗		       ;
;								       ;
;      一、實驗目的：						       ;
;	   應用 8255A 工作模式，控制發光二極體 Ｌ1 ～ Ｌ24 亮暗狀態    ;
;								       ;
;      二、開關狀態： SW3: -234 				       ;
;								       ;
;      三、實驗條件： 寫一程式控制 LED 使其亮暗狀態如下 	       ;
;								       ;
;		      ●○●○●○●○				       ;
;		      ●○●○●○●○				       ;
;		      ●○●○●○●○				       ;
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

		mov	al, 01010101b	; 分別送 (01010101)b 的資料
		mov	dx, Port_A	; 到 Port_A, Port_B 及 Port_C
		out	dx, al		; 使接到這些 Port 的 LED 亮起來
		mov	dx, Port_B
		out	dx, al
		mov	dx, Port_C
		out	dx, al

		mov	ah, 4Ch
		int	21h		; 返回 DOS
		.STACK
		END
