#ifndef __ETFONT_H
#define __ETFONT_H

int  etfont_init(char *path);
void etfont_close(void);
void outccharxy(int xp, int yp, int code);
void outctextxy(int xp, int yp, char *string);

#endif
