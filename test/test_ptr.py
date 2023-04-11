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

    def testPtrMemory(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        pvpe = (mype - 1) % npes

        for t in types:
            sym = shmem.new_array(1, t)
            sym[0] = npes
            shmem.sync_all()

            nloc = shmem.ptr(sym, nxpe)
            if nloc is not None:
                self.assertTrue(isinstance(nloc, np.ndarray))
                self.assertEqual(nloc.dtype, sym.dtype)
                self.assertEqual(nloc[0], npes)
                nloc[0] = nxpe
                shmem.sync_all()
                self.assertEqual(sym[0], mype)

            shmem.sync_all()

            ploc = shmem.ptr(sym, pvpe)
            if ploc is not None:
                self.assertTrue(isinstance(ploc, np.ndarray))
                self.assertEqual(ploc.dtype, sym.dtype)
                self.assertEqual(ploc[0], pvpe)
                ploc[0] = mype
                shmem.sync_all()
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

                    loc = shmem.ptr(sym, nxpe)
                    if loc is not None:
                        self.assertTrue(isinstance(loc, np.ndarray))
                        self.assertEqual(loc.dtype, sym.dtype)
                        self.assertEqual(loc.shape, sym.shape)
                        self.assertEqual(loc.strides, sym.strides)
                        self.assertTrue(np.all(loc == npes))
                        loc[...] = nxpe
                        shmem.sync_all()
                        self.assertTrue(np.all(sym == mype))

                    shmem.sync_all()

                    loc = shmem.ptr(sym, pvpe)
                    if loc is not None:
                        self.assertTrue(isinstance(loc, np.ndarray))
                        self.assertEqual(loc.dtype, sym.dtype)
                        self.assertEqual(loc.shape, sym.shape)
                        self.assertEqual(loc.strides, sym.strides)
                        self.assertTrue(np.all(loc == pvpe))
                        loc[...] = mype
                        shmem.sync_all()
                        self.assertTrue(np.all(sym == nxpe))

                    shmem.free(sym)


if __name__ == '__main__':
    unittest.main()
