from shmem4py import shmem
import numpy as np
import unittest

types = list('bhilqBHILQfd')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]


class TestAlloc(unittest.TestCase):

    def testAlloc(self):
        for n in range(1, 4):
            for t in types:
                for align in (None, 8, 64):
                    for clear in (True, False):
                        cdata = shmem.alloc(t, n, align, clear)
                        shmem.free(cdata)
                        self.assertRaises(KeyError, shmem.free, cdata)

    def testFromCData(self):
        for n in range(1, 4):
            for t in types:
                size = n * np.dtype(t).itemsize
                cdata = shmem.alloc('B', size)
                array = shmem.fromcdata(cdata, dtype=t)
                self.assertEqual(array.shape, (n,))
                self.assertEqual(array.dtype, np.dtype(t))
                #
                cdata = shmem.alloc(t, n)
                array = shmem.fromcdata(cdata)
                self.assertEqual(array.dtype, np.dtype(t))
                self.assertEqual(array.shape, (n,))
                array = shmem.fromcdata(cdata, (n, 1))
                self.assertEqual(array.shape, (n, 1))
                #
                cdata = shmem.alloc(t, n*n)
                array = shmem.fromcdata(cdata)
                self.assertEqual(array.shape, (n*n,))
                array = shmem.fromcdata(cdata, (n, n), order='F')
                self.assertEqual(array.shape, (n, n))
                self.assertTrue(array.flags.f_contiguous)

    def testNewArray(self):
        for n in range(1, 4):
            for t in types:
                for order in ('C', 'F'):
                    for align in (None, 8, 64):
                        for clear in (True, False):
                            array = shmem.new_array(
                                n, t, order=order,
                                align=align, clear=clear
                            )
                            self.assertEqual(array.dtype, np.dtype(t))
                            if order == 'C':
                                self.assertTrue(array.flags.c_contiguous)
                            if order == 'F':
                                self.assertTrue(array.flags.f_contiguous)
                            shmem.free(array.base)
                            array = shmem.new_array(
                                (n, n), t, order=order,
                                align=align, clear=clear
                            )
                            self.assertEqual(array.dtype, np.dtype(t))
                            if order == 'C':
                                self.assertTrue(array.flags.c_contiguous)
                            if order == 'F':
                                self.assertTrue(array.flags.f_contiguous)
                            shmem.free(array.base)

    def testArray(self):
        arglist = (
            42,
            [[1,2],[3,4]],
            [[1,2],[3,4],[5.0,6.0]],
        )
        for arg in arglist:
            for dtype in (None, int, float):
                for order in ('K', 'A', 'C', 'F'):
                    b = np.array(arg, dtype, order=order)
                    a = shmem.array(arg, dtype, order=order)
                    self.assertEqual(a.dtype, b.dtype)
                    self.assertEqual(a.shape, b.shape)
                    self.assertEqual(a.strides, b.strides)
                    a = shmem.array(b)
                    self.assertEqual(a.dtype, b.dtype)
                    self.assertEqual(a.shape, b.shape)
                    self.assertEqual(a.strides, b.strides)


    def testEmpty(self):
        ai = shmem.empty(1, dtype=int)
        af = shmem.empty(1, dtype=float)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))

    def testEmpty(self):
        ai = shmem.empty(1, dtype=int)
        af = shmem.empty(1, dtype=float)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))

    def testZeros(self):
        ai = shmem.zeros(1, dtype=int)
        af = shmem.zeros(1, dtype=float)
        self.assertEqual(ai[0], 0)
        self.assertEqual(af[0], 0.0)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))

    def testOnes(self):
        ai = shmem.ones(1, dtype=int)
        af = shmem.ones(1, dtype=float)
        self.assertEqual(ai[0], 1)
        self.assertEqual(af[0], 1.0)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))

    def testFull(self):
        ai = shmem.full(1, 42)
        af = shmem.full(1, 42, dtype=float)
        self.assertEqual(ai[0], 42)
        self.assertEqual(af[0], 42.0)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))


if __name__ == '__main__':
    unittest.main()
