from shmem4py import shmem
import numpy as np

mype = shmem.my_pe()
npes = shmem.n_pes()
nextpe = (mype + 1) % npes

src = shmem.empty(1, dtype='i')
src[0] = mype

dst = np.empty(1, dtype='i')
dst[0] = -1

shmem.barrier_all()
shmem.get(dst, src, nextpe)

assert dst[0] == nextpe
