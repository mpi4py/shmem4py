from shmem4py import shmem
import numpy as np
import unittest


@unittest.skipIf('osss-ucx' in shmem.VENDOR_STRING, 'osss-ucx')
class TestLock(unittest.TestCase):

    def testSetLock(self):
        npes = shmem.n_pes()
        lock = shmem.new_lock()
        value = np.array(0, dtype='i')
        counter = shmem.array(0, dtype='i')
        shmem.barrier_all()
        for pe in range(npes):
            shmem.set_lock(lock)
            shmem.get(value, counter, pe)
            value += 1
            shmem.put(counter, value, pe)
            shmem.quiet()
            shmem.clear_lock(lock)
        shmem.barrier_all()
        self.assertEqual(counter, npes)

    def testTestLock(self):
        npes = shmem.n_pes()
        lock = shmem.new_lock()
        value = np.array(0, dtype='i')
        counter = shmem.array(0, dtype='i')
        shmem.barrier_all()
        for pe in range(npes):
            while shmem.test_lock(lock):
                pass
            shmem.get(value, counter, pe)
            value += 1
            shmem.put(counter, value, pe)
            shmem.quiet()
            shmem.clear_lock(lock)
        shmem.barrier_all()
        self.assertEqual(counter, npes)


if __name__ == '__main__':
    unittest.main()
