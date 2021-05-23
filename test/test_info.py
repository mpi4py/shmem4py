from shmem4py import shmem
import unittest


class TestInfo(unittest.TestCase):

    def testName(self):
        name = shmem.info_get_name()
        self.assertEqual(name, shmem.VENDOR_STRING)

    def testVersion(self):
        major, minor = shmem.info_get_version()
        self.assertEqual(major, shmem.MAJOR_VERSION)
        self.assertEqual(minor, shmem.MINOR_VERSION)


if __name__ == '__main__':
    unittest.main()
