# adapted from https://github.com/openshmem-org/openshmem-examples/blob/master/c/fcollect.c

from shmem4py import shmem

npes = shmem.n_pes()
me = shmem.my_pe()

dst = shmem.full(npes, 10101, dtype="int32")
src = shmem.zeros(1, dtype="int32")
src[0] = me + 100

print(f"BEFORE: dst[{me}/{npes}] = {dst}")

shmem.barrier_all()
shmem.fcollect(dst, src)
shmem.barrier_all()

print(f"AFTER: dst[{me}/{npes}] = {dst}")

shmem.free(dst)
shmem.free(src)
