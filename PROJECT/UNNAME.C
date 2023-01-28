/*  無名棋程式 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <time.h>

#define RNDCNT (10)
#define BackGround (WHITE)
#define LineCOLOR  (GREEN)
#define CompCOLOR  (LIGHTRED)
#define UserCOLOR  (BLUE)
#define TextCOLOR  (BLACK)
#define CursCOLOR  (BLACK)
#define BoarCOLOR  (CYAN)


int  user_move(void);
int  comp_move(void);
void init_table(void);
void eat(void);
void draw(int x, int y);
int  moveable(void);
int  check(int x, int y);
int  random_move(void);
int  eat_move(int *);
int  safty(void);
int  eatable(int *x, int *y, int who);
void outcpattern(int x, int y, char *msg, int len, int xs, int ys);

char msg1[]    = {
                        /* 恭 */
                0x02,0x01,0x00,
                0x03,0x81,0xc0,
                0x03,0x01,0x98,
                0x7f,0xff,0xfc,
                0x03,0x01,0x80,
                0x03,0x01,0x80,
                0x03,0x01,0x80,
                0x03,0x01,0x86,
                0xff,0xff,0xff,
                0x01,0x81,0x00,
                0x03,0x00,0x80,
                0x06,0x20,0x40,
                0x0c,0x38,0x30,
                0x18,0x30,0x1c,
                0x64,0x30,0x0f,
                0x87,0x34,0x04,
                0x06,0x32,0x20,
                0x0c,0x33,0x10,
                0x0c,0x31,0x18,
                0x18,0x31,0x8c,
                0x30,0x31,0x8c,
                0x40,0x31,0x8c,
                0x03,0xf0,0x00,
                0x00,0x60,0x00,

                        /* 喜 */
                0x00,0x1c,0x00,
                0x00,0x18,0x0c,
                0x7f,0xff,0xfe,
                0x00,0x18,0x00,
                0x00,0x18,0x30,
                0x1f,0xff,0xf8,
                0x00,0x00,0x00,
                0x08,0x00,0x30,
                0x0f,0xff,0xf8,
                0x0c,0x00,0x30,
                0x0c,0x00,0x30,
                0x0f,0xff,0xf0,
                0x0a,0x00,0xc0,
                0x01,0x00,0x80,
                0x01,0x81,0x06,
                0xff,0xff,0xff,
                0x00,0x00,0x00,
                0x08,0x00,0x30,
                0x0f,0xff,0xf8,
                0x0c,0x00,0x30,
                0x0c,0x00,0x30,
                0x0c,0x00,0x30,
                0x0f,0xff,0xf0,
                0x08,0x00,0x20,

                        /* !  */
                0x00,0x00,0x00,
                0x02,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x00,0x00,0x00,
                0x00,0x00,0x00,
                0x02,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x02,0x00,0x00,
                0x00,0x00,0x00,

                        /* 您 */
                0x04,0x10,0x00,
                0x07,0x1c,0x00,
                0x0e,0x38,0x06,
                0x0c,0x3f,0xff,
                0x18,0x61,0x86,
                0x18,0xc1,0x84,
                0x3d,0x01,0x88,
                0x6c,0x09,0xa0,
                0x4c,0x1d,0x90,
                0x8c,0x19,0x98,
                0x0c,0x31,0x8c,
                0x0c,0xc1,0x86,
                0x0d,0x0f,0x86,
                0x08,0x03,0x00,
                0x00,0x20,0x00,
                0x02,0x18,0x00,
                0x13,0x8c,0x08,
                0x13,0x06,0x44,
                0x33,0x06,0x46,
                0x33,0x00,0x43,
                0x73,0x00,0x63,
                0x63,0xff,0xe3,
                0x61,0xff,0xc0,
                0x00,0x00,0x00,

                        /* 贏 */
                0x00,0x18,0x00,
                0x00,0x0c,0x06,
                0xff,0xff,0xff,
                0x0c,0x00,0x00,
                0x0c,0x00,0x00,
                0x07,0xff,0xf8,
                0x10,0x00,0x00,
                0x1f,0xff,0xf8,
                0x18,0x00,0x18,
                0x18,0x00,0x18,
                0x1f,0xff,0xf8,
                0x00,0x00,0x04,
                0x46,0x46,0xfe,
                0x7f,0x7f,0x4c,
                0x66,0x66,0x4c,
                0x76,0x7e,0xcc,
                0x6e,0x66,0x6c,
                0x66,0x7e,0x7c,
                0x6e,0x66,0x5c,
                0x76,0x7e,0x4d,
                0x66,0x20,0x4d,
                0x46,0x74,0x85,
                0x5e,0xc2,0x87,
                0x85,0x03,0x03,

                        /* 了 */
                0x00,0x00,0x00,
                0x00,0x00,0x18,
                0x3f,0xff,0xfc,
                0x00,0x00,0x18,
                0x00,0x00,0x30,
                0x00,0x00,0x60,
                0x00,0x00,0xc0,
                0x00,0x03,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x03,0xfc,0x00,
                0x00,0x38,0x00,
                        };
