#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

#include "etfont.h"

static unsigned char table[]={128,64,32,16,8,4,2,1};
static unsigned char pat[72];
static int           ffont24 = 0, hfont24 = 0;
static int           csizex=1, csizey=1;
static const char    *std24 = "/stdfont.24";
static const char    *asc24 = "/ascfont.24";

int etfont_init(char *path)
{
    char  *std, *asc;
    std = malloc(strlen(path) + strlen(std24) + 1);
    asc = malloc(strlen(path) + strlen(asc24) + 1);
    strcpy(std, path);
    strcpy(&std[strlen(path)], std24);
    strcpy(asc, path);
    strcpy(&asc[strlen(path)], asc24);
    ffont24 = open(std, O_RDONLY|O_BINARY);
    hfont24 = open(asc, O_RDONLY|O_BINARY);

    return (ffont24 != -1 && hfont24 != -1) ? 1 : 0;
}

void etfont_close(void)
{
    close(ffont24);
}

static int chcode(unsigned char hbp, unsigned char lbp)
{
    int   codep;
    int   lt, ht;

    lt = (int)(lbp);
    ht = (int)(hbp);

    if (ht < 129) {
        codep = ht;
    } else {
        if (ht < 164) {
            codep = 157 * (ht - 161) + lt - 64;
        } else {
            if (lt > 161)
                lt -= 34;

            codep = 157 * (ht - 164) + lt - 64;

            if (codep >= 5809)
               codep -= 408;
        }
    }
    return(codep);
}

static void drawchar(int xp, int yp, int kindp)
{
    char i, j, k, l, m;

    for (i = 0; i < 24; i++)
        for (j = 0; j < kindp; j++)
            for (k = 0; k < 8; k++)
                if ((pat[i * kindp + j] & table[k]) != 0)
                    for (l = 0; l < csizex; l++)
                        for (m = 0; m < csizey; m++)
                            putpixel(xp + (j * 8 + k) * csizex + l,
                                     yp + i * csizey + m,
                                     getcolor());
}

static void ffont24disp(unsigned char hbp, unsigned char lbp, int xp, int yp)
{
   lseek(ffont24, 72L * (long) (chcode(hbp, lbp)), SEEK_SET);
   read (ffont24, pat, 72);
   drawchar(xp, yp, 3);
}

static void hfont24disp(unsigned char bp, int xp, int yp)
{
   lseek(hfont24, 48L * (long) bp, SEEK_SET);
   read (hfont24, pat, 48);
   drawchar(xp, yp, 2);
}

void outccharxy(int xp, int yp, int code)
{
    ffont24disp((char) (code >> 8) & 0xFF, (char) code & 0xFF, xp, yp);
}

void outctextxy(int xp, int yp, char *string)
{
    unsigned char *ptr = (unsigned char *) string;

    while (*ptr != '\0') {
        if (*ptr > 127) {
            ffont24disp(*ptr, *(ptr+1), xp, yp);
            ptr += 2;
            xp += 24;
        } else {
            hfont24disp(*ptr, xp, yp);
            ptr++;
            xp += 12;
        }
    }
}
