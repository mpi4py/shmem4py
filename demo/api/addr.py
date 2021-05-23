from shmem4py.api import ffi
from shmem4py.api.lib import *

shmem_init()

loc_target = ffi.new('int*')
shm_target = shmem_malloc(ffi.sizeof('int'))

mype = shmem_my_pe()
npes = shmem_n_pes()
pe = (mype + 1) % npes

if pe != mype:
    assert shmem_addr_accessible(loc_target, pe) == 0
    assert shmem_addr_accessible(shm_target, pe) == 1

shmem_free(shm_target)

shmem_finalize()
