# adapted from https://github.com/Sandia-OpenSHMEM/SOS/blob/main/examples/pi_reduce.c

from shmem4py import shmem
import random

RAND_MAX = 2147483647
NUM_POINTS = 10000

inside = shmem.zeros(1, dtype='i')
total = shmem.zeros(1, dtype='i')

myshmem_n_pes = shmem.n_pes()
me = shmem.my_pe()

random.seed(1+me)

for _ in range(0, NUM_POINTS):
    x = random.randint(0, RAND_MAX)/RAND_MAX
    y = random.randint(0, RAND_MAX)/RAND_MAX

    total[0] += 1
    if x*x + y*y < 1:
        inside[0] += 1

shmem.barrier_all()

shmem.sum_reduce(inside, inside)
shmem.sum_reduce(total, total)

if me == 0:
    approx_pi = 4.0*inside/total
    print(f"Pi from {total} points on {myshmem_n_pes} PEs: {approx_pi}")

shmem.free(inside)
shmem.free(total)
