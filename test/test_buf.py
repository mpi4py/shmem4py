from shmem4py import shmem
import numpy as np
import unittest


class TestBuf(unittest.TestCase):

    def testGetBuffer(self):
        a = np.zeros(4)
        cdata, csize, ctype = shmem._getbuffer(a)
        self.assertTrue(isinstance(cdata, shmem.ffi.CData))
        self.assertEqual(csize, 4)
        self.assertEqual(ctype, 'double')

    def testReadOnly(self):
        a = np.zeros(1)
        a.flags.writeable = False
        shmem._getbuffer(a, readonly=True)
        self.assertRaises(ValueError, shmem._getbuffer, a)

    def testContiguous(self):
        a = np.zeros((2, 2, 2))
        cdata1, csize1, ctype1 = shmem._getbuffer(a)
        cdata2, csize2, ctype2 = shmem._getbuffer(a.T)
        self.assertEqual(cdata1, cdata2)
        self.assertEqual(csize1, csize2)
        self.assertEqual(ctype1, ctype2)
        a.strides = [a.strides[i] for i in (1, 0, 2)]
        self.assertRaises(ValueError, shmem._getbuffer, a)

    def testBadType(self):
        for a in (None, 123, 123.0, [1,2,3]):
            self.assertRaises(TypeError, shmem._getbuffer, a)


if __name__ == '__main__':
    unittest.main()
