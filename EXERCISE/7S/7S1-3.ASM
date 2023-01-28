; ==================================================================== ;
;  ���㢰                                                              ;
;                                                                      ;
;      ����G ���������� ���Ω�C�q��ܾ����򥻹���                    ;
;                                                                      ;
;      �@�B����ت��G                                                  ;
;          ���� 8255A �u�@�Ҧ��A����C�q��ܾ�                         ;
;                                                                      ;
;      �G�B�}�����A�G SW4: -23456--                                    ;
;                     SW5: 123456--                                    ;
;                                                                      ;
;      �T�B�������G �g�@�{������C�q��ܾ�                           ;
;                                                                      ;
; ==================================================================== ;

                .286
Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE
                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; �]�w 8255 �u�@�Ҧ��]�g�J�Ҧ��^

                mov     bx, 0
                mov     cx, 0

loop00:
                mov     al, cl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_A
                out     dx, al

                mov     al, bh
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_B
                out     dx, al

                mov     al, bl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_C
                out     dx, al

                inc     bl
                cmp     bl, 100
                jnz     check_keyboard
                mov     bl, 0
                inc     bh
                cmp     bh, 100
                jnz     check_keyboard
                mov     bh, 0
                inc     cl
                cmp     cl, 100
                jnz     check_keyboard
                mov     cl, 0
check_keyboard:
                call    delay           ; �I�s�ɶ����𪺰Ƶ{��

                mov     ah, 1
                int     16h             ; �ˬd��L���A
                jz      loop00          ; �Y Z �X�� = 1, ����L�w�İϬO�Ū�

                mov     ah, 0
                int     16h             ; Ū����L�w�İϸ��

                cmp     al, 27          ;
                jz      quit
                jmp     loop00          ; �Y�ҫ����䤣�O ESC ��, �h���� loop00

quit:
                mov     ah, 4Ch
                int     21h             ; ��^ DOS

;
;  �� �� �� �� �� �{ ��
;

delay:          push    cx              ; �N cx �Ȧs�������e�O�s�b���|
                push    dx              ; �N dx �Ȧs�������e�O�s�b���|

                mov     dx, 5
delay01:        mov     cx, 0FFFFh
                loop    $
                dec     dx
                jnz     delay01

                pop     dx              ; �N dx �Ȧs�������e�q���|���^
                pop     cx              ; �N cx �Ȧs�������e�q���|���^
                ret                     ; ��^�I�s�{��

                .STACK
                END
