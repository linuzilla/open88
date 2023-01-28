;DATA_1          EQU     56h
;DATA_2          EQU     39h
;DATA_3          EQU     1Eh

DATA_1          EQU     00Fh
DATA_2          EQU     0F0h
DATA_3          EQU     00Fh

                .MODEL  SMALL
                .CODE
Main:           nop
                nop
                nop

                mov     dx, 0FF13h
                mov     al, 80h
                out     dx, al
                call    delay

                mov     dx, 0FF10h
                mov     al, DATA_1
                push    ax
                out     dx, al
                call    delay

                mov     dx, 0FF11h
                mov     al, DATA_2
                out     dx, al
                call    delay

                push    ax
                mov     dx, 0FF12h
                mov     al, DATA_3
                out     dx, al
                call    delay

                push    ax
                mov     dx, 0FF13h
                mov     al, 80h
                out     dx, al
                call    delay

                mov     dx, 0FF12h
                pop     ax
                not     al
                out     dx, al
                call    delay

                mov     dx, 0FF11h
                pop     ax
                not     al
                out     dx, al
                call    delay

                mov     dx, 0FF10h
                pop     ax
                not     al
                out     dx, al
                call    delay

                mov     ah, 1
                int     16h
                jnz     continue
                jmp     Main

continue:


                mov     dx, 0FF13h
                mov     al, 80h
                out     dx, al

                dec     dx
                xor     ax, ax
                out     dx, al
                dec     dx
                out     dx, al
                dec     dx
                out     dx, al

                mov     ax, 4C00h
                int     21h

delay:
                push    ax
                push    cx
                mov     ax, 10
do_loop:        mov     cx, 0
Again:          nop
                loop    Again
                dec     ax
                jnz     do_loop
                pop     cx
                pop     ax
                ret
                END     Main
