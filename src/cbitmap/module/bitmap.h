#include <stdlib.h>
#include <stdio.h>

#define u1 unsigned char
#define u8 unsigned long long
#define false 0
#define true 1

typedef struct {
  u8 size;
  u8 ele_size;
  u1 buff[];
} Bitmap;


Bitmap* BitmapCreate(u8 size);
int BitmapGet(Bitmap *b, u8 n);
void BitmapSet(Bitmap *b, u8 n);
void BitmapDelete(Bitmap *b, u8 n);
u8 BitmaLen(Bitmap* b);
void BitmapFree(Bitmap *b);
void BitmapDump(Bitmap *b, char *path);
Bitmap *BitmapLoad(char *path);
