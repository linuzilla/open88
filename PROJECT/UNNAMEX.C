/*  無名棋程式 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <graphics.h>
#include <time.h>

#define RNDCNT (10)


int  user_move(void);
int  comp_move(void);
void init_table(void);
void eat(void);
void draw(int x, int y);
int  moveable(void);
int  check(int x, int y);
int  random_move(void);
int  eat_move(int *);
int  safty(int trn);
int  eatable(int *x, int *y, int who);

struct _player {
     char *message;
     int  (*func)(void);
     int  number;
} player[2] = {
                 { "You win",  user_move, 6 },
                 { "You Lost", comp_move, 6 }
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
#define SELF    (turn+1)
#define OTHER   (2-turn)



main()          /*    主程式   */
{
    int     gdriver = DETECT, gmode, errorcode;
    int     x, y;
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
        cleardevice();
        setfillstyle(SOLID_FILL, WHITE);
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

        sprintf(string, "%d : %d", player[0].number, player[1].number);
        setcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
        outtextxy(XX+10, YY+width+ 40, string);

        if (player[0].number != player[1].number) {
            outtextxy(XX+10, YY+width+200,
             player[player[0].number > player[1].number ? 0 : 1].message);
        }
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
            default  :
                player[0].func = user_move;
            }
        }
    } while (getch() != 27);

    closegraph();
    return 0;
}

void init_table()
{
    int  i, j;

    setfillstyle(SOLID_FILL, GREEN);

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
                 setcolor(BLACK);
                 rectangle(XX+x*width+d+2,       YY+y*width+d+2,
                           XX+x*width+width-d-2, YY+y*width+width-d-2);
                 delay(30);
                 setcolor(WHITE);
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
                 setcolor(WHITE);
                 rectangle(XX+x*width+d+2,       YY+y*width+d+2,
                           XX+x*width+width-d-2, YY+y*width+width-d-2);
                 x = xx - 1;
                 y = yy - 1;
                 break;
             }
             xx = x + 1;
             yy = y + 1;
             if (table[xx][yy] == SELF) {
                  sel = 1;
                  setcolor(BLACK);
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
                     setcolor(WHITE);
                     rectangle(XX+(xx-1)*width+d+2,       YY+(yy-1)*width+d+2,
                               XX+(xx-1)*width+width-d-2, YY+(yy-1)*width+width-d-2);
                     sel++;
                     table[xx][yy] = 0;
                     draw(xx, yy);
                     xx = x + 1;
                     yy = y + 1;
                     table[xx][yy] = SELF;
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
    table[xx][yy] = SELF;
    draw(xx, yy);

    return 0;
}

int eat_move(int *direction)
{
    int   i, j, k, x, y;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            if (table[i][j] == SELF)
                for (k = 0; k < 4; k++)
                    if (table[i+dir[k].x][j+dir[k].y] == 0) {
                        table[i][j] = 0;
                        xx = i+dir[k].x;
                        yy = j+dir[k].y;
                        table[xx][yy] = SELF;
                        x = xx;
                        y = yy;
                        if (eatable(&x, &y, turn)) {
                            setfillstyle(SOLID_FILL, WHITE);
                            bar(5, 5, 200, 20);
                            setcolor(BLACK);
                            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                            outtextxy(5, 5, "Eat   move");
                            *direction = k;
                            return 1;
                        }
                        table[xx][yy] = 0;
                        table[i][j] = SELF;
                    }
    return 0;
}

int safty(int trn)
{
    int   i, j, k, m, x, y, x1, y1;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            if (table[i][j] == 2-trn)
                for (k = 0; k < 4; k++)
                    if (table[i+dir[k].x][j+dir[k].y] == 0) {
                        table[i][j] = 0;
                        x1 = x = i+dir[k].x;
                        y1 = y = j+dir[k].y;
                        table[x1][y1] = 2-trn;
                        m = eatable(&x, &y, 1-trn);
                        table[x1][y1] = 0;
                        table[i][j] = 2-trn;
                        if (m)
                            return 0;
                    }
    return 1;
}

