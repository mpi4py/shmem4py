from shmem4py import shmem
import numpy as np


class CoArrayRef:
    """
    CoArray reference.
    """

    __slots__ = ('base', 'pe')

    def __init__(self, base, pe):
        npes = shmem.n_pes()
        if pe < 0:
            pe += npes
        assert 0 <= pe < npes
        self.base = base
        self.pe = pe

    def __len__(self, index):
        return self.base.size

    def __getitem__(self, index):
        base = self.base
        pe = self.pe

        #local = shmem.ptr(base, pe)
        #if local is not None:
        #    return local[index]

        if isinstance(index, (int, np.integer)):
            if index < 0:
                index += base.size
            value = np.empty(1, base.dtype)
            shmem.get(value, base[index:index+1], pe)
            return value[0]

        if isinstance(index, slice):
            start, stop, step = index.indices(base.size)
            length = len(range(start, stop, step))
            value = np.empty(length, base.dtype)
            if step > 0:
                offset = start
                stride = step
            else:
                offset = start - step + length * step
                stride = -step
            if stride == 1:
                shmem.get(value, base[offset:], pe)
            else:
                shmem.iget(value, base[offset:], pe, tst=1, sst=stride)
            if step < 0:
                value = np.flip(value)
            return value

        if index in (np.newaxis, Ellipsis, ()):
            if index == np.newaxis:
                shape = (1, base.size)
            else:
                shape = base.size
            value = np.empty(shape, base.dtype)
            shmem.get(value, base, pe)
            return value

        raise TypeError

    def __setitem__(self, index, value):
        base = self.base
        pe = self.pe

        #local = shmem.ptr(base, pe)
        #if local is not None:
        #    local[index] = value
        #    return

        def _value_array(value, dtype, length):
            value = np.asarray(value, dtype)
            if value.size == 1:
                return value.repeat(length)
            value = np.ascontiguousarray(value)
            assert value.size == length
            return value

        if isinstance(index, (int, np.integer)):
            if index < 0:
                index += base.size
            value = _value_array(value, base.dtype, 1)
            shmem.put(base[index:index+1], value, pe)
            shmem.quiet()
            return

        if isinstance(index, slice):
            start, stop, step = index.indices(base.size)
            length = len(range(start, stop, step))
            value = _value_array(value, base.dtype, length)
            if step > 0:
                offset = start
                stride = step
            else:
                offset = start - step + length * step
                stride = -step
                value = np.flip(value).copy()
            if stride == 1:
                shmem.put(base[offset:], value, pe)
                shmem.quiet()
            else:
                shmem.iput(base[offset:], value, pe, tst=stride, sst=1)
                shmem.quiet()
            return

        if index in (np.newaxis, Ellipsis, ()):
            value = _value_array(value, base.dtype, base.size)
            shmem.put(base, value, pe)
            shmem.quiet()
            return

        raise TypeError


class CoArray:

    """
    CoArray wrapper.
    """

    __slots__ = ('base',)

    def __init__(self, base):
        self.base = base

    def __call__(self, pe):
        return CoArrayRef(self.base, pe)

    def __len__(self):
        return shmem.n_pes()

    def __getitem__(self, pe):
        return CoArrayRef(self.base, pe)

    def __setitem__(self, pe, value):
        CoArrayRef(self.base, pe)[...] = value


# ---
from shmem4py import shmem
import numpy as np
import unittest


types = list('bhilqBHILQfdg')
types += [f'i{1<<i}' for i in range(4)]
types += [f'u{1<<i}' for i in range(4)]
types += [f'f{1<<i}' for i in range(2,4)]


class TestCoArray(unittest.TestCase):

    def testGetItem(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        for t in types:
            size = 5
            mold = lambda s: np.arange(s, s+size, dtype=t)
            base = shmem.array(mold(mype))
            coarray = CoArray(base)
            shmem.barrier_all()
            for pe in range(npes):
                check = mold(pe)
                for index in range(-size, size):
                    self.assertTrue(np.all(
                        coarray(pe)[index] == check[index]
                    ))
                for index in (np.newaxis, ..., ()):
                    self.assertTrue(np.all(
                        coarray(pe)[index] == check[index]
                    ))
                self.assertTrue(np.all(
                    coarray(pe)[:] == check[:]
                ))
                self.assertTrue(np.all(
                    coarray(pe)[::1] == check[::1]
                ))
                self.assertTrue(np.all(
                    coarray(pe)[::2] == check[::2]
                ))
                self.assertTrue(np.all(
                    coarray(pe)[::-1] == check[::-1]
                ))
                self.assertTrue(np.all(
                    coarray(pe)[::-2] == check[::-2]
                ))
                for a in range(-size, size):
                    for b in range(-size, size):
                        for s in range(-size, size):
                            if s == 0: continue
                            self.assertTrue(np.all(
                                coarray(pe)[a:b:s] == check[a:b:s]
                            ))

    def testSetItem(self):
        mype = shmem.my_pe()
        npes = shmem.n_pes()
        nxpe = (mype + 1) % npes
        for t in types:
            size = 5
            init = np.array(-1, dtype=t)
            base = shmem.full(size, init, dtype=t)
            coarray = CoArray(base)
            shmem.barrier_all()

            for index in range(-size, size):
                shmem.sync_all()
                coarray(nxpe)[index] = nxpe
                shmem.sync_all()
                self.assertTrue(np.all(base[index] == mype))
                coarray(nxpe)[index] = init.repeat(1)
                shmem.sync_all()
                self.assertTrue(np.all(base == init))

            for index in (np.newaxis, ..., ()):
                shmem.sync_all()
                coarray(nxpe)[index] = nxpe
                shmem.sync_all()
                self.assertTrue(np.all(base[index] == mype))
                coarray(nxpe)[index] = init.repeat(2*size)[::2]
                shmem.sync_all()
                self.assertTrue(np.all(base == init))

            for a in range(-size, size):
                for b in range(-size, size):
                    for s in range(-size, size):
                        if s == 0: continue
                        shmem.sync_all()
                        coarray(nxpe)[a:b:s] = nxpe
                        shmem.sync_all()
                        self.assertTrue(np.all(base[a:b:s] == mype))
                        n = len(range(*slice(a,b,s).indices(size)))
                        coarray(nxpe)[a:b:s] = init.repeat(n)
                        shmem.sync_all()
                        self.assertTrue(np.all(base == init))


if __name__ == '__main__':
    unittest.main()
