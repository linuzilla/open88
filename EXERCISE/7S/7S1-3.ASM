; ==================================================================== ;
;  １～１                                                              ;
;                                                                      ;
;      實驗： ８２５５Ａ 應用於七段顯示器的基本實驗                    ;
;                                                                      ;
;      一、實驗目的：                                                  ;
;          應用 8255A 工作模式，控制七段顯示器                         ;
;                                                                      ;
;      二、開關狀態： SW4: -23456--                                    ;
;                     SW5: 123456--                                    ;
;                                                                      ;
;      三、實驗條件： 寫一程式控制七段顯示器                           ;
;                                                                      ;
; ==================================================================== ;

                .286
Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE
                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; 設定 8255 工作模式（寫入模式）

                mov     bx, 0
                mov     cx, 0

loop00:
                mov     al, cl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_A
                out     dx, al

                mov     al, bh
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_B
                out     dx, al

                mov     al, bl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_C
                out     dx, al

                inc     bl
                cmp     bl, 100
                jnz     check_keyboard
                mov     bl, 0
                inc     bh
                cmp     bh, 100
                jnz     check_keyboard
                mov     bh, 0
                inc     cl
                cmp     cl, 100
                jnz     check_keyboard
                mov     cl, 0
check_keyboard:
                call    delay           ; 呼叫時間延遲的副程式

                mov     ah, 1
                int     16h             ; 檢查鍵盤狀態
                jz      loop00          ; 若 Z 旗標 = 1, 表鍵盤緩衝區是空的

                mov     ah, 0
                int     16h             ; 讀取鍵盤緩衝區資料

                cmp     al, 27          ;
                jz      quit
                jmp     loop00          ; 若所按的鍵不是 ESC 鍵, 則跳到 loop00

quit:
                mov     ah, 4Ch
                int     21h             ; 返回 DOS

;
;  時 間 延 遲 副 程 式
;

delay:          push    cx              ; 將 cx 暫存器的內容保存在堆疊
                push    dx              ; 將 dx 暫存器的內容保存在堆疊

                mov     dx, 5
delay01:        mov     cx, 0FFFFh
                loop    $
                dec     dx
                jnz     delay01

                pop     dx              ; 將 dx 暫存器的內容從堆疊取回
                pop     cx              ; 將 cx 暫存器的內容從堆疊取回
                ret                     ; 返回呼叫程式

                .STACK
                END
