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

loop00:
                mov     ah, 2Ch
                int     21h
                mov     al, dh
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_C
                out     dx, al

                mov     al, cl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_B
                out     dx, al

                mov     al, ch
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_A
                out     dx, al
                jmp     loop00


                .STACK
                END
