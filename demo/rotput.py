from shmem4py import shmem
import numpy as np

mype = shmem.my_pe()
npes = shmem.n_pes()
nextpe = (mype + 1) % npes

src = np.empty(1, dtype='i')
src[0] = nextpe

dst = shmem.empty(1, dtype='i')
dst[0] = -1

shmem.barrier_all()
shmem.put(dst, src, nextpe)
shmem.barrier_all()

assert dst[0] == mype
