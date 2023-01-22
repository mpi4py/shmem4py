from shmem4py import shmem
import numpy as np
import unittest


shmem_15 = shmem.info_get_version() >= (1, 5)

types = list('bhilqBHILQfdgFD')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]


class TestColl(unittest.TestCase):

    def testBarrierAll(self):
        shmem.barrier_all()

    def testSyncAll(self):
        shmem.sync_all()
        shmem.sync()

    def testSyncTeam(self):
        shmem.sync(shmem.TEAM_WORLD)

    def testBroadcast(self):
        team = shmem.TEAM_WORLD
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty(n, t)
                    src = shmem.full(n, mype, t)
                    for root in range(npes):
                        with self.subTest(type=t, size=n, root=root):
                            tgt[...] = npes
                            shmem.barrier_all()
                            shmem.broadcast(tgt, src, root, team=team)
                            self.assertTrue(np.all(tgt == root))
                    shmem.free(tgt)
                    shmem.free(src)

    def testBroadcastSize(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty((3, n), t)
                    src = shmem.empty((5, n), t)
                    for root in range(npes):
                        with self.subTest(type=t, size=n, root=root):
                            tgt[...] = npes
                            src[...] = np.array(-1).astype(t)
                            src[0, :] = mype
                            shmem.barrier_all()
                            shmem.broadcast(tgt, src, root, size=n)
                            self.assertTrue(np.all(tgt[0] == root))
                            self.assertTrue(np.all(tgt[1:, :] == npes))
                    shmem.free(tgt)
                    shmem.free(src)

    def testCollect(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty((npes, n), dtype=t)
                    src = shmem.empty(n, dtype=t)
                    src[...] = mype
                    shmem.barrier_all()
                    shmem.collect(tgt, src)
                    for i in range(npes):
                        self.assertTrue(np.all(tgt[i] == i))
                    shmem.free(tgt)
                    shmem.free(src)

    def testCollectSize(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty(npes*npes*n, dtype=t)
                    src = shmem.empty(npes*n, dtype=t)
                    tgt[...] = npes
                    src[...] = mype
                    shmem.barrier_all()
                    shmem.collect(tgt, src, size=(mype+1)*n)
                    for i in range(npes):
                        a = i*(i+1)//2
                        b = a + i + 1
                        self.assertTrue(np.all(tgt[a*n:b*n] == i))
                    a = npes*(npes+1)//2
                    self.assertTrue(np.all(tgt[a*n:] == npes))
                    shmem.free(tgt)
                    shmem.free(src)

    def testFCollect(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty((npes, n), dtype=t)
                    src = shmem.empty(n, dtype=t)
                    src[...] = mype
                    shmem.barrier_all()
                    shmem.fcollect(tgt, src)
                    for i in range(npes):
                        self.assertTrue(np.all(tgt[i] == i))
                    shmem.free(tgt)
                    shmem.free(src)

    def testFCollectSize(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty((2, npes, n), dtype=t)
                    src = shmem.empty((2, n), dtype=t)
                    src[0] = mype
                    src[1] = npes + 1
                    tgt[...] = npes
                    shmem.barrier_all()
                    shmem.fcollect(tgt, src, size=n)
                    for i in range(npes):
                        self.assertTrue(np.all(tgt[0, i, :] == i))
                        self.assertTrue(np.all(tgt[1:, i, :] == npes))
                    shmem.free(tgt)
                    shmem.free(src)

    def testAllToAll(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            for n in (0, 1, 2, 3, 4):
                with self.subTest(type=t, size=n):
                    if not shmem_15:
                        n = n * 4  // np.dtype(t).itemsize
                    tgt = shmem.empty((npes, n), dtype=t)
                    src = shmem.empty((npes, n), dtype=t)
                    for i in range(npes):
                        src[i] = np.arange(i, i+n, dtype=t)
                    shmem.barrier_all()
                    shmem.alltoall(tgt, src)
                    for i in range(npes):
                        chk = np.arange(mype, mype+n, dtype=t)
                        self.assertTrue(np.all(tgt[i] == chk))
                    shmem.free(tgt)
                    shmem.free(src)

    def testAllToAllStride(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            with self.subTest(type=t):
                itemsize = np.dtype(t).itemsize
                if not shmem_15:
                    if itemsize < 4: continue
                tst, sst = 3, 5
                tgt = shmem.empty((npes, tst), dtype=t)
                src = shmem.empty((npes, sst), dtype=t)
                tgt[...] = npes
                src[...] = np.array(-1).astype(t)
                src[:, 0] = mype
                shmem.barrier_all()
                shmem.alltoalls(tgt, src, tst=tst, sst=sst)
                for i in range(npes):
                    self.assertTrue(np.all(tgt[i, 0] == i))
                    for j in range(1, tst):
                        self.assertTrue(np.all(tgt[i, j] == npes))
                shmem.free(tgt)
                shmem.free(src)

    def testAllToAllStrideSize(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            with self.subTest(type=t):
                itemsize = np.dtype(t).itemsize
                if not shmem_15:
                    if itemsize < 4: continue
                tst, sst = 3, 5
                tgt = shmem.empty((3, npes, tst), dtype=t)
                src = shmem.empty((5, npes, sst), dtype=t)
                tgt[...] = npes
                src[...] = np.array(-1).astype(t)
                src[0, :, 0] = mype
                shmem.barrier_all()
                shmem.alltoalls(tgt, src, tst=tst, sst=sst, size=1)
                for i in range(npes):
                    self.assertTrue(np.all(tgt[0, i, 0] == i))
                    for j in range(1, tst):
                        self.assertTrue(np.all(tgt[0, i, j] == npes))
                self.assertTrue(np.all(tgt[1:, :, :] == npes))
                shmem.free(tgt)
                shmem.free(src)


if __name__ == '__main__':
    unittest.main()
