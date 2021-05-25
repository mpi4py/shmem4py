from shmem4py import shmem
from shmem4py.shmem import ffi
import numpy as np
import unittest
import sys

pypy = sys.implementation.name.startswith('pypy')

types = list('bhilqBHILQfd')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]


class TestPtr(unittest.TestCase):

    def testPtrCData(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        pvpe = (mype - 1) % npes

        for t in types:
            sym = shmem.alloc(t, 1)
            sym[0] = npes
            shmem.barrier_all()

            nloc = shmem.ptr(sym, nxpe)
            self.assertTrue(isinstance(nloc, ffi.CData))
            self.assertEqual(ffi.typeof(sym), ffi.typeof(nloc))
            if nloc:
                if not pypy:
                    self.assertEqual(ffi.sizeof(sym), ffi.sizeof(nloc))
                self.assertEqual(nloc[0], npes)
                nloc[0] = nxpe
                shmem.barrier_all()
                self.assertEqual(sym[0], mype)

            ploc = shmem.ptr(sym, pvpe)
            self.assertTrue(isinstance(ploc, shmem.ffi.CData))
            self.assertEqual(ffi.typeof(sym), ffi.typeof(ploc))
            if ploc:
                if not pypy:
                    self.assertEqual(ffi.sizeof(sym), ffi.sizeof(ploc))
                self.assertEqual(ploc[0], pvpe)
                ploc[0] = mype
                shmem.barrier_all()
                self.assertEqual(sym[0], nxpe)

            shmem.free(sym)

    def testPtrArray(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        pvpe = (mype - 1) % npes
        for t in types:
            for d in (0, 1, 2, 3):
                for order in ('C', 'F'):
                    sym = shmem.full((3,)*d, npes, dtype=t, order=order)
                    shmem.barrier_all()
                    loc = shmem.ptr(sym, nxpe)
                    if loc is not None:
                        self.assertTrue(isinstance(loc, np.ndarray))
                        self.assertEqual(loc.dtype, sym.dtype)
                        self.assertEqual(loc.shape, sym.shape)
                        self.assertEqual(loc.strides, sym.strides)
                        self.assertTrue(np.all(loc == npes))
                        loc[...] = nxpe
                        shmem.barrier_all()
                        self.assertTrue(np.all(sym == mype))
                    loc = shmem.ptr(sym, pvpe)
                    if loc is not None:
                        self.assertTrue(isinstance(loc, np.ndarray))
                        self.assertEqual(loc.dtype, sym.dtype)
                        self.assertEqual(loc.shape, sym.shape)
                        self.assertEqual(loc.strides, sym.strides)
                        self.assertTrue(np.all(loc == pvpe))
                        loc[...] = mype
                        shmem.barrier_all()
                        self.assertTrue(np.all(sym == nxpe))


if __name__ == '__main__':
    unittest.main()
