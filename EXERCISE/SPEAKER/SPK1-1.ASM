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

                mov     dx, Port_A
                mov     al, 2
sound:          xor     al, 2
                out     dx,al
                mov     cx, 120h

                loop    $
                jmp     sound

                .STACK
                END
