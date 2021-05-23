from shmem4py.api import ffi
from shmem4py.api.lib import *

shmem_init()

mype = shmem_my_pe()
npes = shmem_n_pes()

print(f"Hello from PE {mype} of {npes}")

shmem_finalize()
