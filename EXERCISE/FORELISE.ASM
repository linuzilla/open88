;
;
;
;
o21             EQU      65
o21u            EQU      69
o22             EQU      73
o22u            EQU      78
o23             EQU      82
o24             EQU      87
o24u            EQU      93
o25             EQU      98
o25u            EQU     104
o26             EQU     110
o26u            EQU     116
o27             EQU     123
;
o31             EQU     131
o31u            EQU     139
o32             EQU     147
o32u            EQU     156
o33             EQU     165
o34             EQU     175
o34u            EQU     185
o35             EQU     196
o35u            EQU     208
o36             EQU     220
o36u            EQU     233
o37             EQU     247
;
o41             EQU     262
o41u            EQU     277
o42             EQU     294
o42u            EQU     311
o43             EQU     330
o44             EQU     349
o44u            EQU     370
o45             EQU     392
o45u            EQU     415
o46             EQU     440
o46u            EQU     466
o47             EQU     494
;
o51             EQU     532
o51u            EQU     554
o52             EQU     587
o52u            EQU     622
o53             EQU     659
o54             EQU     698
o54u            EQU     740
o55             EQU     784
o55u            EQU     831
o56             EQU     880
o56u            EQU     932
o57             EQU     988
;
o61             EQU     1047
o61u            EQU     1109
o62             EQU     1175
o62u            EQU     1245
o63             EQU     1319
o64             EQU     1397
o64u            EQU     1480
o65             EQU     1568
o65u            EQU     1661
o66             EQU     1760
o66u            EQU     1865
o67             EQU     1976
rest            EQU     0
final           EQU     -1
repeat          EQU     -2

l0              EQU     128
l1_5            EQU      96
l1              EQU      64
l2_5            EQU      48
l2              EQU      32
l4_5            EQU      24
l4              EQU      16
l8_5            EQU      12
l8              EQU       8
l16_5           EQU       6
l16             EQU       4
l32_5           EQU       3
l32             EQU       2
l64             EQU       1



Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

Port_Ctl_8253   EQU     0FF03h
Channel2_8253   EQU     0FF02H



                .MODEL  SMALL
                .CODE
                mov     ax, @data
                mov     ds, ax

                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; 設定 8255 工作模式（寫入模式）

                cld
replay:
                lea     si, table
next:
                lodsw
                cmp     ax, repeat
                jz      replay
                cmp     ax, final
                jz      exit
                cmp     ax, rest
                jz      rest_pause
                mov     bx, ax

                mov     al, 0B6h
                mov     dx, Port_Ctl_8253
                out     dx, al

                mov     dx, 14h
                mov     ax, 4F38h       ; dx:ax = 144F38h = 1331000
                div     bx              ; 1331000 / frequency

                mov     dx, Channel2_8253
                out     dx, al
                mov     al, ah
                out     dx, al
;
                mov     al, 3
                mov     dx, Port_A
                out     dx, al
;
rest_pause:
                lodsw
                mov     dx, ax
delay:          mov     cx, 0
delay00:        nop
                loop    delay00
                dec     dx
                jnz     delay
;
                mov     al, 0
                mov     dx, Port_A
                out     dx, al

                jmp     next
exit:
                mov     ah, 4Ch
                int     21h

                .DATA

table           LABEL   BYTE
                DW      o63,l8,o62u,l8

                DW      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8
                dw      o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8

                dw      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o61,l8,o57,l8
                dw      o56,l4,rest,l4,o63,l8,o62u,l8

                DW      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8
                dw      o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8

                dw      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o61,l8,o57,l8
                dw      o56,l4,rest,l8,o57,l8,o61,l8,o62,l8

                dw      o63,l4,rest,l8,o55,l8,o64,l8,o63,l8
                dw      o62,l4,rest,l8,o54,l8,o63,l8,o62,l8
                dw      o61,l4,rest,l8,o53,l8,o62,l8,o61,l8
                dw      o57,l4,o63,l8,o43,l8,o53,l8,o53,l8
                dw      o63,l8,o53,l8,o63,l8,o52u,l8,o53,l8,o52u,l8
                Dw      o53,l8,o52u,l8,o53,l8,o62u,l8,o63,l8,o62u,l8
                dw      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8
                dw      o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8
                dw      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o61,l8,o57,l8
                dw      o56,l4,rest,l8,o57,l8,o61,l8,o62,l8

                dw      o63,l4,rest,l8,o55,l8,o64,l8,o63,l8
                dw      o62,l4,rest,l8,o54,l8,o63,l8,o62,l8
                dw      o61,l4,rest,l8,o53,l8,o62,l8,o61,l8
                dw      o57,l4,o63,l8,o43,l8,o53,l8,o53,l8
                dw      o63,l8,o53,l8,o63,l8,o52u,l8,o53,l8,o52u,l8
                Dw      o53,l8,o52u,l8,o53,l8,o62u,l8,o63,l8,o62u,l8
                dw      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8
                dw      o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8
                dw      o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8
                dw      o56,l4,rest,l8,o51,l8,o53,l8,o56,l8
                dw      o57,l4,rest,l8,o53,l8,o61,l8,o57,l8
                dw      o56,l2_5
                DW      final

                .STACK
                END
