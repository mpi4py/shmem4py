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
types_std += [f'i{1<<i}' for i in range(2, 4)]
types_std += [f'u{1<<i}' for i in range(2, 4)]


class TestAMO(unittest.TestCase):

    def testFetch(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            src = shmem.array(mype, dtype=t)
            shmem.barrier_all()
            val = shmem.atomic_fetch(src, nxpe)
            self.assertEqual(val, nxpe)

    def testSet(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            tgt = shmem.array(-1, dtype=t)
            shmem.atomic_set(tgt, nxpe, nxpe)
            shmem.barrier_all()
            self.assertEqual(tgt, mype)

    def testSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            tgt = shmem.array(-1, dtype=t)
            shmem.barrier_all()
            val = shmem.atomic_swap(tgt, nxpe, nxpe)
            shmem.barrier_all()
            self.assertEqual(tgt, mype)
            self.assertEqual(val, np.array(-1, dtype=t))

    @unittest.skipIf('open-mpi' in shmem.VENDOR_STRING, 'open-mpi')
    def testCompareSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            #
            val = shmem.atomic_compare_swap(tgt, 1, nxpe, nxpe)
            shmem.barrier_all()
            self.assertEqual(tgt, 0)
            self.assertEqual(val, 0)
            #
            val = shmem.atomic_compare_swap(tgt, 0, nxpe, nxpe)
            shmem.barrier_all()
            self.assertEqual(tgt, mype)
            self.assertEqual(val, 0)
            #
            val = shmem.atomic_compare_swap(tgt, nxpe, 0, nxpe)
            shmem.barrier_all()
            self.assertEqual(tgt, 0)
            self.assertEqual(val, nxpe)
            #
            val = shmem.atomic_compare_swap(tgt, npes, 0, nxpe)
            shmem.barrier_all()
            self.assertEqual(tgt, 0)
            self.assertEqual(val, 0)

    def testFetchOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            for i in range(3):
                op = shmem.AMO_INC
                val = shmem.atomic_fetch_op(tgt, op, None, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, i)
            for i in range(3):
                op = shmem.AMO_ADD
                val = shmem.atomic_fetch_op(tgt, op, 1, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, 3 + i)

    def testOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            tgt = shmem.array(0, dtype=t)
            for i in range(3):
                shmem.barrier_all()
                op = shmem.AMO_INC
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_op(tgt, op, None, nxpe)
                self.assertEqual(val, i)
            for i in range(3):
                shmem.barrier_all()
                op = shmem.AMO_ADD
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_op(tgt, op, 1, nxpe)
                self.assertEqual(val, 3 + i)

    def testFetchIncAdd(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            for i in range(3):
                val = shmem.atomic_fetch_inc(tgt, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, i)
            for i in range(3):
                val = shmem.atomic_fetch_add(tgt, 1, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, 3 + i)

    def testIncAdd(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            tgt = shmem.array(0, dtype=t)
            for i in range(3):
                shmem.barrier_all()
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_inc(tgt, nxpe)
                self.assertEqual(val, i)
            for i in range(3):
                shmem.barrier_all()
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_add(tgt, 1, nxpe)
                self.assertEqual(val, 3 + i)

    def testFetchBitwise(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_bit:
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            for i in range(5):
                val = shmem.atomic_fetch_or(tgt, 1<<i, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, 2**i-1)
            for i in reversed(range(5)):
                val = shmem.atomic_fetch_xor(tgt, 1<<i, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, 2**(i+1)-1)
            shmem.atomic_set(tgt, 2**5-1, nxpe)
            shmem.barrier_all()
            for i in reversed(range(5)):
                val = shmem.atomic_fetch_and(tgt, 2**i-1, nxpe)
                shmem.barrier_all()
                self.assertEqual(val, 2**(i+1)-1)

    def testBitwise(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_bit:
            tgt = shmem.array(0, dtype=t)
            for i in range(5):
                shmem.barrier_all()
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_or(tgt, 1<<i, nxpe)
                self.assertEqual(val, 2**i-1)
            for i in reversed(range(5)):
                shmem.barrier_all()
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_xor(tgt, 1<<i, nxpe)
                self.assertEqual(val, 2**(i+1)-1)
            shmem.barrier_all()
            shmem.atomic_set(tgt, 2**5-1, nxpe)
            for i in reversed(range(5)):
                shmem.barrier_all()
                val = shmem.atomic_fetch(tgt, nxpe)
                shmem.atomic_and(tgt, 2**i-1, nxpe)
                self.assertEqual(val, 2**(i+1)-1)


class TestAMONBI(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        val = np.array(0, dtype='i')
        src = shmem.array(0, dtype='i')
        try:
            shmem.atomic_fetch_nbi(val, src, shmem.my_pe())
        except NotImplementedError:
            raise unittest.SkipTest('amo-nbi')

    def testFetch(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            val = np.array(0, dtype=t)
            src = shmem.array(mype, dtype=t)
            shmem.barrier_all()
            shmem.atomic_fetch_nbi(val, src, nxpe)
            shmem.quiet()
            self.assertEqual(val, nxpe)

    def testSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_ext:
            val = np.array(0, dtype=t)
            tgt = shmem.array(-1, dtype=t)
            shmem.barrier_all()
            shmem.atomic_swap_nbi(val, tgt, nxpe, nxpe)
            shmem.quiet()
            self.assertEqual(tgt, mype)
            self.assertEqual(val, np.array(-1, dtype=t))

    @unittest.skipIf('open-mpi' in shmem.VENDOR_STRING, 'open-mpi')
    def testCompareSwap(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            val = np.array(0, dtype=t)
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            #
            shmem.atomic_compare_swap_nbi(val, tgt, 1, nxpe, nxpe)
            shmem.quiet()
            self.assertEqual(tgt, 0)
            self.assertEqual(val, 0)
            #
            shmem.atomic_compare_swap_nbi(val, tgt, 0, nxpe, nxpe)
            shmem.quiet()
            self.assertEqual(tgt, mype)
            self.assertEqual(val, 0)
            #
            shmem.atomic_compare_swap_nbi(val, tgt, nxpe, 0, nxpe)
            shmem.quiet()
            self.assertEqual(tgt, 0)
            self.assertEqual(val, nxpe)
            #
            shmem.atomic_compare_swap_nbi(val, tgt, npes, 0, nxpe)
            shmem.quiet()
            self.assertEqual(tgt, 0)
            self.assertEqual(val, 0)

    def testFetchOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            val = np.array(0, dtype=t)
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            for i in range(3):
                op = shmem.AMO_INC
                shmem.atomic_fetch_op_nbi(val, tgt, op, None, nxpe)
                shmem.quiet()
                self.assertEqual(val, i)
            for i in range(3):
                op = shmem.AMO_ADD
                shmem.atomic_fetch_op_nbi(val, tgt, op, 1, nxpe)
                shmem.quiet()
                self.assertEqual(val, 3 + i)

    def testFetchIncAdd(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_std:
            val = np.array(0, dtype=t)
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            for i in range(3):
                shmem.atomic_fetch_inc_nbi(val, tgt, nxpe)
                shmem.quiet()
                self.assertEqual(val, i)
            for i in range(3):
                shmem.atomic_fetch_add_nbi(val, tgt, 1, nxpe)
                shmem.quiet()
                self.assertEqual(val, 3 + i)

    def testFetchBitwise(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types_bit:
            val = np.array(0, dtype=t)
            tgt = shmem.array(0, dtype=t)
            shmem.barrier_all()
            for i in range(5):
                shmem.atomic_fetch_or_nbi(val, tgt, 1<<i, nxpe)
                shmem.quiet()
                self.assertEqual(val, 2**i-1)
            for i in reversed(range(5)):
                shmem.atomic_fetch_xor_nbi(val, tgt, 1<<i, nxpe)
                shmem.quiet()
                self.assertEqual(val, 2**(i+1)-1)
            shmem.atomic_set(tgt, 2**5-1, nxpe)
            shmem.barrier_all()
            for i in reversed(range(5)):
                shmem.atomic_fetch_and_nbi(val, tgt, 2**i-1, nxpe)
                shmem.quiet()
                self.assertEqual(val, 2**(i+1)-1)


if __name__ == '__main__':
    unittest.main()
