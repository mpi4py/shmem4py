# adapted from http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf (Example 33)

from shmem4py import shmem

mype = shmem.my_pe()
npes = shmem.n_pes()

source = shmem.zeros(npes, dtype="int32")
dest = shmem.full(npes, -999, dtype="int32")

if mype == 0:
    for i in range(npes):
        source[i] = i + 1

shmem.barrier_all()

shmem.broadcast(dest, source, 0)

print(f"{mype}: {dest}")

shmem.free(source)
shmem.free(dest)
