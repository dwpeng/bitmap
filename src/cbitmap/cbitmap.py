import os
import bitmap

_Bitmap = bitmap.Bitmap

UINT8_MAX = 255
UINT16_MAX = 65535
UINT32_MAX = 4294967295

class Bitmap():

    def __init__(self, size=0):
        assert size >= 0
        self._bitmap = None
        if size > 0:
            self._bitmap = _Bitmap(size)
        self._len = size

    def load(self, path):
        if not os.path.exists(path):
            raise FileNotFoundError("File not found in %s. Please check it again." % path)
        b = Bitmap()
        b._bitmap = self._bitmap._load(path.encode('utf-8'))
        b._len = len(b._bitmap)
        return b

    def get(self, n):
        assert type(n) is int  and n >= 0
        return self._bitmap._get(n)
    
    def set(self, n):
        assert type(n) is int  and n >= 0
        return self._bitmap._set(n)
    
    def delete(self, n):
        assert type(n) is int  and n >= 0
        return self._bitmap._delete(n)

    def dump(self, path):
        return self._bitmap._dump(path.encode('utf-8'))

    def __len__(self):
        return len(self._bitmap)

    def __str__(self):
        return '<Bitmap %d>' % len(self)
