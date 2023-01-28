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

loop00:         mov     al, bl
                mov     dx, Port_A
                out     dx, al

                mov     al, 1
                mov     cx, 8
loop01:         mov     dx, Port_B
                out     dx, al
                inc     dx
                not     al
                out     dx, al
                not     al
                call    delay
                shl     al, 1
                loop    loop01

                inc     bx
                cmp     bx, 14
                jc      loop00

                mov     ah, 4Ch
                int     21h             ; 返回 DOS

delay:          push    cx
                push    dx
                mov     dx, 10
delay01:        mov     cx, 0FFFFh
                loop    $
                dec     dx
                jnz     delay01
                pop     dx
                pop     cx
                ret                     ; 返回呼叫程式

                .STACK
                END
