from shmem4py import shmem
import numpy as np
import unittest

types = list('bhilqBHILQfd')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]


#@unittest.skipIf(True, "always")
class TestAlloc(unittest.TestCase):

    def testAlloc(self):
        hint_atomics = shmem.MALLOC_ATOMICS_REMOTE
        hint_remote = shmem.MALLOC_SIGNAL_REMOTE
        for n in range(4):
            for s in [1, 2, 4, 8, 12, 16]:
                for align in (None, 8, 64, 128):
                    for clear in (True, False):
                        for hints in (0, hint_atomics, hint_remote):
                            mem = shmem.alloc(n, s, align, hints, clear)
                            cdata = shmem.ffi.from_buffer(mem)
                            caddr = shmem.ffi.cast('uintptr_t', cdata)
                            self.assertEqual(len(mem), n*s)
                            if align is not None:
                                self.assertEqual(int(caddr) % align, 0)
                            if clear and len(mem):
                                self.assertEqual(mem[0], 0)
                            shmem.free(mem)
                            self.assertRaises(KeyError, shmem.free, mem)

    def testFromAlloc(self):
        for n in range(4):
            for t in types:
                s = np.dtype(t).itemsize
                cdata = shmem.alloc(n, s)
                array = shmem.fromalloc(cdata, dtype=t)
                self.assertEqual(array.shape, (n,))
                self.assertEqual(array.dtype, np.dtype(t))
                shmem.free(cdata)
                #
                cdata = shmem.alloc(n, s)
                array = shmem.fromalloc(cdata, dtype=t)
                self.assertEqual(array.dtype, np.dtype(t))
                self.assertEqual(array.shape, (n,))
                array = shmem.fromalloc(cdata, (n, 1), dtype=t)
                self.assertEqual(array.shape, (n, 1))
                shmem.free(cdata)
                #
                cdata = shmem.alloc(n*n, s)
                array = shmem.fromalloc(cdata, dtype=t)
                self.assertEqual(array.shape, (n*n,))
                array = shmem.fromalloc(cdata, (n, n), dtype=t, order='F')
                self.assertEqual(array.shape, (n, n))
                self.assertTrue(array.flags.f_contiguous)
                shmem.free(cdata)

    def testNewArray(self):
        for n in range(4):
            for t in types:
                for order in ('C', 'F'):
                    for align in (None, 8, 64):
                        for clear in (True, False):
                            array = shmem.new_array(
                                n, t, order=order,
                                align=align, clear=clear,
                            )
                            self.assertEqual(array.dtype, np.dtype(t))
                            if order == 'C':
                                self.assertTrue(array.flags.c_contiguous)
                            if order == 'F':
                                self.assertTrue(array.flags.f_contiguous)
                            shmem.del_array(array)
                            array = shmem.new_array(
                                (n, n), t, order=order,
                                align=align, clear=clear,
                            )
                            self.assertEqual(array.dtype, np.dtype(t))
                            if order == 'C':
                                self.assertTrue(array.flags.c_contiguous)
                            if order == 'F':
                                self.assertTrue(array.flags.f_contiguous)
                            shmem.del_array(array)

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
                    shmem.free(a)
                    a = shmem.array(b)
                    self.assertEqual(a.dtype, b.dtype)
                    self.assertEqual(a.shape, b.shape)
                    self.assertEqual(a.strides, b.strides)
                    shmem.free(a)

    def testEmpty(self):
        ai = shmem.empty(1, dtype=int)
        af = shmem.empty(1, dtype=float)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))
        shmem.free(ai)
        shmem.free(af)

    def testZeros(self):
        ai = shmem.zeros(1, dtype=int)
        af = shmem.zeros(1, dtype=float)
        self.assertEqual(ai[0], 0)
        self.assertEqual(af[0], 0.0)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))
        shmem.free(ai)
        shmem.free(af)

    def testOnes(self):
        ai = shmem.ones(1, dtype=int)
        af = shmem.ones(1, dtype=float)
        self.assertEqual(ai[0], 1)
        self.assertEqual(af[0], 1.0)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))
        shmem.free(ai)
        shmem.free(af)

    def testFull(self):
        ai = shmem.full(1, 42)
        af = shmem.full(1, 42, dtype=float)
        self.assertEqual(ai[0], 42)
        self.assertEqual(af[0], 42.0)
        self.assertEqual(ai.dtype, np.dtype(int))
        self.assertEqual(af.dtype, np.dtype(float))
        shmem.free(ai)
        shmem.free(af)


if __name__ == '__main__':
    unittest.main()
