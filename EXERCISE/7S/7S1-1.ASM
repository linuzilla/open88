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

Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE
                push    ds
                mov     ax, 0
                push    ax

                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; �]�w 8255 �u�@�Ҧ��]�g�J�Ҧ��^

                mov     al, 0ABh
                mov     dx, Port_A
                out     dx, al
                mov     al, 0CDh
                mov     dx, Port_B
                out     dx, al
                mov     al, 0EFh
                mov     dx, Port_C
                out     dx, al

                retf
                .STACK
                END