char msg2[]    = {
                        /* 抱 */
                0x08,0x08,0x00,
                0x0e,0x0e,0x00,
                0x0c,0x0c,0x00,
                0x0c,0x0c,0x06,
                0x0c,0x1f,0xff,
                0x0d,0x18,0x06,
                0xff,0xb0,0x06,
                0x0c,0x40,0x66,
                0x0c,0x9f,0xf6,
                0x0c,0x18,0x66,
                0x0c,0x18,0x66,
                0x0d,0x98,0x66,
                0x1f,0x18,0x66,
                0xfc,0x1f,0xe6,
                0x6c,0x18,0x46,
                0x0c,0x18,0x3c,
                0x0c,0x18,0x08,
                0x0c,0x18,0x02,
                0x0c,0x18,0x02,
                0x0c,0x18,0x02,
                0x0c,0x18,0x03,
                0x0c,0x1f,0xff,
                0x7c,0x0f,0xfe,
                0x18,0x00,0x00,

                        /* 歉 */
                0x20,0x70,0x80,
                0x18,0x60,0xe0,
                0x0c,0xc0,0xc0,
                0x08,0x88,0xc0,
                0xff,0xfc,0xc0,
                0x19,0x81,0x86,
                0x19,0x81,0xff,
                0x7f,0xfb,0x66,
                0x19,0x9a,0x64,
                0x19,0x9c,0x68,
                0x19,0x98,0x60,
                0xff,0xfe,0x60,
                0x19,0x98,0x60,
                0x19,0x98,0x60,
                0x19,0x98,0x60,
                0x7f,0xf8,0xf0,
                0x19,0x90,0xd0,
                0x39,0xc0,0xd0,
                0x39,0xb1,0x98,
                0x59,0x99,0x88,
                0x59,0x8b,0x0c,
                0x99,0x82,0x06,
                0x19,0x84,0x07,
                0x11,0x08,0x02,

                        /* !  */
                0x00,0x00,0x00,
                0x02,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x02,0x00,0x00,
                0x00,0x00,0x00,
                0x00,0x00,0x00,
                0x02,0x00,0x00,
                0x07,0x00,0x00,
                0x07,0x00,0x00,
                0x02,0x00,0x00,
                0x00,0x00,0x00,

                        /* 您 */
                0x04,0x10,0x00,
                0x07,0x1c,0x00,
                0x0e,0x38,0x06,
                0x0c,0x3f,0xff,
                0x18,0x61,0x86,
                0x18,0xc1,0x84,
                0x3d,0x01,0x88,
                0x6c,0x09,0xa0,
                0x4c,0x1d,0x90,
                0x8c,0x19,0x98,
                0x0c,0x31,0x8c,
                0x0c,0xc1,0x86,
                0x0d,0x0f,0x86,
                0x08,0x03,0x00,
                0x00,0x20,0x00,
                0x02,0x18,0x00,
                0x13,0x8c,0x08,
                0x13,0x06,0x44,
                0x33,0x06,0x46,
                0x33,0x00,0x43,
                0x73,0x00,0x63,
                0x63,0xff,0xe3,
                0x61,0xff,0xc0,
                0x00,0x00,0x00,

                        /* 輸 */
                0x10,0x01,0xc0,
                0x1c,0x01,0x80,
                0x19,0x03,0x40,
                0xff,0x86,0x20,
                0x18,0x0c,0x18,
                0x18,0x18,0x0c,
                0xff,0x20,0x07,
                0x99,0x4f,0xf2,
                0x99,0x00,0x00,
                0x99,0x23,0x04,
                0xff,0x3f,0xa7,
                0x99,0x33,0x36,
                0x99,0x33,0x26,
                0x99,0x33,0x26,
                0xff,0x3f,0x26,
                0x99,0x33,0x26,
                0x18,0x33,0x26,
                0x19,0x33,0x26,
                0xff,0xbf,0x26,
                0x18,0x33,0x26,
                0x18,0x33,0x06,
                0x18,0x63,0x06,
                0x18,0x47,0x3e,
                0x18,0x82,0x0c,

                        /* 了 */
                0x00,0x00,0x00,
                0x00,0x00,0x18,
                0x3f,0xff,0xfc,
                0x00,0x00,0x18,
                0x00,0x00,0x30,
                0x00,0x00,0x60,
                0x00,0x00,0xc0,
                0x00,0x03,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x00,0x0c,0x00,
                0x03,0xfc,0x00,
                0x00,0x38,0x00
                };


