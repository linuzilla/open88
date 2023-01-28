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

loop00:
                mov     ah, 2Ch
                int     21h
                mov     al, dh
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_C
                out     dx, al

                mov     al, cl
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_B
                out     dx, al

                mov     al, ch
                aam
                shl     ah, 4
                add     al, ah
                mov     dx, Port_A
                out     dx, al

                mov     ah, 1
                int     16h             ; �ˬd��L���A
                jz      loop00          ; �Y Z �X�� = 1, ����L�w�İϬO�Ū�

                mov     ah, 0
                int     16h             ; Ū����L�w�İϸ��

                cmp     al, 27          ;
                jnz     loop00          ; �Y�ҫ����䤣�O ESC ��, �h���� loop00

                mov     ah, 4Ch
                int     21h             ; ��^ DOS

                .STACK
                END
