                .286
                .MODEL  SMALL, C
                .CODE
                EXTRN   _initial: NEAR
                EXTRN   _simu_out_dx_al: NEAR
                EXTRN   _init_advance: NEAR

                PUBLIC  $outdxal$
$outdxal$       PROC    NEAR USES ds es ax bx cx dx si di, parameter: WORD

                push    ax
                push    dx              ; prepare for call _simu_out_dx_al

                out     dx, al

                mov     ax, @data
                mov     ds, ax
                mov     es, ax

                cmp     BYTE PTR [initial], 0
                jnz     already_init
                push    parameter
                call    _initial
                pop     ax

                call    _init_advance          ;  danger

                inc     BYTE PTR [initial]
already_init:
                call    _simu_out_dx_al
                add     sp, 4

                ret
$outdxal$       ENDP
                .DATA
initial         DB      0
                END
