; ==================================================================== ;
;  ���㢰                                                              ;
;                                                                      ;
;      ����G ���������� ���Ω� �ڢӢ� ���򥻹���                      ;
;                                                                      ;
;      �@�B����ت��G                                                  ;
;          ���� 8255A �u�@�Ҧ��A����o���G���� ��1 �� ��24 �G�t���A    ;
;                                                                      ;
;      �G�B�}�����A�G SW3: -234                                        ;
;                                                                      ;
;      �T�B�������G �g�@�{������ LED �Ϩ���G                        ;
;                                                                      ;
;                     ����������������                                 ;
;                     ����������������                                 ;
;                     ����������������                                 ;
;                                                                      ;
; ==================================================================== ;


Port_Ctrl       EQU     0FF13h          ; 8255A Control Port
Port_A          EQU     0FF10h          ; 8255A Port A
Port_B          EQU     0FF11h          ; 8255A Port B
Port_C          EQU     0FF12h          ; 8255A Port C

                .MODEL  SMALL
                .CODE
                mov     dx, Port_Ctrl
                mov     al, 80h
                out     dx, al          ; �]�w 8255 �u�@�Ҧ��]�g�J�Ҧ��^

                mov     al, 11111110b   ; ���O�e (11111111)b �����
                mov     dx, Port_A      ; �� Port_A, Port_B �� Port_C
                out     dx, al          ; �ϱ���o�� Port �� LED �G�_��
                mov     dx, Port_B
                out     dx, al
                mov     dx, Port_C
                out     dx, al

                mov     ah, 4Ch
                int     21h             ; ��^ DOS
                .STACK
                END
