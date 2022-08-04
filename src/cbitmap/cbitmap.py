import os
import bitmap as cbitmap

UINT8_MAX = 255
UINT16_MAX = 65535
UINT32_MAX = 4294967295

class _Bitmap:

    def __init__(self, bitmap_ptr):
        self._bitmap_ptr = bitmap_ptr
    
    def _dump(self, path):
        return cbitmap.dump(self._bitmap_ptr, path)

    def _get(self, n):
        assert type(n) is int
        return cbitmap.get(self._bitmap_ptr, n)

    def _set(self, n):
        assert type(n) is int
        return cbitmap.set(self._bitmap_ptr, n)

    def __len__(self):
        if self._bitmap_ptr:
            return cbitmap.len(self._bitmap_ptr)
        return 0

    def __enter__(self):
        return self

    def __exit__(self, *args):
        if self._bitmap_ptr:
            cbitmap.destory(self._bitmap_ptr)
        self._bitmap_ptr = None

    def __del__(self):
        if self._bitmap_ptr:
            cbitmap.destory(self._bitmap_ptr)
        self._bitmap_ptr = None

class Bitmap():

    def __init__(self, size=UINT16_MAX):
        assert size >= 0
        self._bitmap = None
        if size > 0:
            self._bitmap = _Bitmap(cbitmap.create(size))
        self._len = size

    @staticmethod
    def load(path):
        if not os.path.exists(path):
            raise FileNotFoundError("File not found in %s. Please check it again." % path)
        b = Bitmap(0)
        b._bitmap = _Bitmap(cbitmap.load(path))
        b._len = len(b._bitmap)
        return b

    def get(self, n):
        return getattr(self._bitmap, '_get')(n)
    
    def set(self, n):
        return getattr(self._bitmap, '_set')(n)
    
    def dump(self, path):
        assert type(path) is str
        return getattr(self._bitmap, '_dump')(path)

    def __len__(self):
        return self._len

    def __str__(self):
        return '<Bitmap %d>' % len(self)

    def __del__(self):
        del self._bitmap
