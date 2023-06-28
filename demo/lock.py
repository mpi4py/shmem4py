# adapted from http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf (Example 45)

import numpy as np
from shmem4py import shmem

lock = shmem.new_lock()
mype = shmem.my_pe()

val = np.array([0], dtype='i')
count = shmem.array([0], dtype='i')
shmem.barrier_all()

shmem.set_lock(lock)
shmem.get(val, count, 0)
print(f"{mype}: count is {val[0]}")
val[0] += 1
shmem.put(count, val, 0)
shmem.clear_lock(lock)

shmem.del_lock(lock)
shmem.free(count)
