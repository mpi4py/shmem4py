from shmem4py.api import ffi
from shmem4py.api.lib import *

shmem_init()

mype = shmem_my_pe()
npes = shmem_n_pes()
nextpe = (mype + 1) % npes

src = ffi.new('int*')
src[0] = nextpe

dst = shmem_malloc(ffi.sizeof('int'))
dst = ffi.cast('int*', dst)
dst[0] = -1

shmem_barrier_all()
shmem_int_put(dst, src, 1, nextpe)
shmem_barrier_all()

assert dst[0] == mype

shmem_free(dst)

shmem_finalize()
