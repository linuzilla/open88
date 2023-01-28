/* simulator library ,  written by  Jiann-Ching Liu  */

/* Initial Position of LED */
#define XX      (2)
#define YY      (16)

/* Initial Position of 7's Segment */
#define XXs     (2)
#define YYs     (5)

/* Initial Position of Word Table */
#define XXw     (48)
#define YYw     (9)

/* Initial Position of Speaker */
#define XXp     (56)
#define YYp     (4)

#define Port_A  (0xFF10)
#define Port_B  (0xFF11)
#define Port_C  (0xFF12)

#define portA   (port[0])
#define portB   (port[1])
#define portC   (port[2])
#define portCTL (port[3])

#define Port_Ctl_8253  (0xFF03)
#define Channel2_8253  (0xFF02)

#define DELAY_CLICK (3)

extern int _F12_KeyPress;
extern void _set_click(int);

struct sevenseg {
    int  xx;
    int  yy;
    int  tag;
};

static unsigned char port[4] = { 0, 0, 0, 0 };
                   /*      0     1     2     3     4     5     6     7  */
static int SStable[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
                   /*      8     9     A     B     C     D     E     F  */
                         0x7F, 0x6F, 0x7F, 0x4C, 0x62, 0x69, 0x78, 0x00,
                                     0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71 };

static int PC_speaker = 0;

static int clearTable[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };



void cls(void)
{
    asm {
        mov   ah, 0Fh
        int   10h
        mov   ah, 0
        int   10h
    }
}

void locate(int x, int y)
{
    asm {
        mov   bh, 0
        mov   ax, y
        mov   dx, x
        mov   dh, al
        mov   ah, 02h
        int   10h
    }
}

void print(char *string)
{
    register  i;
    char      x = string[0];

    for (i = 0; x != '\0'; x = string[++i]) {
        asm {
            mov ah, 0Eh
            mov al, x
            int 10h
        }
    }
}

void putchr(char c)
{
    asm {
        mov  ah, 0Eh
        mov  al, c
        int  10h
    }
}


void _delay_clear(int port)
{
    int    xy;
    asm {
        mov   ah, 3
        mov   bh, 0
        int   10h
        mov   xy, dx
    }
    locate(XXw, YYw + port);
    print("ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú");
    asm {
        mov   ah, 2
        mov   bh, 0
        mov   dx, xy
        int   10h
    }
}


void _timeListManager(void)
{
    int i, click = 0;
    for (i = 0; i < 14; i++) {
        switch (clearTable[i]) {
        case 1:
            _delay_clear(i);
            clearTable[i] = 0;
        case 0:
            break;
        default:
            click = 1;
            clearTable[i]--;
        }
    }
    if (click)
        _set_click(click);
}

