from shmem4py import shmem

mype = shmem.my_pe()
npes = shmem.n_pes()

print(f"Hello from PE {mype} of {npes}")
