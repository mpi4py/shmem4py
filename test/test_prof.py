from shmem4py import shmem
import unittest


class TestProf(unittest.TestCase):

    def testPcontrol(self):
        for level in (1, 2, 0, 2, 1):
            shmem.pcontrol(level)


if __name__ == '__main__':
    unittest.main()
