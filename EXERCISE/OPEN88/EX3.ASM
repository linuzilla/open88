Port_Ctrl       EQU     0FF13h
Port_A          EQU     0FF10h
Port_B          EQU     0FF11h
Port_C          EQU     0FF12h


                .MODEL  SMALL
                .CODE
Main:           mov     bx, 1
                mov     di, bx
                cld
                mov     si, OFFSET Pattern - 1
                mov     al, 89h
                mov     dx, Port_Ctrl
                out     dx, al
                call    Two_Zero
; Read:           mov     dx, Port_C
;                 in      al, dx
;                 and     al, 0C0h
;                 cmp     al, 80h
;                 jnz     Not80
;                 call    Two_Zero
;                 jmp     Main
; Not80:          cmp     al, 40h
;                 jnz     Read
Read:
                call    IncCounter
                call    Delay

                mov     ah, 1
                int     16h
                jz      Read
                mov     ax, 4C00h
                int     21h

Two_Zero:       mov     al, 3Fh
                mov     dx, Port_A
                out     dx, al
                inc     dx
                out     dx, al
                call    Delay
                retn

IncCounter:     cmp     bx, 10
                jz      Ten
                inc     bx
                push    bx
                add     bx, si
                mov     al, [bx]
                mov     dx, Port_B
                out     dx, al
                pop     bx
                retn

Ten:            mov     bx, 1
                mov     al, 3Fh
                mov     dx, Port_B
                out     dx, al
                cmp     di, 10
                jz      HTen
                inc     di
                push    di
                add     di, si
                mov     al, [di]
                mov     dx, Port_A
                out     dx, al
                pop     di
                ret

HTen:           mov     di, 1
                mov     al, 3Fh
                mov     dx, Port_A
                out     dx, al
                ret

Delay:
                push    dx
                mov     dx, 100
delay_loop:     mov     cx, 0
                loop    $
                dec     dx
                jnz     delay_loop
                pop     dx
                retn


Pattern         DB      3Fh, 06h, 5Bh, 4Fh, 66h, 6Dh, 7Dh, 27h, 7Fh, 6Fh, 90h, 90h

                .STACK
                END     Main
