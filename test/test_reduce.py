from shmem4py import shmem
import numpy as np
import unittest


types_i = list('bhilq')
types_u = list('BHILQ')
types_f = list('fdg')
types_c = list('FD')

if shmem.info_get_version() < (1, 5):
    types_i.remove('b')
    types_u.remove('B')

ops = {
    shmem.OP_AND  : types_u,
    shmem.OP_OR   : types_u,
    shmem.OP_XOR  : types_u,
    shmem.OP_MAX  : types_i+types_u+types_f,
    shmem.OP_MIN  : types_i+types_u+types_f,
    shmem.OP_SUM  : types_i+types_u+types_f+types_c,
    shmem.OP_PROD : types_i+types_u+types_f+types_c,
}

ufunc = {
    'and'  : np.bitwise_and,
    'or'   : np.bitwise_or,
    'xor'  : np.bitwise_xor,
    'max'  : np.maximum,
    'min'  : np.minimum,
    'sum'  : np.add,
    'prod' : np.multiply,
}

if shmem.info_get_version() < (1, 5):
    for op in map(shmem.OP, "max min sum prod".split()):
        for t in types_u:
            ops[op].remove(t)


class TestReduce(unittest.TestCase):

    def testReduce(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in ops['sum']:
            with self.subTest(type=t):
                ini = np.array(-1).astype(t)
                tgt = shmem.array(ini, dtype=t)
                src = shmem.full(1, mype, dtype=t)
                shmem.barrier_all()
                shmem.reduce(tgt, src)
                self.assertEqual(tgt, ((npes-1)*npes)//2)
                shmem.free(tgt)
                shmem.free(src)

    def testReduceTeam(self):
        team = shmem.TEAM_WORLD
        mype = team.my_pe()
        npes = team.n_pes()
        for t in ops['sum']:
            with self.subTest(type=t):
                ini = np.array(-1).astype(t)
                tgt = shmem.array(ini, dtype=t)
                src = shmem.full(1, mype, dtype=t)
                shmem.barrier_all()
                shmem.reduce(tgt, src, team=team)
                self.assertEqual(tgt, ((npes-1)*npes)//2)
                shmem.free(tgt)
                shmem.free(src)

    def testReduceOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for op, types in ops.items():
            reducefn = ufunc[op].reduce
            for t in types:
                with self.subTest(type=t, op=op):
                    ini = np.array(-1).astype(t)
                    val = reducefn(np.arange(1, npes+1, dtype=t), dtype=t)
                    tgt = shmem.full(2, ini, dtype=t)
                    src = shmem.full(1, mype+1, dtype=t)
                    shmem.barrier_all()
                    shmem.reduce(tgt, src, op=op)
                    if op == 'prod' and t in (types_f+types_c):
                        self.assertTrue(np.allclose(tgt[0], val))
                    else:
                        self.assertEqual(tgt[0], val)
                    self.assertEqual(tgt[1], ini)
                    shmem.free(tgt)
                    shmem.free(src)

    def testReduceOpSize(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for op, types in ops.items():
            reducefn = ufunc[op].reduce
            for t in types:
                ini = np.array(-1).astype(t)
                val = reducefn(np.arange(1, npes+1, dtype=t), dtype=t)
                tgt = shmem.full(npes+2, ini, dtype=t)
                src = shmem.full(npes+2, mype+1, dtype=t)
                for size in range(npes+2):
                    with self.subTest(type=t, op=op, size=size):
                        shmem.barrier_all()
                        shmem.reduce(tgt, src, op=op, size=size)
                        if op == 'prod' and t in (types_f+types_c):
                            self.assertTrue(np.allclose(tgt[:size], val))
                        else:
                            self.assertTrue(np.all(tgt[:size] == val))
                        self.assertTrue(np.all(tgt[size:] == ini))
                shmem.free(tgt)
                shmem.free(src)

    def testOpReduce(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for op, types in ops.items():
            reducefn = ufunc[op].reduce
            for t in types:
                with self.subTest(type=t, op=op):
                    ini = np.array(-1).astype(t)
                    val = reducefn(np.arange(1, npes+1, dtype=t), dtype=t)
                    tgt = shmem.full(2, ini, dtype=t)
                    src = shmem.full(1, mype+1, dtype=t)
                    shmem.barrier_all()
                    shmem_reduce = getattr(shmem, f'{op}_reduce')
                    shmem_reduce(tgt, src)
                    if op == 'prod' and t in (types_f+types_c):
                        self.assertTrue(np.allclose(tgt[0], val))
                    else:
                        self.assertEqual(tgt[0], val)
                    self.assertEqual(tgt[1], ini)
                    shmem.free(tgt)
                    shmem.free(src)


if __name__ == '__main__':
    unittest.main()
