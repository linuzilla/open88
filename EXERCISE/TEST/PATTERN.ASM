Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE
                mov     ax, @data
                mov     ds, ax

                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; 設定 8255 工作模式（寫入模式）


                cld
forever:
                lea     si, pattern
                xor     bx, bx
                mov     cx, 14
loop00:
                mov     al, 14
                mov     dx, Port_A
                out     dx, al

                lodsb
                inc     dx
                out     dx, al
                lodsb
                inc     dx
                out     dx, al

                mov     al, bl
                mov     dx, Port_A
                out     dx, al
                inc     bx
                loop    loop00
                jmp     forever

                .DATA

pattern         LABEL   BYTE
                DB        0, 128
                DB      124, 254
                DB        1,  18
                DB      124,  40
                DB        0,  68
                DB       31, 242
                DB       16,  16
                DB       31, 240
                DB       16,  16
                DB       31, 240
                DB       16,  16
                DB       31, 240
                DB       32,   8
                DB       64,   4
                .STACK
                END
