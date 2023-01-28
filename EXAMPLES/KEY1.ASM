                .286
Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE

                mov     dx, Port_Ctrl
                mov     al, 82h
                out     dx, al

next:

                mov     dx, Port_B
                in      al, dx

                mov     cx, 8
                mov     si, 1
                mov     dx, 0
loop00:         shr     al, 1
                jnc     skip
                add     dx, si
skip:           inc     si
                loop    loop00
                mov     al, dl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_C
                out     dx, al
                call    delay

                mov     ah, 1
                int     16h
                jz      next

                mov     ah, 4Ch
                int     21h             ; ªð¦^ DOS

delay:
                push    cx
                mov     cx, 0
                loop    $
                pop     cx
                ret

                .STACK
                END
