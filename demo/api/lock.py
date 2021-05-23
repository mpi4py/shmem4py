from shmem4py.api import ffi
from shmem4py.api.lib import *
from time import sleep

shmem_init()

mype = shmem_my_pe()
npes = shmem_n_pes()

L = shmem_malloc(ffi.sizeof('long'))
L = ffi.cast('long*', L)
L[0] = 0

shmem_barrier_all()

sleep(mype/4)

shmem_set_lock(L)
print(f"[{mype}]: after sleep({mype/4:.2f}) and set-lock")
shmem_clear_lock(L)

shmem_free(L)

shmem_finalize()