struct _player {
     char *message;
     int  (*func)(void);
     int  number;
} player[2] = {
                 { msg1,  user_move, 6 },
                 { msg2, comp_move, 6 }
              };

struct _dir {
    int   x, y;
} dir[4] = {
                    {  0,  -1 },
        { -1,  0 },              {  1,  0 },
                    {  0,   1 },
           };

#define NUM     (4)             /*  設定為 4x4 的棋盤 */

int XX, YY;                     /*  棋盤的啟始位置 */
int turn = 1;
int width;
int d = 2, xx, yy;

int  table[NUM+2][NUM+2];       /*  棋盤的陣列 */






main()          /*    主程式   */
{
    int     gdriver = DETECT, gmode, errorcode;
    int     x, y, i, demo = 0;
    int     xmax, ymax;
    char    string[10];

#ifdef BGI
    registerbgidriver(EGAVGA_driver);
#endif

    initgraph(&gdriver, &gmode, "");    /*  啟動 Turbo C 的繪圖模式 */
    if ((errorcode = graphresult()) != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        return 1;
    }

    randomize();

    x = ((xmax = getmaxx()) - 50) / NUM;
    y = ((ymax = getmaxy()) - 50) / NUM;
    width = x < y ? x : y;
    XX    = (xmax - NUM * width) / 2;
    YY    = (ymax - NUM * width) / 2;

    do {
        if (demo) delay(1000);
        cleardevice();
        setfillstyle(SOLID_FILL, BackGround);
        bar(0, 0, xmax, ymax);

        init_table();           /*  新局，將棋盤初始化 */
        do {
            turn = (turn+1) % 2;        /* 換下一家 */
            if (moveable()) {
                if (player[turn].func())
                    break;
                eat();
            } else {
                player[turn].number = 0;
                turn = (turn + 1) % 2;
            }
        } while (player[1-turn].number);

        for (i = 1; i <= xmax/2/3-20; i++) {
            setfillstyle(SOLID_FILL, BoarCOLOR);
            bar(xmax/2 - i*3, ymax/2 - i, xmax/2 + i*3, ymax/2 + i);
        }
        sprintf(string, "%d : %d", player[0].number, player[1].number);
        setcolor(TextCOLOR);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
        outtextxy(XX+90, YY+width+30, string);


        outcpattern(XX+10, YY+width+110,
         player[player[0].number > player[1].number ? 0 : 1].message, 6, 3, 3);


        if (kbhit()) {
            switch(getch()) {
            case 'c' :
            case 'C' :
                player[0].func = comp_move;
                break;
            case 'r' :
            case 'R' :
                player[0].func = random_move;
                break;
            case 'd' :
            case 'D' :
                demo = 1;
                player[0].func = comp_move;
                break;
            default  :
                demo = 0;
                player[0].func = user_move;
            }
        }
    } while (demo || getch() != 27);

    closegraph();
    return 0;
}

