from unittest import TestCase
from cbitmap import Bitmap
import os

class BitmapTest(TestCase):

    @staticmethod
    def init_bitmap_by_size(size):
        return Bitmap(size)
    
    @staticmethod
    def init_bitmap_by_path(path):
        return Bitmap(1).load(path)

    def test_len(self):
        b = self.init_bitmap_by_size(10)
        self.assertEqual(10, len(b))
        del b
    
    def test_load_and_dump(self):
        b = self.init_bitmap_by_size(10)
        b.dump('data')
        del b
        b = self.init_bitmap_by_path('data')
        self.assertEqual(10, len(b))
        os.remove('data')
        del b

    def test_set_and_get_and_delete(self):
        b = self.init_bitmap_by_size(20)
        ret1 = []
        ret2 = []
        ret3 = []
        for i in range(10):
            b.set(i)
        
        for i in range(10):
            ret1.append(b.get(i))

        for i in range(10, 20):
            ret2.append(b.get(i))
        
        for i in range(5):
            b.delete(i)

        for i in range(5):
            ret3.append(b.get(i))

        del b
        ret1 = all(ret1)
        ret3 = not any(ret3)
        ret2 = not any(ret2)
        self.assertTrue(ret1 is True)
        self.assertTrue(ret2 is True)
        self.assertTrue(ret3 is True)
