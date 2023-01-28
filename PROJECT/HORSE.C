/*  賽馬程式 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>

#include "etfont.h"

#define XX      (80)            /*  畫面的啟始位置 */
#define YY      (50)
#define HORSE   ( 8)            /*  跑道數  */
#define BLK_W   (20)            /*  馬的造形的寬度 */
#define BLK_H   (20)            /*  馬的造形的高度 */
#define FRAME   (4)
#define TITLE   (80)

#define BackGround  (WHITE)

#pragma warn -pin

int pattern[FRAME][BLK_H][BLK_W] = {   /*  馬的造形 */
                            {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
         0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
         0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
         0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
         0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                               },
                               {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
         0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
         0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                               },
                               {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
         0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
         0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
         0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
         0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
         0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                               },
                               {
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1,
         0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
         0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
         0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                            },
                             };



struct _horse {         /* 馬匹的資料結構 */
    int  pos;           /* 馬匹的位置 */
    int  sel;           /* 造形 */
    int  arr;           /* 名次 */
    int  bet;           /* 下注 */
} horse[HORSE];

void draw_horse(int x, int y, int sel, int color);   /* 畫馬的副程式 */
int  money = 1000;

main()
{
    int     gdriver = DETECT, gmode, errorcode;
    int     xmax, ymax;
    int     i, j, k, over, win;
    char    *str = "                  ";

    if (! etfont_init("c:/et3")) {
         printf("Can not initialize ET font system\n");
         return 1;
    }



#ifdef BGI
    registerbgidriver(EGAVGA_driver);
#endif

    initgraph(&gdriver, &gmode, "");            /* 啟動 Turbo C 的繪圖模式 */
    if ((errorcode = graphresult()) != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        return 1;
    }


    xmax = getmaxx();                   /* 畫場地 */
    ymax = getmaxy();

    randomize();                /*  亂數初始化  */

    while (money > 0) {
        cleardevice();
        setfillstyle(SOLID_FILL, BackGround);
        bar(0, 0, xmax, ymax);
        setcolor(RED);
        line(0,0,xmax,0);
        line(0,0,0,ymax);
        line(xmax,0,xmax,ymax);
        line(0,ymax,xmax,ymax);

//      setcolor(LIGHTBLUE);
//      outctextxy(10, 10, "馬 場 大 亨");

        setcolor(GREEN);
        setlinestyle(SOLID_LINE, 1, THICK_WIDTH);
        for (i = 0; i <= HORSE; i++) {
            line (XX, i * (ymax - TITLE) / HORSE + TITLE - 5,
                  xmax - 10, i * (ymax - TITLE) / HORSE + TITLE - 5);
            if (i != HORSE) {
                sprintf(str, "%2d", i);
                setcolor(BROWN);
                outctextxy(100, i*(ymax-TITLE)/HORSE+TITLE+10, str);
            }
        }
        setcolor(LIGHTCYAN);
        line(xmax-60, TITLE-5, xmax-60, ymax - 5);

        for (i = 0; i < HORSE; i++) {       /* 馬匹資料的初始化 */
            horse[i].pos = XX;
            horse[i].sel = 0;
            horse[i].arr = 0;
            horse[i].bet = 0;
            draw_horse(horse[i].pos, i*(ymax-TITLE)/HORSE+TITLE+5, horse[i].sel, i+1);
        }
        setcolor(BROWN);
        sprintf(str, "現   金:%6d", money);
        outctextxy(5, 10, str);
        outctextxy(5, 40, "下   注");

        do {
            j = (k = getch()) - '1';
            if (j >= 0 && j < HORSE) {
                setcolor(BackGround);
                sprintf(str, "%2d", horse[j].bet);
                outctextxy(horse[j].pos-60, j*(ymax-TITLE)/HORSE+TITLE+10, str);
                sprintf(str, "現   金:%6d", money);
                outctextxy(5, 10, str);
                horse[j].bet += 10;
                money -= 10;
                sprintf(str, "%2d", horse[j].bet);
                setcolor(BROWN);
                outctextxy(horse[j].pos-60, j*(ymax-TITLE)/HORSE+TITLE+10, str);
                sprintf(str, "現   金:%6d", money);
                outctextxy(5, 10, str);
            }
        } while (k != ' ');

        over = 0;
        do {
            i = random(HORSE);      /*  選擇馬匹  */
            if (horse[i].pos > xmax - 75) {         /* 判繼是否到達終點 */
                if (! horse[i].arr) {
                    char string[] = "     ";
                    sprintf(string, "%2d", ++over);
                    setcolor(BROWN);
//                  settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
//                  outtextxy(horse[i].pos-50, (i+1)*(ymax-YY-20)/HORSE+25, string);
                    outctextxy(horse[i].pos-50, i*(ymax-TITLE)/HORSE+TITLE+10, string);
                    if ((horse[i].arr = over) == 1) {
                        win = i;
                    }
                }
            } else {
                horse[i].pos += 2;
                horse[i].sel = ++horse[i].sel % FRAME;
                draw_horse(horse[i].pos, i*(ymax-TITLE)/HORSE+TITLE+5, horse[i].sel, i+1);
            }
        } while(over != HORSE);

        setfillstyle(SOLID_FILL, BLUE);
        bar(xmax/2 - 100, ymax/2 - 20, xmax/2 + 100, ymax/2 +20);

        setcolor(YELLOW);
        if (horse[win].bet != 0) {
            sprintf(str, "您贏了 %d", horse[win].bet * HORSE);
            outctextxy(xmax/2 - 100 + 5, ymax/2 - 20 + 5, str);
            money += horse[win].bet * HORSE;
        } else {
            outctextxy(xmax/2 - 100 + 5, ymax/2 - 20 + 5,
                     "抱歉! 您輸了");
        }
        if (getch() == 27)
            break;
    }

    getch();

    etfont_close();
    closegraph();
    return 0;
}

void draw_horse(int x, int y, int sel, int color)
{
    int  i, j;

    for (j = y; j < y+BLK_H; j++)
        for (i = x; i < x+ BLK_W; i++)
            putpixel(i, j, pattern[sel][j-y][i-x] == 1 ? color : BackGround);
}

/* 工作：
 *       一、把馬匹的造形改大一點，並畫大一點。
 *       二、配合課本資料，加入押注程式。
 *       三、加入音效程式。
 */
