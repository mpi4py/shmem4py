# adapted from https://github.com/openshmem-org/openshmem-examples/blob/master/c/collect64.c

from shmem4py import shmem

npes = shmem.n_pes()
me = shmem.my_pe()

src = shmem.array([11, 12, 13, 14])
dst = shmem.full(npes*(1+npes)//2, -1)

shmem.barrier_all()

shmem.collect(dst, src, me+1)

print(f"AFTER: dst[{me}/{npes}] = {dst}")

shmem.free(src)
shmem.free(dst)
