from shmem4py import shmem
import unittest


class TestColl(unittest.TestCase):

    def testBarrierAll(self):
        shmem.barrier_all()

    def testSyncAll(self):
        shmem.sync_all()
        shmem.sync()

    def testSyncTeam(self):
        shmem.sync(shmem.TEAM_WORLD)


if __name__ == '__main__':
    unittest.main()
