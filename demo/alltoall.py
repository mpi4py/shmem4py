# adapted from http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf (Example 31)

from shmem4py import shmem

mype = shmem.my_pe()
npes = shmem.n_pes()

count = 2

source = shmem.zeros(count*npes, dtype="int32")
dest = shmem.full(count*npes, 9999, dtype="int32")

for pe in range(0, npes):
    for i in range(0, count):
        source[(pe*count) + i] = mype*npes + pe

print(f"{mype}: source = {source}")

team = shmem.Team(shmem.TEAM_WORLD)
team.sync()

shmem.alltoall(dest, source, 2, team)

print(f"{mype}: dest = {dest}")

# verify results
for pe in range(0, npes):
    for i in range(0, count):
        if dest[(pe*count) + i] != pe*npes + mype:
            print(f"[{mype}] ERROR: dest[{(pe*count) + i}]={dest[(pe*count) + i]}, should be {pe*npes + mype}")

shmem.free(dest)
shmem.free(source)
