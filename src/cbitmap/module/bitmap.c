#include "bitmap.h"

Bitmap *BitmapCreate(u8 size) {
  u8 real_size = size / 8 + 1;
  Bitmap *b = calloc(1, sizeof(Bitmap) + sizeof(u1) * real_size);
  b->size = real_size;
  b->ele_size = size;
  return b;
}

int BitmapGet(Bitmap *b, u8 n) {
  u8 offset = n % 8;
  u8 count = n / 8;
  if (count >= b->size)
    return false;
  u1 offset_number = (1 << offset);
  if ((b->buff[count] & offset_number) == offset_number) {
    return true;
  }
  return false;
}

void BitmapSet(Bitmap *b, u8 n) {
  u8 offset = n % 8;
  u8 count = n / 8;
  b->buff[count] = b->buff[count] | (1 << offset);
}

void BitmapDelete(Bitmap *b, u8 n) {
  u8 offset = n % 8;
  u8 count = n / 8;
  b->buff[count] = b->buff[count] & (~(1 << offset));
}

u8 BitmaLen(Bitmap* b){
    return b->ele_size;
}


void BitmapFree(Bitmap *b) {
  if (b) {
    free(b);
  }
}

void BitmapDump(Bitmap *b, char *path) {
  FILE *fp = fopen(path, "wb");
  fwrite(&b->size, sizeof(u8), 1, fp);
  fwrite(&b->ele_size, sizeof(u8), 1, fp);
  fwrite(b->buff, sizeof(u1), b->size, fp);
  fclose(fp);
}

Bitmap *BitmapLoad(char *path) {
  u8 size = 0, ele_size = 0;
  FILE *fp = fopen(path, "rb");
  fread(&size, sizeof(u8), 1, fp);
  fread(&ele_size, sizeof(u8), 1, fp);
  Bitmap *b = BitmapCreate(ele_size);
  fread(b->buff, sizeof(u1), size, fp);
  fclose(fp);
  return b;
}
