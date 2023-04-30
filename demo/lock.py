# adapted from http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf (Example 45)

from shmem4py import shmem

lock = shmem.new_lock()
mype = shmem.my_pe()

count = shmem.array([0], dtype='i')
val = shmem.array([0], dtype='i')

shmem.set_lock(lock)
shmem.get(val, count, 0)
print(f"{mype}: count is {val[0]}")
val[0] += 1
shmem.put(count, val, 0)
shmem.clear_lock(lock)

shmem.del_lock(lock)
shmem.free(count)
shmem.free(val)
