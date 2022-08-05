# cython: language_level=3
# distutils: sources = src/cbitmap/module/bitmap.c
# distutils: include_dirs = src/cbitmap/module/

cimport cbitmap

cdef class Bitmap:

    cdef cbitmap.Bitmap* _bitmap

    def __cinit__(self, unsigned long long size):
        self._bitmap = NULL
        if size > 0:
            self._bitmap = cbitmap.BitmapCreate(size)

    def __dealloc__(self):
        if self._bitmap is not NULL:
            cbitmap.BitmapFree(self._bitmap)
        self._bitmap = NULL

    cpdef bint _get(self, unsigned long long n):
        return cbitmap.BitmapGet(self._bitmap, n)

    cpdef _set(self, unsigned long long n):
        cbitmap.BitmapSet(self._bitmap, n)

    cpdef _delete(self, unsigned long long n):
        cbitmap.BitmapDelete(self._bitmap, n)

    cpdef _load(self, char* path):
        b = Bitmap(0)
        b._bitmap = cbitmap.BitmapLoad(path)
        return b
    
    cpdef _dump(self, char* path):
        cbitmap.BitmapDump(self._bitmap, path)

    def __len__(self):
        return cbitmap.BitmaLen(self._bitmap)

    def __bool__(self):
        return bool(len(self))
