from shmem4py import shmem
import numpy as np
import unittest

types_std = list('ilqILQ')
types_std += [f'i{1<<i}' for i in range(2, 4)]
types_std += [f'u{1<<i}' for i in range(2, 4)]

types_ext = list('fd')
types_ext += [f'f{1<<i}' for i in range(2, 4)]
types_ext += types_std

types_bit = list('ILQ')
types_bit += [f'u{1<<i}' for i in range(2, 4)]


class TestAMO(unittest.TestCase):

    def testFetch(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            with self.subTest(type=t):
                src = shmem.array(mype, dtype=t)
                val = shmem.atomic_fetch(src, nxpe)
                self.assertEqual(val, nxpe)
                shmem.free(src)

    def testSet(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            with self.subTest(type=t):
                ini = np.array(-1).astype(t)
                tgt = shmem.array(ini, dtype=t)
                shmem.atomic_set(tgt, nxpe, nxpe)
                shmem.barrier_all()
                self.assertEqual(tgt, mype)
                shmem.free(tgt)

    def testSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            with self.subTest(type=t):
                ini = np.array(-1).astype(t)
                tgt = shmem.array(ini, dtype=t)
                val = shmem.atomic_swap(tgt, nxpe, nxpe)
                shmem.barrier_all()
                self.assertEqual(tgt, mype)
                self.assertEqual(val, np.array(-1).astype(t))
                shmem.free(tgt)

    @unittest.skipIf('open-mpi' in shmem.VENDOR_STRING, 'open-mpi')
    def testCompareSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                #
                shmem.sync_all()
                val = shmem.atomic_compare_swap(tgt, 1, nxpe, nxpe)
                shmem.barrier_all()
                self.assertEqual(tgt, 0)
                self.assertEqual(val, 0)
                #
                shmem.sync_all()
                val = shmem.atomic_compare_swap(tgt, 0, nxpe, nxpe)
                shmem.barrier_all()
                self.assertEqual(tgt, mype)
                self.assertEqual(val, 0)
                #
                shmem.sync_all()
                val = shmem.atomic_compare_swap(tgt, nxpe, 0, nxpe)
                shmem.barrier_all()
                self.assertEqual(tgt, 0)
                self.assertEqual(val, nxpe)
                #
                shmem.sync_all()
                val = shmem.atomic_compare_swap(tgt, npes, 0, nxpe)
                shmem.barrier_all()
                self.assertEqual(tgt, 0)
                self.assertEqual(val, 0)
                #
                shmem.free(tgt)

    def testFetchOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    shmem.sync_all()
                    op = shmem.AMO_INC
                    val = shmem.atomic_fetch_op(tgt, None, op, nxpe)
                    self.assertEqual(val, i)
                for i in range(3):
                    shmem.sync_all()
                    op = shmem.AMO_ADD
                    val = shmem.atomic_fetch_op(tgt, 1, op, nxpe)
                    self.assertEqual(val, 3 + i)
                shmem.free(tgt)
        for t in types_ext:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    op = shmem.AMO_SET
                    val = shmem.atomic_fetch_op(tgt, i+1, op, nxpe)
                    self.assertEqual(val, i)
                shmem.free(tgt)

    def testOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    shmem.sync_all()
                    op = shmem.AMO_INC
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_op(tgt, None, op, nxpe)
                    self.assertEqual(val, i)
                for i in range(3):
                    op = shmem.AMO_ADD
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_op(tgt, 1, op, nxpe)
                    self.assertEqual(val, 3 + i)
                shmem.free(tgt)
        for t in types_ext:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    op = shmem.AMO_SET
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_op(tgt, i+1, op, nxpe)
                    self.assertEqual(val, i)
                shmem.free(tgt)

    def testFetchIncAdd(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    val = shmem.atomic_fetch_inc(tgt, nxpe)
                    self.assertEqual(val, i)
                for i in range(3):
                    val = shmem.atomic_fetch_add(tgt, 1, nxpe)
                    self.assertEqual(val, 3 + i)
                shmem.free(tgt)

    def testIncAdd(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    shmem.sync_all()
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_inc(tgt, nxpe)
                    self.assertEqual(val, i)
                for i in range(3):
                    shmem.sync_all()
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_add(tgt, 1, nxpe)
                    self.assertEqual(val, 3 + i)
                shmem.free(tgt)

    def testFetchBitwise(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_bit:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(5):
                    val = shmem.atomic_fetch_or(tgt, 1<<i, nxpe)
                    self.assertEqual(val, 2**i-1)
                for i in reversed(range(5)):
                    val = shmem.atomic_fetch_xor(tgt, 1<<i, nxpe)
                    self.assertEqual(val, 2**(i+1)-1)
                shmem.atomic_set(tgt, 2**5-1, nxpe)
                shmem.barrier_all()
                for i in reversed(range(5)):
                    val = shmem.atomic_fetch_and(tgt, 2**i-1, nxpe)
                    self.assertEqual(val, 2**(i+1)-1)
                shmem.free(tgt)

    def testBitwise(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_bit:
            with self.subTest(type=t):
                tgt = shmem.array(0, dtype=t)
                for i in range(5):
                    shmem.barrier_all()
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_or(tgt, 1<<i, nxpe)
                    self.assertEqual(val, 2**i-1)
                for i in reversed(range(5)):
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_xor(tgt, 1<<i, nxpe)
                    self.assertEqual(val, 2**(i+1)-1)
                shmem.barrier_all()
                shmem.atomic_set(tgt, 2**5-1, nxpe)
                for i in reversed(range(5)):
                    val = shmem.atomic_fetch(tgt, nxpe)
                    shmem.atomic_and(tgt, 2**i-1, nxpe)
                    self.assertEqual(val, 2**(i+1)-1)
                shmem.free(tgt)


class TestAMONBI(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        val = np.array(0, dtype='i')
        src = shmem.array(0, dtype='i')
        try:
            shmem.atomic_fetch_nbi(val, src, shmem.my_pe())
        except NotImplementedError:
            raise unittest.SkipTest('amo-nbi')
        finally:
            shmem.free(src)

    def testFetch(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        prpe = (mype - 1) % npes
        nxpe = (mype + 1) % npes
        for t in types_ext:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                src = shmem.array(mype, dtype=t)
                #
                shmem.sync_all()
                shmem.atomic_fetch_nbi(val, src, nxpe)
                shmem.quiet()
                self.assertEqual(val, nxpe)
                #
                shmem.sync_all()
                src[...] = np.array(prpe, dtype=t)
                shmem.sync_all()
                shmem.atomic_fetch_nbi(val, src, nxpe)
                shmem.quiet()
                self.assertEqual(val, mype)
                #
                shmem.free(src)

    def testSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        prpe = (mype - 1) % npes
        nxpe = (mype + 1) % npes
        for t in types_ext:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                ini = np.array(-1).astype(t)
                tgt = shmem.array(ini, dtype=t)
                #
                shmem.sync_all()
                shmem.atomic_swap_nbi(val, tgt, nxpe, nxpe)
                shmem.quiet()
                self.assertEqual(val, np.array(-1).astype(t))
                shmem.sync_all()
                self.assertEqual(tgt, mype)
                #
                shmem.sync_all()
                shmem.atomic_swap_nbi(val, tgt, mype, nxpe)
                shmem.quiet()
                self.assertEqual(val, np.array(nxpe, dtype=t))
                shmem.sync_all()
                self.assertEqual(tgt, prpe)
                #
                shmem.free(tgt)

    @unittest.skipIf('open-mpi' in shmem.VENDOR_STRING, 'open-mpi')
    def testCompareSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                tgt = shmem.array(0, dtype=t)
                #
                shmem.sync_all()
                shmem.atomic_compare_swap_nbi(val, tgt, 1, nxpe, nxpe)
                shmem.quiet()
                self.assertEqual(val, 0)
                shmem.sync_all()
                self.assertEqual(tgt, 0)
                #
                shmem.sync_all()
                shmem.atomic_compare_swap_nbi(val, tgt, 0, nxpe, nxpe)
                shmem.quiet()
                self.assertEqual(val, 0)
                shmem.sync_all()
                self.assertEqual(tgt, mype)
                #
                shmem.sync_all()
                shmem.atomic_compare_swap_nbi(val, tgt, nxpe, 0, nxpe)
                shmem.quiet()
                self.assertEqual(val, nxpe)
                shmem.sync_all()
                self.assertEqual(tgt, 0)
                #
                shmem.sync_all()
                shmem.atomic_compare_swap_nbi(val, tgt, npes, 0, nxpe)
                shmem.quiet()
                self.assertEqual(val, 0)
                shmem.sync_all()
                self.assertEqual(tgt, 0)
                #
                shmem.free(tgt)

    def testFetchOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    op = shmem.AMO_INC
                    shmem.atomic_fetch_op_nbi(val, tgt, None, op, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, i)
                for i in range(3):
                    op = shmem.AMO_ADD
                    shmem.atomic_fetch_op_nbi(val, tgt, 1, op, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, 3 + i)
                shmem.free(tgt)
        for t in types_ext:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    op = shmem.AMO_SET
                    shmem.atomic_fetch_op_nbi(val, tgt, i+1, op, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, i)
                shmem.free(tgt)

    def testFetchIncAdd(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                tgt = shmem.array(0, dtype=t)
                for i in range(3):
                    shmem.atomic_fetch_inc_nbi(val, tgt, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, i)
                for i in range(3):
                    shmem.atomic_fetch_add_nbi(val, tgt, 1, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, 3 + i)
                shmem.free(tgt)

    def testFetchBitwise(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_bit:
            with self.subTest(type=t):
                val = np.array(0, dtype=t)
                tgt = shmem.array(0, dtype=t)
                for i in range(5):
                    shmem.atomic_fetch_or_nbi(val, tgt, 1<<i, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, 2**i-1)
                for i in reversed(range(5)):
                    shmem.atomic_fetch_xor_nbi(val, tgt, 1<<i, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, 2**(i+1)-1)
                shmem.atomic_set(tgt, 2**5-1, nxpe)
                shmem.quiet()
                for i in reversed(range(5)):
                    shmem.atomic_fetch_and_nbi(val, tgt, 2**i-1, nxpe)
                    shmem.quiet()
                    self.assertEqual(val, 2**(i+1)-1)
                shmem.free(tgt)


if __name__ == '__main__':
    unittest.main()