void init_table()
{
    int  i, j;

    setfillstyle(SOLID_FILL, LineCOLOR);

    for (i = 0; i <= NUM; i++) {
        bar(XX+i*width-d, YY+d        , XX+i*width+d, YY+NUM*width-d);
        bar(XX+d        , YY+i*width-d, XX+NUM*width-d, YY+i*width+d);
    }

    for (j = 0; j < NUM + 2; j++) {
        for (i = 0; i < NUM + 2; i++) {
            if (i == 0 || j == 0 || i == NUM+1 || j == NUM+1) {
                table[i][j] = 3;
            } else {
                if (j == 1 || (j == 2 && (i == 1 || i == 4))) {
                    table[i][j] = 2;
                } else {
                    if (j == 4 || (j == 3 && (i == 1 || i == 4)))
                        table[i][j] = 1;
                    else
                        table[i][j] = 0;
                }
            }
        }
    }

    xx = yy = NUM/2;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            draw(i, j);

    player[0].number = player[1].number = 6;
}

int user_move()
{
    int   k, sel = 0, beep = 0;
    int   x = xx - 1, y = yy -1, ox, oy;

    setlinestyle(SOLID_LINE, 1, THICK_WIDTH);
    do {
         while (! kbhit()) {
             if (! sel) {
                 setcolor(CursCOLOR);
                 rectangle(XX+x*width+d+2,       YY+y*width+d+2,
                           XX+x*width+width-d-2, YY+y*width+width-d-2);
                 delay(30);
                 setcolor(BackGround);
                 rectangle(XX+x*width+d+2,       YY+y*width+d+2,
                           XX+x*width+width-d-2, YY+y*width+width-d-2);
                 delay(30);
             }
         }

         ox = x;
         oy = y;

         switch(k = getch()) {
         case 72:  /* up    */
             if (sel)
                 y--;
             else
                 y = (y + NUM - 1) % NUM;
             break;
         case 80:  /* down  */
             if (sel)
                 y++;
             else
                 y = (y + 1) % NUM;
             break;
         case 75:  /* left  */
             if (sel)
                 x--;
             else
                 x = (x + NUM - 1) % NUM;
             break;
         case 77:  /* right */
             if (sel)
                 x++;
             else
             x = (x + 1) % NUM;
             break;
         case '\r' :
         case ' '  :
             if (sel) {
                 sel = 0;
                 setcolor(BackGround);
                 rectangle(XX+x*width+d+2,       YY+y*width+d+2,
                           XX+x*width+width-d-2, YY+y*width+width-d-2);
                 x = xx - 1;
                 y = yy - 1;
                 break;
             }
             xx = x + 1;
             yy = y + 1;
             if (table[xx][yy] == turn+1) {
                  sel = 1;
                  setcolor(CursCOLOR);
                  rectangle(XX+x*width+d+2,       YY+y*width+d+2,
                            XX+x*width+width-d-2, YY+y*width+width-d-2);
             } else {
                  beep = 1;
                  k = 0;
             }
             break;
         case 27  :
             return 1;
         }

         if (sel) {
             switch (k) {
             case 72:  /* up    */
             case 80:  /* down  */
             case 75:  /* left  */
             case 77:  /* right */
                 if (table[x+1][y+1] == 0) {
                     setcolor(BackGround);
                     rectangle(XX+(xx-1)*width+d+2,       YY+(yy-1)*width+d+2,
                               XX+(xx-1)*width+width-d-2, YY+(yy-1)*width+width-d-2);
                     sel++;
                     table[xx][yy] = 0;
                     draw(xx, yy);
                     xx = x + 1;
                     yy = y + 1;
                     table[xx][yy] = turn+1;
                     draw(xx, yy);
                 } else {
                     x = ox;
                     y = oy;
                     beep = 1;
                 }
             }
         }
         if (beep) {
             sound(40);
             delay(150);
             nosound();
             beep = 0;
         }
    } while (sel < 2);

    return 0;
}

