# adapted from http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf (Example 21)

from shmem4py import shmem

race_winner = shmem.array([-1])

mype = shmem.my_pe()
oldval = shmem.atomic_compare_swap(race_winner, -1, mype, 0)

if oldval == -1:
    print(f"PE {mype} was first")

shmem.free(race_winner)