int random_move()
{
    int   idx, scount = 0;
    int   i, j, k, danger = 0;

    while (1) {
        do {
            do {
                xx = random(NUM) + 1;
                yy = random(NUM) + 1;
            } while(table[xx][yy] != SELF);
        } while(! check(xx, yy));

        do {
             idx = random(4);
        } while(table[xx+dir[idx].x][yy+dir[idx].y] != 0);

        table[xx][yy] = 0;
        xx += dir[idx].x;
        yy += dir[idx].y;
        table[xx][yy] = SELF;


//      if (safty(turn) || scount > RNDCNT) break;
        if (safty(turn)) {
            setfillstyle(SOLID_FILL, WHITE);
            bar(5, 5, 200, 20);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setcolor(BLACK);
            outtextxy(5, 5, "r-s   move");
            break;
        }
        if (scount > RNDCNT) {
/*
            setfillstyle(SOLID_FILL, WHITE);
            bar(5, 5, 200, 20);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            setcolor(BLACK);
            outtextxy(5, 5, "DangerMove");
*/
            danger = 1;
            break;
        }


        table[xx][yy] = 0;
        xx -= dir[idx].x;
        yy -= dir[idx].y;
        table[xx][yy] = SELF;

        if (scount++ == RNDCNT) {
            for (i = 1; i <= NUM; i++) {
                for (j = 1; j <= NUM; j++) {
                    if (table[i][j] == SELF) {
                        for (k = 0; k < 4; k++) {
                            if (table[i+dir[k].x][j+dir[k].y] == 0) {
                                xx = i+dir[k].x;
                                yy = j+dir[k].y;
                                table[xx][yy] = SELF;;
                                table[i][j] = 0;
                                if (safty(turn)) {
                                    draw(xx, yy);
                                    draw(i, j);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    bar(5, 5, 200, 20);
                                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                                    setcolor(BLACK);
                                    outtextxy(5, 5, "Safty move");
                                    return 0;
                                }
                                table[i][j] = SELF;
                                table[xx][yy] = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    if (danger) { // prepare to kill
        int   sx = xx, sy = yy;

        for (i = 1; i <= NUM; i++) {
            for (j = 1; j <= NUM; j++) {
                if (table[i][j] == SELF) {
                    for (k = 0; k < 4; k++) {
                        if (table[i+dir[k].x][j+dir[k].y] == 0) {
                            xx = i+dir[k].x;
                            yy = j+dir[k].y;
                            table[xx][yy] = SELF;
                            table[i][j] = 0;
                            if (! safty(1-turn)) {
                                draw(xx, yy);
                                draw(i, j);
                                setfillstyle(SOLID_FILL, WHITE);
                                bar(5, 5, 200, 20);
                                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                                setcolor(BLACK);
                                outtextxy(5, 5, "P-K   move");
                                return 0;
                            }
                            table[i][j] = SELF;
                            table[xx][yy] = 0;
                        }
                    }
                }
            }
        }
        setfillstyle(SOLID_FILL, WHITE);
        bar(5, 5, 200, 20);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(BLACK);
        outtextxy(5, 5, "DangerMove");
        xx = sx;
        yy = sy;
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
            if (table[xx+2*dir[i].x][yy+2*dir[i].y] == OTHER) {
                if (table[xx+3*dir[i].x][yy+3*dir[i].y] == 0 ||
                    table[xx-dir[i].x][yy-dir[i].y] == 0) {
                    table[xx+2*dir[i].x][yy+2*dir[i].y] = 0;
                    draw(xx+2*dir[i].x, yy+2*dir[i].y);
                    player[1-turn].number--;
                }
            }
        }
        if (table[xx+dir[i].x][yy+dir[i].y] == OTHER) {
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
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, table[x][y]==0 ? WHITE :
                             table[x][y]==1 ? LIGHTBLUE : BLACK);
    fillellipse(XX+(x-1)*width+d+(width-d)/2,
                YY+(y-1)*width+d+(width-d)/2,
                (width-d)/2-3, (width-d)/2-3);
}

int moveable()
{
    int   i, j, k;

    for (i = 1; i <= NUM; i++)
        for (j = 1; j <= NUM; j++)
            if (table[i][j] == SELF)
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