int comp_move()
{
    int   d;

    if (! eat_move(&d))
        return random_move();

    table[xx-dir[d].x][yy-dir[d].y] = 0;
    draw(xx-dir[d].x, yy-dir[d].y);
    table[xx][yy] = turn+1;
    draw(xx, yy);

    return 0;
}

int eat_move(int *direction)
{
    int   i, j, k, x, y;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            if (table[i][j] == turn+1)
                for (k = 0; k < 4; k++)
                    if (table[i+dir[k].x][j+dir[k].y] == 0) {
                        table[i][j] = 0;
                        xx = i+dir[k].x;
                        yy = j+dir[k].y;
                        table[xx][yy] = turn+1;
                        x = xx;
                        y = yy;
                        if (eatable(&x, &y, turn)) {
                            *direction = k;
                            return 1;
                        }
                        table[xx][yy] = 0;
                        table[i][j] = turn+1;
                    }
    return 0;
}

int safty()
{
    int   i, j, k, m, x, y, x1, y1;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            if (table[i][j] == 2-turn)
                for (k = 0; k < 4; k++)
                    if (table[i+dir[k].x][j+dir[k].y] == 0) {
                        table[i][j] = 0;
                        x1 = x = i+dir[k].x;
                        y1 = y = j+dir[k].y;
                        table[x1][y1] = 2-turn;
                        m = eatable(&x, &y, 1-turn);
                        table[x1][y1] = 0;
                        table[i][j] = 2-turn;
                        if (m)
                            return 0;
                    }
    return 1;
}

