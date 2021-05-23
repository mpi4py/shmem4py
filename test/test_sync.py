from shmem4py import shmem
import numpy as np
import unittest

types = list('ilqILQ')
types += [f'i{1<<i}' for i in range(2, 4)]
types += [f'u{1<<i}' for i in range(2, 4)]


class TestSync(unittest.TestCase):

    def testWait(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            flags = shmem.zeros(npes, t)
            for pe in range(npes):
                shmem.atomic_set(flags[..., mype], 1, pe)
            for pe in range(npes):
                shmem.wait_until(flags[..., pe], 'eq', 1)


    def testTest(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            flags = shmem.zeros(npes, t)
            for pe in range(npes):
                done = shmem.test(flags[..., mype], '==', 1)
                self.assertFalse(done)
            for pe in range(npes):
                shmem.atomic_set(flags[..., mype], 1, pe)
            shmem.barrier_all()
            for pe in range(npes):
                done = shmem.test(flags[..., pe], shmem.CMP_EQ, 1)
                self.assertTrue(done)


if __name__ == '__main__':
    unittest.main()
