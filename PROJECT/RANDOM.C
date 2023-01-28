#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dos.h>
#include <graphics.h>

#include "freq.h"

static int mptr = 0;

static int music[] = {
               o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8,
               o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o61,l8,o57,l8,
               o56,l4,rest,l4,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8,
               o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o61,l8,o57,l8,
               o56,l4,rest,l8,o57,l8,o61,l8,o62,l8,
               o63,l4,rest,l8,o55,l8,o64,l8,o63,l8,
               o62,l4,rest,l8,o54,l8,o63,l8,o62,l8,
               o61,l4,rest,l8,o53,l8,o62,l8,o61,l8,
               o57,l4,o63,l8,o43,l8,o53,l8,o53,l8,
               o63,l8,o53,l8,o63,l8,o52u,l8,o53,l8,o52u,l8,
               o53,l8,o52u,l8,o53,l8,o62u,l8,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8,
               o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o61,l8,o57,l8,
               o56,l4,rest,l8,o57,l8,o61,l8,o62,l8,
               o63,l4,rest,l8,o55,l8,o64,l8,o63,l8,
               o62,l4,rest,l8,o54,l8,o63,l8,o62,l8,
               o61,l4,rest,l8,o53,l8,o62,l8,o61,l8,
               o57,l4,o63,l8,o43,l8,o53,l8,o53,l8,
               o63,l8,o53,l8,o63,l8,o52u,l8,o53,l8,o52u,l8,
               o53,l8,o52u,l8,o53,l8,o62u,l8,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o55u,l8,o57,l8,
               o61,l4,rest,l8,o53,l8,o63,l8,o62u,l8,
               o63,l8,o62u,l8,o63,l8,o57,l8,o62,l8,o61,l8,
               o56,l4,rest,l8,o51,l8,o53,l8,o56,l8,
               o57,l4,rest,l8,o53,l8,o61,l8,o57,l8,o56,l2_5,
               repeat
                     };


void   interrupt play_music(void);
void   interrupt (*int08svc)(void);
static int freq = 0, leng = 0;

main()
{
    int     gdriver = DETECT, gmode, errorcode;
    int     xmax, ymax, x[3], y[3];
    int     i, point, colors;


#ifdef BGI
    registerbgidriver(EGAVGA_driver);
#endif

    initgraph(&gdriver, &gmode, "");
    if ((errorcode = graphresult()) != grOk) {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        exit(1);
    }

    int08svc = getvect(0x08);
    setvect(0x08, play_music);

    colors  = getmaxcolor();
    randomize();
    x[0] = random(xmax = getmaxx());
    y[0] = random(ymax = getmaxy());
    x[1] = random(xmax);
    y[1] = random(ymax);

    do {
        while(! kbhit()){
            x[2] = x[1];
            y[2] = y[1];
            x[1] = x[0];
            y[1] = y[0];
            x[0] = random(xmax);
            y[0] = random(ymax);
            point  = 25 + random(25) + random(25);
            setcolor(random(colors + 1));
            for (i = 0; i <= point; i++) {
                line(x[2]+i*(x[1]-x[2])/point,y[2]+i*(y[1]-y[2])/point,
                     x[1]+i*(x[0]-x[1])/point,y[1]+i*(y[0]-y[1])/point);
                delay(30);
            }
        }
        cleardevice();
    } while(getch() != 27);


    closegraph();

    setvect(0x08, int08svc);
    nosound();
    return 0;
}


void interrupt play_music()
{
    int08svc();

    if (leng-- == 0) {
        nosound();
        freq = music[mptr++];
        leng = music[mptr++];
        if (freq != rest)
            sound(freq);
        if (music[mptr] == repeat)
            mptr = 0;
    }
}
