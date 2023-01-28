                .MODEL  SMALL
                .CODE
Start:
                mov     ax, @data
                mov     ds, ax

                mov     ah, 09
                mov     dx, OFFSET message
                int     21h

Repeat:         mov     si, 0
                call    Begin
                mov     al, 80h
                mov     dx, 0FF13h
                out     dx, al
                mov     ah, 1
                int     16h
                jz      Repeat
                mov     ah, 0
                int     16h
                mov     ax, 4C00h
                int     21h

Begin:          mov     di, OFFSET Freq[si]
                cmp     di, -1
                jz      Quit
                mov     bx, OFFSET Leng[si]
                call    speaker
                add     si, 02
                jnz     Begin
Quit:           ret

speaker:        mov     dx, 0FF03h
                mov     al, 0B6h
                out     dx, al
                mov     dx, 01Ch
                div     di
                mov     dx, 0FF02h
                out     dx, al
                mov     al, ah
                out     dx, al
                mov     dx, 0FF13h
                mov     al, 80h
                out     dx, al
                mov     dx, 0FF10h
                mov     al, 03
                out     dx, al
Delay_1:        mov     cx, 0F000h
Delay_2:
                loop    Delay_2
                dec     bx
                jnz     Delay_1
                mov     al, 0
                mov     dx, 0FF10h
                out     dx, al
                ret

                .DATA
Freq            DB      026H,001H,006H,001H,0E9H,000H,0E9H,000H,006H,001H,0E9H,000H,0AFH,000H,093H,000H
                DB      09CH,000H,0AFH,000H,0C4H,000H,0AFH,000H,093H,000H,0AFH,000H,0E9H,000H,006H,001H
                DB      026H,001H,026H,001H,026H,001H,006H,001H,0E9H,000H,006H,001H,026H,001H,006H,001H
                DB      006H,001H,026H,001H,006H,001H,0E9H,000H,0E9H,000H,006H,001H,0E9H,000H,0AFH,000H
                DB      093H,000H,09CH,000H,0AFH,000H,0C4H,000H,0AFH,000H,093H,000H,0AFH,000H,0E9H,000H
                DB      006H,001H,026H,001H,05DH,001H,05DH,001H,026H,001H,0E9H,000H,006H,001H,026H,001H
                DB      006H,001H,0E9H,000H,026H,001H,05DH,001H,026H,001H,05DH,001H,05DH,001H,026H,001H
                DB      05DH,001H,026H,001H,05DH,001H,037H,001H,088H,001H,037H,001H,088H,001H,088H,001H
                DB      037H,001H,088H,001H,037H,001H,088H,001H,0D2H,001H,0D2H,001H,05DH,001H,05DH,001H
                DB      026H,001H,026H,001H,006H,001H,0E9H,000H,006H,001H,026H,001H,05DH,001H,088H,001H
                DB      05DH,001H,026H,001H,0E9H,000H,006H,001H,026H,001H,006H,001H,0E9H,000H,0FFH,0FFH

Leng            DB      00CH,000H,00CH,000H,019H,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H
                DB      00CH,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H,019H,000H,00CH,000H,00CH,000H
                DB      019H,000H,019H,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H,019H,000H,019H,000H
                DB      019H,000H,00CH,000H,00CH,000H,019H,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H
                DB      00CH,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H,019H,000H,00CH,000H
                DB      00CH,000H,019H,000H,019H,000H,00CH,000H,00CH,000H,00CH,000H,00CH,000H,019H,000H
                DB      019H,000H,032H,000H,00CH,000H,019H,000H,00CH,000H,019H,000H,019H,000H,00CH,000H
                DB      019H,000H,00CH,000H,032H,000H,00CH,000H,019H,000H,00CH,000H,019H,000H,019H,000H
                DB      00CH,000H,019H,000H,00CH,000H,032H,000H,019H,000H,019H,000H,019H,000H,019H,000H
                DB      019H,000H,019H,000H,019H,000H,00CH,000H,00CH,000H,00CH,000H,019H,000H,00CH,000H
                DB      00CH,000H,00CH,000H,00CH,000H,00CH,000H,019H,000H,019H,000H,019H,000H,090H,090H

message         DB      13, 10, 'Music: Turkey in The Straw', 13, 10, '$'
                .STACK
                END     Start
