from shmem4py.api import ffi
from shmem4py.api.lib import *

shmem_init()

mype = shmem_my_pe()
npes = shmem_n_pes()

if mype == 0:
    for i in range(npes):
        flag = shmem_pe_accessible(i)
        print(f"From PE {mype}: PE {i} is ", end='')
        print(f"{'' if flag else 'NOT '}", end='')
        print("accessible")

shmem_finalize()
