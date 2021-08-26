from shmem4py import rc
import unittest


class TestRC(unittest.TestCase):

    def testRCCall1(self):
        rc(initialize   = rc.initialize)
        rc(threads      = rc.threads)
        rc(thread_level = rc.thread_level)
        rc(finalize     = rc.finalize)

    def testRCCall2(self):
        kwargs = rc.__dict__.copy()
        rc(**kwargs)
        rc()

    def testCallBad(self):
        error = lambda: rc(ABCXYZ=123456)
        self.assertRaises(TypeError, error)

    def testAttr(self):
        rc.initialize   = rc.initialize
        rc.threads      = rc.threads
        rc.thread_level = rc.thread_level
        rc.finalize     = rc.finalize

    def testAttrBad(self):
        error = lambda: setattr(rc, 'ABCXYZ', 123456)
        self.assertRaises(TypeError, error)

    def testRepr(self):
        mod = type(rc).__module__
        self.assertEqual(repr(rc), f"<{mod}.rc>")


if __name__ == '__main__':
    unittest.main()
