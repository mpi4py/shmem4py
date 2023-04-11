from shmem4py import shmem
import unittest


class TestQuery(unittest.TestCase):

    def testQueryThread(self):
        provided = shmem.query_thread()
        self.assertTrue(
            provided in (
                shmem.THREAD_SINGLE,
                shmem.THREAD_FUNNELED,
                shmem.THREAD_SERIALIZED,
                shmem.THREAD_MULTIPLE,
            )
        )

    def testPEAccessible(self):
        flag = shmem.pe_accessible(shmem.my_pe())
        self.assertTrue(flag)

    def testAddrAccessibleCData(self):
        addr = shmem.new_array(1, 'i')
        flag = shmem.addr_accessible(addr, shmem.my_pe())
        shmem.free(addr)
        self.assertTrue(flag)

    def testAddrAccessibleNumPy(self):
        addr = shmem.empty(1, dtype='i')
        flag = shmem.addr_accessible(addr, shmem.my_pe())
        shmem.free(addr)
        self.assertTrue(flag)


if __name__ == '__main__':
    unittest.main()
