from shmem4py import shmem
import numpy as np
import unittest


types = list('bhilqBHILQfdgFD')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]

op_name = {
    shmem.SIGNAL_SET: 'set',
    shmem.SIGNAL_ADD: 'add',
}

@unittest.skipIf('OSHMPI' in shmem.VENDOR_STRING, 'OSHMPI')
@unittest.skipIf(shmem.SIGNAL_SET == shmem.SIGNAL_ADD, 'put-with-signal')
class TestSignal(unittest.TestCase):

    def testPutSignal(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for ctx in (None, shmem.CTX_DEFAULT):
            for op in (shmem.SIGNAL_SET, shmem.SIGNAL_ADD):
                sig_addr = shmem.new_signal()
                for i, t in enumerate(types):
                    with self.subTest(type=t, op=op_name[op], ctx=bool(ctx)):
                        signal = 1 if (op == shmem.SIGNAL_ADD) else i+1
                        result = i+1
                        src = np.full(2, nxpe, dtype=t)
                        dst = shmem.full(2, -1, dtype=t)
                        shmem.barrier_all()
                        shmem.put_signal(
                            dst, src, nxpe,
                            sig_addr, signal, op,
                            ctx=ctx)
                        shmem.barrier_all()
                        value = shmem.signal_fetch(sig_addr)
                        self.assertEqual(dst[0], mype)
                        self.assertEqual(dst[1], mype)
                        self.assertEqual(value, result)
                        shmem.free(dst)
                shmem.del_signal(sig_addr)

    def testPutSignalNBI(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for ctx in (None, shmem.CTX_DEFAULT):
            for op in (shmem.SIGNAL_SET, shmem.SIGNAL_ADD):
                sig_addr = shmem.new_signal()
                for i, t in enumerate(types):
                    with self.subTest(type=t, op=op_name[op], ctx=bool(ctx)):
                        signal = 1 if (op == shmem.SIGNAL_ADD) else i+1
                        result = i+1
                        src = np.full(2, nxpe, dtype=t)
                        dst = shmem.full(2, -1, dtype=t)
                        shmem.barrier_all()
                        shmem.put_signal_nbi(
                            dst, src, nxpe,
                            sig_addr, signal, op,
                            ctx=ctx)
                        shmem.quiet()
                        shmem.barrier_all()
                        value = shmem.signal_fetch(sig_addr)
                        self.assertEqual(dst[0], mype)
                        self.assertEqual(dst[1], mype)
                        self.assertEqual(value, result)
                        shmem.free(dst)
                shmem.del_signal(sig_addr)


if __name__ == '__main__':
    unittest.main()
