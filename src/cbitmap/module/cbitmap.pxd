cdef extern from "bitmap.h":
    ctypedef struct Bitmap:
        pass

    Bitmap* BitmapCreate(unsigned long long size)
    bint BitmapGet(Bitmap *b, unsigned long long n)
    void BitmapSet(Bitmap *b, unsigned long long n)
    void BitmapDelete(Bitmap *b, unsigned long long n)
    unsigned long long BitmapLen(Bitmap* b)
    void BitmapFree(Bitmap *b)
    void BitmapDump(Bitmap *b, char *path)
    Bitmap *BitmapLoad(char *path)
    void BitmapSetKmers(Bitmap *b, char *seq, unsigned long long kmer_size)
