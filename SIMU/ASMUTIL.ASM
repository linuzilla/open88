                .286
                .MODEL  SMALL
                .CODE
                PUBLIC  __init_advance
                PUBLIC  __set_click
;               EXTRN   __atexit: NEAR
                EXTRN   __timeListManager: NEAR

FuncKEY         EQU     58h     ; F12

__init_advance  PROC    NEAR
                push    ds
                push    es
                push    dx
                push    bx
                push    ax

                mov     ax, cs
                mov     ds, ax

                mov     ax, 3500h
                int     21h
                mov     cs:[old00seg], es
                mov     cs:[old00off], bx

                mov     ax, 3508h
                int     21h
                mov     cs:[old08seg], es
                mov     cs:[old08off], bx

                mov     ax, 3509h
                int     21h
                mov     cs:[old09seg], es
                mov     cs:[old09off], bx

                mov     ax, 351Bh
                int     21h
                mov     cs:[old1Bseg], es
                mov     cs:[old1Boff], bx

                mov     ax, 3523h
                int     21h
                mov     cs:[old23seg], es
                mov     cs:[old23off], bx

                mov     ax, 3520h
                int     21h
                mov     cs:[old20seg], es
                mov     cs:[old20off], bx

                mov     ax, 3521h
                int     21h
                mov     cs:[old21seg], es
                mov     cs:[old21off], bx



                mov     dx, OFFSET int00_svc
                mov     ax, 2500h
                int     21h

                mov     dx, OFFSET int08_svc
                mov     ax, 2508h
                int     21h

                mov     dx, OFFSET int09_svc
                mov     ax, 2509h
                int     21h

                mov     dx, OFFSET int1B_svc
                mov     ax, 251Bh
                int     21h

                mov     dx, OFFSET int23_svc
                mov     ax, 2523h
                int     21h

                mov     dx, OFFSET int20_svc
                mov     ax, 2520h
                int     21h

                mov     dx, OFFSET int21_svc
                mov     ax, 2521h
                int     21h


                mov     ah, 01          ; cursor off
                mov     cx, 2000h
                int     10h


                pop     ax
                pop     bx
                pop     dx
                pop     es
                pop     ds
                ret

__init_advance  ENDP


int08_svc       PROC    FAR
                pushf
                call    DWORD PTR cs:[old08off]

                push    ax
                mov     al, 0
                xchg    cs:[_Busy_flag], al
                cmp     al, 1
                pop     ax
                jz      critical_section
                iret

critical_section:
                cmp     WORD PTR cs:[_Counter], 0
                jz      exit_section

                dec     WORD PTR cs:[_Counter]

                push    ds
                push    es
                pusha
                mov     ax, @data
                mov     ds, ax
                mov     es, ax
                call    __timeListManager
                popa
                pop     es
                pop     ds

exit_section:
                mov     BYTE PTR cs:[_Busy_flag], 1
                iret

int08_svc       ENDP

_Busy_flag      DB      1
_Counter        DW      0

__set_click     PROC    NEAR
                push    bp
                mov     bp, sp
                push    ax
                mov     ax, [BP][4]
                mov     cs:[_Counter], ax
                pop     ax
                pop     bp
                ret
__set_click     ENDP

int09_svc       PROC    FAR

                push    ax
                in      al, 60h

                cmp     al, FuncKEY
                jz      SHORT myword
                cmp     al, (FuncKEY + 0Fh)
                jz      SHORT myword

Busy:           pop     ax
                jmp     DWORD PTR cs:[old09off]

myword:         push    ds
                mov     ax, @data
                mov     ds, ax
                mov     WORD PTR ds:[__F12_KeyPress], 1
                pop     ds
                jmp     Busy

int09_svc       ENDP

int1B_svc       PROC    FAR             ; Ctrl-Break
                iret
int1B_svc       ENDP

int23_svc       PROC    FAR             ; Ctrl-C
int23_svc       ENDP

int00_svc       PROC    FAR             ; Divide by Zero
int00_svc       ENDP

int20_svc       PROC    FAR
                mov     ax, 4CFEh
int20_svc       ENDP

int21_svc       PROC    FAR
                cmp     ah, 4Ch
                jz      exit
                jmp     DWORD PTR cs:[old21off]

exit:


; --------   Wait for flush ----------------
flush:
                pushf
fflush:         sti
                cmp     WORD PTR cs:[_Counter], 0
                jnz     fflush
                popf


                push    ds
                push    ax

                mov     ds, cs:[old21seg]
                mov     dx, cs:[old21off]
                mov     ax, 2521h
                pushf
                call    DWORD PTR cs:[old21off]

                mov     ds, cs:[old00seg]
                mov     dx, cs:[old00off]
                mov     ax, 2500h
                int     21h

                mov     ds, cs:[old08seg]
                mov     dx, cs:[old08off]
                mov     ax, 2508h
                int     21h

                mov     ds, cs:[old09seg]
                mov     dx, cs:[old09off]
                mov     ax, 2509h
                int     21h

                mov     ds, cs:[old1Bseg]
                mov     dx, cs:[old1Boff]
                mov     ax, 251Bh
                int     21h

                mov     ds, cs:[old23seg]
                mov     dx, cs:[old23off]
                mov     ax, 2523h
                int     21h

                mov     ds, cs:[old20seg]
                mov     dx, cs:[old20off]
                mov     ax, 2520h
                int     21h

                pop     ax
                pop     ds
int21svcjmp:
                pusha
                call    __atexit
                popa
                jmp     DWORD PTR cs:[old21off]

int21_svc       ENDP

__atexit        PROC    NEAR

                mov     ah, 01
                mov     cx, 0B0Ch
                int     10h             ; cursor on

                mov     bh, 0
                mov     dx, 1700h
                mov     ah, 02h
                int     10h             ; locate(23,0)


clear_keyb_buffer:                              ;
                                                ;
                mov     ah, 01                  ;
                int     16h                     ;
                jz      keyb_clean              ;
                mov     ah, 0                   ;
                int     16h                     ;
                jmp     clear_keyb_buffer       ;
                                                ;
keyb_clean:                                     ;

; ---------  Speaker off  ------------------
                in      al, 61h
                and     al, 0FDh
                out     61h, al


                ret
__atexit        ENDP


old00off        DW      ?
old00seg        DW      ?
old08off        DW      ?
old08seg        DW      ?
old09off        DW      ?
old09seg        DW      ?
old1Boff        DW      ?
old1Bseg        DW      ?
old20off        DW      ?
old20seg        DW      ?
old21off        DW      ?
old21seg        DW      ?
old23off        DW      ?
old23seg        DW      ?
                .DATA
                PUBLIC  __F12_KeyPress
__F12_KeyPress  DW      0
                END
