Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE
                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; 設定 8255 工作模式（寫入模式）

forever:
                mov     bx, 0
                mov     cl, 10110011B

loop00:         mov     al, bl
                mov     dx, Port_A
                out     dx, al

                mov     al, cl
                mov     dx, Port_B
                out     dx, al
                inc     dx
                not     al
                out     dx, al
                not     cx

                inc     bx
                cmp     bx, 14
                jc      loop00
                jmp     forever


                .STACK
                END
