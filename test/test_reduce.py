from shmem4py import shmem
import numpy as np
import unittest


types_i = list('hilq')
types_u = list('HILQ')
types_f = list('fdg')
types_c = list('FD')


ops = {
    'and'  : types_u,
    'or'   : types_u,
    'xor'  : types_u,
    'max'  : types_i+types_u+types_f,
    'min'  : types_i+types_u+types_f,
    'sum'  : types_i+types_u+types_f+types_c,
    'prod' : types_i+types_u+types_f+types_c,
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
    for op in "max min sum prod".split():
        for t in types_u:
            ops[op].remove(t)


class TestReduce(unittest.TestCase):

    def testReduce(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in ops['sum']:
            tgt = shmem.array(-1, dtype=t)
            src = shmem.full(1, mype, dtype=t)
            shmem.barrier_all()
            shmem.reduce(tgt, src)
            self.assertEqual(tgt, ((npes-1)*npes)//2)

    def testReduceTeam(self):
        team = shmem.TEAM_WORLD
        mype = team.my_pe()
        npes = team.n_pes()
        for t in ops['sum']:
            tgt = shmem.array(-1, dtype=t)
            src = shmem.full(1, mype, dtype=t)
            shmem.barrier_all()
            shmem.reduce(tgt, src, team=team)
            self.assertEqual(tgt, ((npes-1)*npes)//2)

    def testReduceOp(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for op, types in ops.items():
            reducefn = ufunc[op].reduce
            for t in types:
                tgt = shmem.array(-1, dtype=t)
                src = shmem.full(1, mype+1, dtype=t)
                shmem.barrier_all()
                shmem.reduce(tgt, src, op=op)
                val = reducefn(np.arange(1, npes+1, dtype=t))
                self.assertEqual(tgt, val)

    def testReduceOpSize(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for op, types in ops.items():
            reducefn = ufunc[op].reduce
            for t in types:
                ini = np.array(-1, dtype=t)
                tgt = shmem.full(npes, ini, dtype=t)
                src = shmem.full(npes, mype+1, dtype=t)
                for size in range(npes):
                    shmem.barrier_all()
                    shmem.reduce(tgt, src, op=op, size=size)
                    val = reducefn(np.arange(1, npes+1, dtype=t))
                    self.assertTrue(np.all(tgt[:size] == val))
                    self.assertTrue(np.all(tgt[size:] == ini))


if __name__ == '__main__':
    unittest.main()
