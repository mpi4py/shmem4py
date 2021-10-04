from shmem4py import shmem
import numpy as np
import unittest

types = list('ilqILQ')
types += [f'i{1<<i}' for i in range(2, 4)]
types += [f'u{1<<i}' for i in range(2, 4)]


class TestWait(unittest.TestCase):

    def testOne(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            with self.subTest(type=t):
                ivar = shmem.zeros(npes, t)
                for pe in range(npes):
                    shmem.atomic_set(ivar[..., mype], 1, pe)
                shmem.barrier_all()
                for cmps, vals in zip(
                    ["eq ne lt le ge gt".split(),
                     "== !=  < <= >=  >".split()],
                    [[1, 0, 2, 1, 0, 0],
                     [1, 0, 2, 1, 0, 0]]
                ):
                    for cmp, val in zip(cmps, vals):
                        for pe in range(npes):
                            shmem.wait_until(ivar[..., pe], cmp, val)

    def testAll(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            for n in [1, 3]:
                with self.subTest(type=t, size=n):
                    if n == 0:
                        ivars = shmem.zeros(0, t)
                        shmem.wait_until_all(ivars, '==', 0)
                        values = np.zeros(0, t)
                        shmem.wait_until_all_vector(
                            ivars, '==', values,
                        )
                        #
                        ivars = shmem.zeros(3, t)
                        status = np.ones(3, 'i')
                        shmem.wait_until_all(
                            ivars, '==', 0, status=status,
                        )
                        values = np.zeros(3, t)
                        shmem.wait_until_all_vector(
                            ivars, '==', values, status=status,
                        )
                        continue
                    #
                    ivars = shmem.zeros(n, t)
                    values = np.zeros(n, t)
                    shmem.wait_until_all(ivars, '==', 0)
                    shmem.wait_until_all_vector(ivars, '==', values)
                    src = np.full(n, mype + 1, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    shmem.wait_until_all(ivars, shmem.CMP_NE, 0)
                    shmem.wait_until_all_vector(ivars, shmem.CMP_NE, values)
                    #
                    src = np.ones(n, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    cmp_l = "eq ne lt le ge gt".split()
                    v1_l = [1, 0, 2, 1, 0, 0]
                    v2_l = [1, 2, 3, 2, 1, 0]
                    for cmp, v1, v2 in zip(cmp_l, v1_l, v2_l):
                        shmem.wait_until_all(ivars, cmp, v1)
                        shmem.wait_until_all(ivars, cmp, v2)
                        v1vec = np.full(n, v1, t)
                        v2vec = np.full(n, v2, t)
                        shmem.wait_until_all_vector(ivars, cmp, v1vec)
                        shmem.wait_until_all_vector(ivars, cmp, v2vec)

    def testAny(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            for n in [0, 1, 3]:
                with self.subTest(type=t, size=n):
                    if n == 0:
                        ivars = shmem.zeros(0, t)
                        index = shmem.wait_until_any(ivars, '==', 0)
                        self.assertEqual(index, None)
                        values = np.ones(0, t)
                        index = shmem.wait_until_any_vector(ivars, '==', values)
                        self.assertEqual(index, None)
                        #
                        ivars = shmem.zeros(3, t)
                        status = np.ones(3, 'i')
                        index = shmem.wait_until_any(
                            ivars, '==', 0, status=status,
                        )
                        self.assertEqual(index, None)
                        values = np.ones(3, t)
                        index = shmem.wait_until_any_vector(
                            ivars, '==', values, status=status,
                        )
                        self.assertEqual(index, None)
                        continue
                    #
                    ivars = shmem.zeros(n, t)
                    ivars[-1] = 1
                    if n > 1:
                        index = shmem.wait_until_any(ivars, '==', 0)
                        self.assertNotEqual(index, n-1)
                    index = shmem.wait_until_any(ivars, '==', 1)
                    self.assertEqual(index, n-1)
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    if n > 1:
                        index = shmem.wait_until_any_vector(ivars, '==', z)
                        self.assertNotEqual(index, n-1)
                    index = shmem.wait_until_any_vector(ivars, '==', o)
                    self.assertEqual(index, n-1)
                    #
                    src = np.full(n, mype + 1, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    index = shmem.wait_until_any(ivars, shmem.CMP_GT, 0)
                    self.assertNotEqual(index, None)
                    index = shmem.wait_until_any(ivars, shmem.CMP_NE, 0)
                    self.assertNotEqual(index, None)
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    index = shmem.wait_until_any_vector(ivars, shmem.CMP_GT, z)
                    self.assertNotEqual(index, None)
                    index = shmem.wait_until_any_vector(ivars, shmem.CMP_NE, z)
                    self.assertNotEqual(index, None)
                    #
                    shmem.put(ivars, np.zeros(n, t), nxpe)
                    shmem.put(ivars[-1:], np.full(1, 7, t), nxpe)
                    shmem.barrier_all()
                    cmp_l = "eq ne lt le ge gt".split()
                    v1_l = [7, 0, 8, 7, 6, 5]
                    v2_l = [7, 0, 9, 8, 7, 6]
                    for cmp, v1, v2 in zip(cmp_l, v1_l, v2_l):
                        index = shmem.wait_until_any(ivars, cmp, v1)
                        self.assertNotEqual(index, None)
                        index = shmem.wait_until_any(ivars, cmp, v2)
                        self.assertNotEqual(index, None)
                        v1vec = np.full(n, v1, t)
                        v2vec = np.full(n, v1, t)
                        index = shmem.wait_until_any_vector(ivars, cmp, v1vec)
                        self.assertNotEqual(index, None)
                        index = shmem.wait_until_any_vector(ivars, cmp, v2vec)
                        self.assertNotEqual(index, None)

    def testSome(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            for n in [0, 1, 3]:
                with self.subTest(type=t, size=n):
                    if n ==0:
                        ivars = shmem.zeros(0, t)
                        index = shmem.wait_until_some(ivars, '==', 0)
                        self.assertEqual(index, [])
                        values = np.zeros(0, t)
                        index = shmem.wait_until_some_vector(ivars, '==', values)
                        self.assertEqual(index, [])
                        #
                        ivars = shmem.zeros(3, t)
                        status = np.ones(3, 'i')
                        index = shmem.wait_until_some(
                            ivars, '==', 0, status=status,
                        )
                        self.assertEqual(index, [])
                        values = np.zeros(3, t)
                        index = shmem.wait_until_some_vector(
                            ivars, '==', values, status=status,
                        )
                        self.assertEqual(index, [])
                        continue
                    #
                    ivars = shmem.zeros(n, t)
                    ivars[-1] = 1
                    if n > 1:
                        index = shmem.wait_until_some(ivars, '==', 0)
                        self.assertTrue(n-1 not in index)
                    index = shmem.wait_until_some(ivars, '==', 1)
                    self.assertEqual(index, [n-1])
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    if n > 1:
                        index = shmem.wait_until_some_vector(ivars, '==', z)
                        self.assertTrue(n-1 not in index)
                    index = shmem.wait_until_some_vector(ivars, '==', o)
                    self.assertEqual(index, [n-1])
                    #
                    src = np.full(n, mype + 1, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    index = shmem.wait_until_some(ivars, shmem.CMP_GE, 0)
                    self.assertNotEqual(index, [])
                    index = shmem.wait_until_some(ivars, shmem.CMP_NE, 0)
                    self.assertNotEqual(index, [])
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    index = shmem.wait_until_some_vector(ivars, shmem.CMP_GE, z)
                    self.assertNotEqual(index, [])
                    index = shmem.wait_until_some_vector(ivars, shmem.CMP_NE, z)
                    self.assertNotEqual(index, [])
                    #
                    n = min(n, 2)
                    ivars = shmem.zeros(n, t)
                    shmem.put(ivars, np.zeros(n, t), nxpe)
                    shmem.put(ivars[-1:], np.full(1, 7, t), nxpe)
                    shmem.barrier_all()
                    cmp_l = "eq ne lt le ge gt".split()
                    v1_l = [7, 0, 8, 7, 6, 5]
                    v2_l = [7, 0, 9, 8, 7, 6]
                    for cmp, v1, v2 in zip(cmp_l, v1_l, v2_l):
                        index = shmem.wait_until_some(ivars, cmp, v1)
                        self.assertNotEqual(index, [])
                        index = shmem.wait_until_some(ivars, cmp, v2)
                        self.assertNotEqual(index, [])
                        v1vec = np.full(n, v1, t)
                        v2vec = np.full(n, v1, t)
                        index = shmem.wait_until_some_vector(ivars, cmp, v1vec)
                        self.assertNotEqual(index, [])
                        index = shmem.wait_until_some_vector(ivars, cmp, v2vec)
                        self.assertNotEqual(index, [])


class TestTest(unittest.TestCase):

    def testOne(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            with self.subTest(type=t):
                ivar = shmem.zeros(npes, t)
                for pe in range(npes):
                    flag = shmem.test(ivar[..., mype], '==', 1)
                    self.assertFalse(flag)
                for pe in range(npes):
                    shmem.atomic_set(ivar[..., mype], 1, pe)
                shmem.barrier_all()
                for cmps, vals in zip(
                    ["eq ne lt le ge gt".split(),
                     "== !=  < <= >=  >".split()],
                    [[1, 0, 2, 1, 0, 0],
                     [1, 0, 2, 1, 0, 0]]
                ):
                    for cmp, val in zip(cmps, vals):
                        for pe in range(npes):
                            flag = shmem.test(ivar[..., pe], cmp, val)
                            self.assertTrue(flag)

    def testAll(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            for n in [0, 1, 3]:
                with self.subTest(type=t, size=n):
                    if n == 0:
                        continue # XXX Sandia-OSS
                        ivars = shmem.zeros(0, t)
                        flag = shmem.test_all(ivars, '==', 0)
                        self.assertTrue(flag)
                        values = np.zeros(0, t)
                        flag = shmem.test_all_vector(
                            ivars, '==', values,
                        )
                        self.assertTrue(flag)
                        #
                        ivars = shmem.zeros(3, t)
                        status = np.ones(3, 'i')
                        index = shmem.test_all(
                            ivars, '==', 0, status=status,
                        )
                        self.assertTrue(flag)
                        values = np.zeros(3, t)
                        flag = shmem.test_all_vector(
                            ivars, '==', values, status=status,
                        )
                        self.assertTrue(flag)
                        continue
                    #
                    ivars = shmem.zeros(n, t)
                    values = np.zeros(n, t)
                    flag = shmem.test_all(ivars, '==', 0)
                    self.assertTrue(flag)
                    flag = shmem.test_all_vector(ivars, '==', values)
                    self.assertTrue(flag)
                    src = np.full(n, mype + 1, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    flag = shmem.test_all(ivars, shmem.CMP_NE, 0)
                    self.assertTrue(flag)
                    flag = shmem.test_all_vector(ivars, shmem.CMP_NE, values)
                    self.assertTrue(flag)
                    #
                    src = np.ones(n, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    cmp_l = "eq ne lt le ge gt".split()
                    v1_l = [1, 0, 2, 1, 0, 0]
                    v2_l = [1, 2, 3, 2, 1, 0]
                    for cmp, v1, v2 in zip(cmp_l, v1_l, v2_l):
                        flag = shmem.test_all(ivars, cmp, v1)
                        self.assertTrue(flag)
                        flag = shmem.test_all(ivars, cmp, v2)
                        self.assertTrue(flag)
                        v1vec = np.full(n, v1, t)
                        v2vec = np.full(n, v2, t)
                        flag = shmem.test_all_vector(ivars, cmp, v1vec)
                        self.assertTrue(flag)
                        flag = shmem.test_all_vector(ivars, cmp, v2vec)
                        self.assertTrue(flag)

    def testAny(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            for n in [0, 1, 3]:
                with self.subTest(type=t, size=n):
                    if n == 0:
                        ivars = shmem.zeros(0, t)
                        index = shmem.test_any(ivars, '==', 0)
                        self.assertEqual(index, None)
                        values = np.ones(0, t)
                        index = shmem.test_any_vector(ivars, '==', values)
                        self.assertEqual(index, None)
                        #
                        ivars = shmem.zeros(3, t)
                        status = np.ones(3, 'i')
                        index = shmem.test_any(
                            ivars, '==', 0, status=status,
                        )
                        self.assertEqual(index, None)
                        values = np.ones(3, t)
                        index = shmem.test_any_vector(
                            ivars, '==', values, status=status,
                        )
                        self.assertEqual(index, None)
                        continue
                    #
                    ivars = shmem.zeros(n, t)
                    ivars[-1] = 1
                    index = shmem.test_any(ivars, '==', 0)
                    self.assertNotEqual(index, n-1)
                    index = shmem.test_any(ivars, '==', 1)
                    self.assertEqual(index, n-1)
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    index = shmem.test_any_vector(ivars, '==', z)
                    self.assertNotEqual(index, n-1)
                    index = shmem.test_any_vector(ivars, '==', o)
                    self.assertEqual(index, n-1)
                    #
                    src = np.full(n, mype + 1, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    index = shmem.test_any(ivars, shmem.CMP_EQ, 0)
                    self.assertEqual(index, None)
                    index = shmem.test_any(ivars, shmem.CMP_NE, 0)
                    self.assertNotEqual(index, None)
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    index = shmem.test_any_vector(ivars, shmem.CMP_EQ, z)
                    self.assertEqual(index, None)
                    index = shmem.test_any_vector(ivars, shmem.CMP_NE, z)
                    self.assertNotEqual(index, None)
                    #
                    shmem.put(ivars, np.zeros(n, t), nxpe)
                    shmem.put(ivars[-1:], np.full(1, 7, t), nxpe)
                    shmem.barrier_all()
                    cmp_l = "eq ne lt le ge gt".split()
                    v1_l = [7, 0, 8, 7, 6, 5]
                    v2_l = [7, 0, 9, 8, 7, 6]
                    for cmp, v1, v2 in zip(cmp_l, v1_l, v2_l):
                        index = shmem.test_any(ivars, cmp, v1)
                        self.assertNotEqual(index, None)
                        index = shmem.test_any(ivars, cmp, v2)
                        self.assertNotEqual(index, None)
                        v1vec = np.full(n, v1, t)
                        v2vec = np.full(n, v1, t)
                        index = shmem.test_any_vector(ivars, cmp, v1vec)
                        self.assertNotEqual(index, None)
                        index = shmem.test_any_vector(ivars, cmp, v2vec)
                        self.assertNotEqual(index, None)

    def testSome(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            for n in [0, 1, 3]:
                with self.subTest(type=t, size=n):
                    if n ==0:
                        ivars = shmem.zeros(0, t)
                        index = shmem.test_some(ivars, '==', 0)
                        self.assertEqual(index, [])
                        values = np.zeros(0, t)
                        index = shmem.test_some_vector(ivars, '==', values)
                        self.assertEqual(index, [])
                        #
                        ivars = shmem.zeros(3, t)
                        status = np.ones(3, 'i')
                        index = shmem.test_some(
                            ivars, '==', 0, status=status,
                        )
                        self.assertEqual(index, [])
                        values = np.zeros(3, t)
                        index = shmem.test_some_vector(
                            ivars, '==', values, status=status,
                        )
                        self.assertEqual(index, [])
                        continue
                    #
                    ivars = shmem.zeros(n, t)
                    ivars[-1] = 1
                    index = shmem.test_some(ivars, '==', 0)
                    self.assertTrue(n-1 not in index)
                    index = shmem.test_some(ivars, '==', 1)
                    self.assertEqual(index, [n-1])
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    index = shmem.test_some_vector(ivars, '==', z)
                    self.assertTrue(n-1 not in index)
                    index = shmem.test_some_vector(ivars, '==', o)
                    self.assertEqual(index, [n-1])
                    #
                    src = np.full(n, mype + 1, t)
                    shmem.put(ivars, src, nxpe)
                    shmem.barrier_all()
                    index = shmem.test_some(ivars, shmem.CMP_EQ, 0)
                    self.assertEqual(index, [])
                    index = shmem.test_some(ivars, shmem.CMP_NE, 0)
                    self.assertNotEqual(index, [])
                    z, o = np.full(n, 0, t), np.full(n, 1, t)
                    index = shmem.test_some_vector(ivars, shmem.CMP_EQ, z)
                    self.assertEqual(index, [])
                    index = shmem.test_some_vector(ivars, shmem.CMP_NE, z)
                    self.assertNotEqual(index, [])
                    #
                    shmem.put(ivars, np.zeros(n, t), nxpe)
                    shmem.put(ivars[-1:], np.full(1, 7, t), nxpe)
                    shmem.barrier_all()
                    cmp_l = "eq ne lt le ge gt".split()
                    v1_l = [7, 0, 8, 7, 6, 5]
                    v2_l = [7, 0, 9, 8, 7, 6]
                    for cmp, v1, v2 in zip(cmp_l, v1_l, v2_l):
                        index = shmem.test_some(ivars, cmp, v1)
                        self.assertNotEqual(index, [])
                        index = shmem.test_some(ivars, cmp, v2)
                        self.assertNotEqual(index, [])
                        v1vec = np.full(n, v1, t)
                        v2vec = np.full(n, v1, t)
                        index = shmem.test_some_vector(ivars, cmp, v1vec)
                        self.assertNotEqual(index, [])
                        index = shmem.test_some_vector(ivars, cmp, v2vec)
                        self.assertNotEqual(index, [])


class TestSignal(unittest.TestCase):

    def testWait(self):
        signal = shmem.new_signal()
        signal[0] = 1
        shmem.barrier_all()
        sig = shmem.signal_fetch(signal)
        self.assertEqual(sig, 1)
        cmps = "eq ne lt le ge gt".split()
        vals = [1, 0, 2, 2, 0, 0]
        for cmp, val in zip(cmps, vals):
            sig = shmem.signal_wait_until(signal, cmp, val)
            self.assertEqual(sig, 1)


if __name__ == '__main__':
    unittest.main()
