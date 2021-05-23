from shmem4py import shmem

mype = shmem.my_pe()
npes = shmem.n_pes()

if mype == 0:
    for i in range(npes):
        flag = shmem.pe_accessible(i)
        print(f"From PE {mype}: PE {i} is ", end='')
        print(f"{'' if flag else 'NOT '}", end='')
        print("accessible")
