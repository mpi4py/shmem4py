from shmem4py import shmem
import numpy as np
import unittest


types = list('bhilqBHILQfdgFD')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]


class TestRMA(unittest.TestCase):

    def testPutSizeCtx(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            src = np.full(2, nxpe, dtype=t)
            dst = shmem.empty(2, dtype=t)
            dst[...] = init = np.array(-1).astype(t)
            ctx = shmem.CTX_DEFAULT
            shmem.barrier_all()
            shmem.put(dst, src, nxpe, size=1, ctx=ctx)
            shmem.barrier_all()
            self.assertEqual(dst[0], mype)
            self.assertEqual(dst[1], init)
            shmem.free(dst)

    def testGetSizeCtx(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            src = shmem.full(2, mype, dtype=t)
            dst = np.empty(2, dtype=t)
            dst[...] = init = np.array(-1).astype(t)
            ctx = shmem.CTX_DEFAULT
            shmem.barrier_all()
            shmem.get(dst, src, nxpe, size=1, ctx=ctx)
            shmem.barrier_all()
            self.assertEqual(dst[0], nxpe)
            self.assertEqual(dst[1], init)
            shmem.free(src)

    def testPut(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            src = np.full(2, nxpe, dtype=t)
            dst = shmem.full(2, -1, dtype=t)
            shmem.barrier_all()
            shmem.put(dst, src, nxpe)
            shmem.barrier_all()
            self.assertEqual(dst[0], mype)
            self.assertEqual(dst[1], mype)
            shmem.free(dst)

    def testGet(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            src = shmem.full(1, mype, dtype=t)
            dst = np.full(1, -1, dtype=t)
            shmem.barrier_all()
            shmem.get(dst, src, nxpe)
            self.assertEqual(dst[0], nxpe)
            shmem.free(src)

    def testIPut(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            if t in "FDG": continue
            src = np.full(12, nxpe, dtype=t)
            tgt = shmem.empty(12, dtype=t)
            val = np.array(-1).astype(t)
            for tst in range(1, 12):
                with self.subTest(t=t, tst=tst):
                    tgt[...] = val
                    shmem.barrier_all()
                    shmem.iput(tgt, src, nxpe, tst=tst)
                    shmem.barrier_all()
                    self.assertTrue(np.all(tgt[::tst]==mype))
                    for i in range(1, tst):
                        self.assertTrue(np.all(tgt[i::tst]==val))
            for sst in range(1, 12):
                with self.subTest(t=t, sst=sst):
                    tgt[...] = val
                    shmem.barrier_all()
                    shmem.iput(tgt, src, nxpe, sst=sst)
                    shmem.barrier_all()
                    n = src[::sst].size
                    self.assertTrue(np.all(tgt[:n]==mype))
                    self.assertTrue(np.all(tgt[n:]==val))
            shmem.free(tgt)

    def testIGet(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            if t in "FDG": continue
            src = shmem.full(12, mype, dtype=t)
            tgt = np.empty(12, dtype=t)
            val = np.array(-1).astype(t)
            for tst in range(1, 12):
                with self.subTest(t=t, tst=tst):
                    tgt[...] = val
                    shmem.barrier_all()
                    shmem.iget(tgt, src, nxpe, tst=tst)
                    shmem.barrier_all()
                    self.assertTrue(np.all(tgt[::tst]==nxpe))
                    for i in range(1, tst):
                        self.assertTrue(np.all(tgt[i::tst]==val))
            for sst in range(1, 12):
                with self.subTest(t=t, sst=sst):
                    tgt[...] = val
                    shmem.barrier_all()
                    shmem.iget(tgt, src, nxpe, sst=sst)
                    shmem.barrier_all()
                    n = src[::sst].size
                    self.assertTrue(np.all(tgt[:n]==nxpe))
                    self.assertTrue(np.all(tgt[n:]==val))
            shmem.free(src)

    def testPutNBI(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            src = np.full(1, nxpe, dtype=t)
            dst = shmem.full(1, -1, dtype=t)
            shmem.barrier_all()
            shmem.put_nbi(dst, src, nxpe)
            shmem.fence()
            shmem.quiet()
            shmem.barrier_all()
            self.assertEqual(dst[0], mype)
            shmem.free(dst)

    def testGetNBI(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            src = shmem.full(1, mype, dtype=t)
            dst = np.full(1, -1, dtype=t)
            shmem.barrier_all()
            shmem.get_nbi(dst, src, nxpe)
            shmem.fence()
            shmem.quiet()
            self.assertEqual(dst[0], nxpe)
            shmem.free(src)


if __name__ == '__main__':
    unittest.main()