void _initial(int option)
{
    int   i, j;
    cls();
    asm {
        mov    ah, 09
        mov    al, ' '
        mov    bx, 1Fh
        mov    cx, 25 * 80
        int    10h
    }
    print("                                                                                ");
    print(" Open 88 I/O Experiments Simulator  Version 0.03 (á-release)                    ");
    print(" Copyright (c) 1995  written by  Jiann-Ching Liu.  All rights reserved.         ");
    print("                                                                                ");
    print(" ÚÄÄÄÄÄ¿ÚÄÄÄÄÄ¿ ÚÄÄÄÄÄ¿ÚÄÄÄÄÄ¿ ÚÄÄÄÄÄ¿ÚÄÄÄÄÄ¿                                   ");
    print(" ³     ³³     ³ ³ ÄÄÄ ³³ ÄÄÄ ³ ³ ÄÄÄ ³³ ÄÄÄ ³                                   ");
    print(" ³     ³³     ³ ³³   ³³³³   ³³ ³³   ³³³³   ³³                                   ");
    print(" ³     ³³     ³ ³     ³³     ³ ³     ³³     ³                                   ");
    print(" ³     ³³     ³ ³³   ³³³³   ³³ ³³   ³³³³   ³³ ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ");
    print(" ³     ³³     ³ ³ ÄÄÄ ³³ ÄÄÄ ³ ³ ÄÄÄ ³³ ÄÄÄ ³ ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print(" ÀÄÄÄÄÄÙÀÄÄÄÄÄÙ ÀÄÄÄÄÄÙÀÄÄÄÄÄÙ ÀÄÄÄÄÄÙÀÄÄÄÄÄÙ ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("    Port A         Port B         Port C      ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print(" ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("                                              ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("            7   6   5   4   3   2   1   0     ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("         ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print(" Port A: ³ ( ) ( ) ( ) ( ) ( ) ( ) ( ) ( ) ³  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("         ³                                 ³  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print(" Port B: ³ ( ) ( ) ( ) ( ) ( ) ( ) ( ) ( ) ³  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("         ³                                 ³  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print(" Port C: ³ ( ) ( ) ( ) ( ) ( ) ( ) ( ) ( ) ³  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("         ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ  ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print("                                              ³ ú ú ú ú ú ú ú ú ú ú ú ú ú ú ú ³ ");
    print(" ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß  ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ");

    for (i = 0; i < 2; i++, option >>= 1) {
        if (option & 1) {
            switch(i) {
            case 0: /* Enable PC speaker */
                PC_speaker = 1;
                locate(XXp - 9, YYp);
                print("Speaker: ");
                break;
            case 1: /* Patch 7's Segment */
                for (j = 10; j < 16; j++) {
                    SStable[j] = SStable[j+6];
                }
                break;
            }
        }
    }

//  locate(1,23);
    return;
}

void _simu_out_dx_al(unsigned int _dx, unsigned int _ax)
{
    static struct sevenseg pos[] = {                     /*    ÄaÄ    */
                    {1, 0, 1}, {4, 1, 0}, {4, 3, 0},     /*  f³   ³b  */
                    {1, 4, 1}, {0, 3, 0}, {0, 1, 0},     /*    ÄgÄ    */
                    {1, 2, 1}                            /*  e³   ³c  */
                                   };                    /*    ÄdÄ    */

    int  i, j, k, __ax;
    unsigned char _al = (char) (_ax & 0x00FF), __al;

    if (_dx >= Port_A && _dx <= Port_C) {

        _ax &= 0xFF;

        /*  LED moudle */
        for (i = 0; i < 8; i++) {
            locate(XX + 10 + (7-i)*4, YY + 2 * (_dx - Port_A));
            if ((_ax >> i) & 1)
                putchr('þ');
            else
                putchr(' ');
        }
        /* 7's segment module */
        for (i = 0, __ax = _ax; i < 2; i++, __ax >>= 4) {
            for (j = 0, k = SStable[__ax & 0xF]; j < 7; j++, k >>= 1) {
                locate(XXs+pos[j].xx + (_dx-Port_A)*15+(1-i)*7, YYs+pos[j].yy);
                if (k & 1)
                    print(pos[j].tag ? "ÄÄÄ" : "³");
                else
                    print(pos[j].tag ? "   " : " ");
            }
        }
        /*
                      B    C
                    ÚÄÄÄÄÂÄÄÄÄ¿
                    ³    ³    ³
                  A ³    ³    ³
                    ÀÄÄÄÄÁÄÄÄÄÙ
                    dot matrix module
         */


        if (_dx == Port_A) {
            unsigned char _al_ = _al & 0x0F;

            if ((portA & 0x0F) < 14 && (portA & 0x0F) != _al_) {       // clear
                clearTable[(portA & 0x0F)] = DELAY_CLICK;
                _set_click(1);
            }
            if (_al_ < 14) {
                clearTable[_al_] = 0;
                locate(XXw, YYw + _al_);
                for (i = 7; i >= 0; i--) {
                    if ((portB >> i ) & 1) {
                        print("Ü ");
                    } else {
                        print("ú ");
                    }
                }
                for (i = 7; i > 0; i--) {
                    if ((portC >> i ) & 1) {
                        print("Ü ");
                    } else {
                        print("ú ");
                    }
                }
            }
        } else {
            if ((portA & 0x0F) < 14) {
                locate(XXw + (_dx - Port_B) * 16, YYw + (portA & 0x0F));
                for (i = 7; i > 0; i--) {
                    if ((_al >> i ) & 1) {
                        print("Ü ");
                    } else {
                        print("ú ");
                    }
                }
                if (_dx == Port_B)
                    putchr(_al & 1 ? 'Ü' : 'ú');
                clearTable[(portA & 0x0F)] = 0;
            }
        }


        /* speaker */

        if (PC_speaker) {
            if (_dx == Port_A) {
                 locate(XXp, YYp);
                 if (_al & 1) {
                     __al = _al & 0x03;
                     asm {
                         mov  al, __al
                         shr  al, 1
                         pushf
                         shl  al, 7
                         popf
                         rcr  al, 7
                         mov  __al, al

                         in   al, 61h
                         or   al, __al
                         out  61h, al
                     }
                     putchr('');
                 } else {
                     asm {
                         in   al, 61h
                         and  al, 11111100B
                         out  61h, al
                     }
                     putchr(' ');
                 }
            }
        }


        port[_dx - Port_A] = _al;

    }

    if (PC_speaker && (_dx == Port_Ctl_8253 || _dx == Channel2_8253)) {
        int   __dx = _dx - Channel2_8253 + 0x42;
        asm {
            mov  al, _al;
            mov  dx, __dx;
            out  dx, al
        }
    }

    if (_F12_KeyPress) {
        asm  mov ax, 4CFFh
        asm  int 21h
    }
    return;
}
