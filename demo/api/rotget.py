from shmem4py.api import ffi
from shmem4py.api.lib import *

shmem_init()

mype = shmem_my_pe()
npes = shmem_n_pes()
nextpe = (mype + 1) % npes

src = shmem_malloc(ffi.sizeof('long'))
src = ffi.cast('long*', src)
src[0] = mype

dst = ffi.new('long*')
dst[0] = -1

shmem_barrier_all()
shmem_long_get(dst, src, 1, nextpe)

assert dst[0] == nextpe

shmem_free(src)

shmem_finalize()
