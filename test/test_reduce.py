from shmem4py import shmem
import unittest

types = list('ilqILQ')
types += [f'i{1<<i}' for i in range(2, 4)]
types += [f'u{1<<i}' for i in range(2, 4)]


has_reduce = hasattr(shmem.lib, 'shmem_int_sum_reduce')

class TestReduce(unittest.TestCase):

    def testCall(self):
        tgt = shmem.zeros(1, dtype='i')
        src = shmem.zeros(1, dtype='i')
        try:
            shmem.reduce(tgt, src)
        except AttributeError:
            pass

    @unittest.skipIf(not has_reduce, 'shmem-reduce')
    def testReduce(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            tgt = shmem.zeros(1, dtype=t)
            src = shmem.full(1, mype, dtype=t)
            shmem.barrier_all()
            shmem.reduce(tgt, src)
            shmem.barrier_all()
            self.assertEqual(tgt[0], ((npes-1)*npes)//2)
            shmem.reduce(tgt, src, op='min')
            shmem.barrier_all()
            self.assertEqual(tgt[0], 0)
            shmem.reduce(tgt, src, op='max')
            shmem.barrier_all()
            self.assertEqual(tgt[0], npes-1)


if __name__ == '__main__':
    unittest.main()