int random_move()
{
    int   idx, scount = 0;
    int   i, j, k;

    while (1) {
        do {
            do {
                xx = random(NUM) + 1;
                yy = random(NUM) + 1;
            } while(table[xx][yy] != turn+1);
        } while(! check(xx, yy));

        do {
             idx = random(4);
        } while(table[xx+dir[idx].x][yy+dir[idx].y] != 0);

        table[xx][yy] = 0;
        xx += dir[idx].x;
        yy += dir[idx].y;
        table[xx][yy] = turn+1;


        if (safty() || scount > RNDCNT) break;


        table[xx][yy] = 0;
        xx -= dir[idx].x;
        yy -= dir[idx].y;
        table[xx][yy] = turn+1;

        if (scount++ == RNDCNT) {
            for (i = 1; i <= NUM; i++) {
                for (j = 1; j <= NUM; j++) {
                    if (table[i][j] == turn+1) {
                        for (k = 0; k < 4; k++) {
                            if (table[i+dir[k].x][j+dir[k].y] == 0) {
                                xx = i+dir[k].x;
                                yy = j+dir[k].y;
                                table[xx][yy] = turn+1;;
                                table[i][j] = 0;
                                if (safty()) {
                                    draw(xx, yy);
                                    draw(i, j);
                                    return 0;
                                }
                                table[i][j] = turn+1;
                                table[xx][yy] = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    draw(xx, yy);
    draw(xx-dir[idx].x, yy-dir[idx].y);

    return 0;
}

void eat()
{
    int   i;

    for (i = 0; i < 4; i++) {
        if (table[xx+dir[i].x][yy+dir[i].y] == turn + 1) {
            if (table[xx+2*dir[i].x][yy+2*dir[i].y] == 2 - turn) {
                if (table[xx+3*dir[i].x][yy+3*dir[i].y] == 0 ||
                    table[xx-dir[i].x][yy-dir[i].y] == 0) {
                    table[xx+2*dir[i].x][yy+2*dir[i].y] = 0;
                    draw(xx+2*dir[i].x, yy+2*dir[i].y);
                    player[1-turn].number--;
                }
            }
        }
        if (table[xx+dir[i].x][yy+dir[i].y] == 2 - turn) {
            if (table[xx-dir[i].x][yy-dir[i].y] == turn + 1) {
                if (table[xx+2*dir[i].x][yy+2*dir[i].y] == 0 ||
                    table[xx-2*dir[i].x][yy-2*dir[i].y] == 0) {
                    table[xx+dir[i].x][yy+dir[i].y] = 0;
                    draw(xx+dir[i].x, yy+dir[i].y);
                    player[1-turn].number--;
                }
            }
        }
    }
}

int eatable(int *x, int *y, int who)
{
    int   i;

    for (i = 0; i < 4; i++) {
        if (table[*x+dir[i].x][*y+dir[i].y] == who + 1) {
            if (table[*x+2*dir[i].x][*y+2*dir[i].y] == 2 - who) {
                if (table[*x+3*dir[i].x][*y+3*dir[i].y] == 0 ||
                    table[*x-dir[i].x][*y-dir[i].y] == 0) {
                        *x = *x + 2*dir[i].x;
                        *y = *y + 2*dir[i].y;
                        return 1;
                }
            }
        }
        if (table[*x+dir[i].x][*y+dir[i].y] == 2 - who) {
            if (table[*x-dir[i].x][*y-dir[i].y] == who + 1) {
                if (table[*x+2*dir[i].x][*y+2*dir[i].y] == 0 ||
                    table[*x-2*dir[i].x][*y-2*dir[i].y] == 0) {
                        *x = *x + dir[i].x;
                        *y = *y + dir[i].y;
                        return 1;
                }
            }
        }
    }
    return 0;
}

void draw(int x, int y)
{
    setcolor(BackGround);
    setfillstyle(SOLID_FILL, table[x][y]==0 ? BackGround :
                             table[x][y]==1 ? UserCOLOR : CompCOLOR);
    fillellipse(XX+(x-1)*width+d+(width-d)/2,
                YY+(y-1)*width+d+(width-d)/2,
                (width-d)/2-3, (width-d)/2-3);
}

int moveable()
{
    int   i, j, k;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            if (table[i][j] == turn+1)
                for (k = 0; k < 4; k++)
                    if (table[i+dir[k].x][j+dir[k].y] == 0)
                        return 1;

    return 0;
}

int check(int x, int y)
{
    int   k;
    for (k = 0; k < 4; k++)
        if (table[x+dir[k].x][y+dir[k].y] == 0)
                return 1;
    return 0;
}


void outcpattern(int x, int y, char *msg, int len, int xs, int ys)
{
    int  i, j, k, js, ks, m;
    char c;

    for (i = 0; i < len; i++) {
        for (j = 0; j < 24; j++) {
            for (js = 0; js < ys; js++) {
                for (k = 0; k < 3; k++) {
                    for (m = 0, c = *(msg+(i*24+j)*3+k); m < 8; m++) {
                        if (((c >> (7-m)) & 0x01) != 0) {
                            for (ks = 0; ks < xs; ks++) {
                                putpixel(x+(24*i+k*8+m)*xs+ks, y+j*ys+js, getcolor());
                            }
                        }
                    }
                }
            }
        }
    }
}
