# adapted from http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf (Example 40)

from shmem4py import shmem

mype = shmem.my_pe()
npes = shmem.n_pes()
if npes == 1:
    exit(0) # test requires at least 2 PEs

wait_vars = shmem.zeros(npes, dtype='i')

if mype == 0:
    idx = 0
    while not shmem.test(wait_vars[idx:idx+1], shmem.CMP.NE, 0):
        idx = (idx + 1) % npes
    print(f"PE {mype} observed first update from PE {idx}")

else:
    shmem.atomic_set(wait_vars[mype:mype+1], mype, 0)

shmem.free(wait_vars)
