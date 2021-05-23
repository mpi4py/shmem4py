from shmem4py import shmem
import unittest


class TestColl(unittest.TestCase):

    def testBarrierAll(self):
        shmem.barrier_all()

    def testSyncAll(self):
        shmem.sync_all()


if __name__ == '__main__':
    unittest.main()
