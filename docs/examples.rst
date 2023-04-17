.. examples:

Usage examples
==============

Hello world
-----------

The simplest "Hello world" example analog to that of `C implementation <https://github.com/openshmem-org/osss-ucx/blob/main/example/hello.c>`_
reads::

    from shmem4py import shmem

    mype = shmem.my_pe()
    npes = shmem.n_pes()

    print(f"Hello from PE {mype} of {npes}")


It should produce the following output::

    $ oshrun -n 4 python -u hello.py
    Hello from PE 1 of 4
    Hello from PE 3 of 4
    Hello from PE 2 of 4
    Hello from PE 0 of 4


Note that unlike in C, initialization and finalization routines (`init` and `finalize`) do not need to be called explicitly.


Get a remote value
------------------

In the following example, each process (``mype``) out of ``npes`` processes,
writes its rank into ``src`` and initializes an empty ``dst`` array.
Then, each process fetches the value of ``src`` from the next process's (``mype + 1``)
memory using `get` and stores it into its own ``dst`` array. The last process gets the value
of ``src`` from the first process (``% npes``)::

    from shmem4py import shmem
    import numpy as np

    mype = shmem.my_pe()
    npes = shmem.n_pes()
    nextpe = (mype + 1) % npes

    src = shmem.empty(1, dtype='i')
    src[0] = mype

    dst = np.empty(1, dtype='i')
    dst[0] = -1

    print(f'Before data transfer rank {mype} src={src[0]} dst={dst[0]}')

    shmem.barrier_all()
    shmem.get(dst, src, nextpe)

    print(f'After data transfer rank {mype} src={src[0]} dst={dst[0]}')


The following output is expected::

    $ oshrun -n 4 python -u rotget.py
    Before data transfer rank 0 src=0 dst=-1
    Before data transfer rank 3 src=3 dst=-1
    Before data transfer rank 2 src=2 dst=-1
    Before data transfer rank 1 src=1 dst=-1
    After data transfer rank 0 src=0 dst=1
    After data transfer rank 3 src=3 dst=0
    After data transfer rank 1 src=1 dst=2
    After data transfer rank 2 src=2 dst=3

Alternatively, the same could be achieved by using `put`, where each process
can write its rank into a remote process's memory.


Broadcast an array from root to all PEs
---------------------------------------
The following code can be used to broadcast an array from a chosen rank (here ``0``, the third argument of `broadcast` routine)::

    from shmem4py import shmem

    mype = shmem.my_pe()
    npes = shmem.n_pes()

    source = shmem.zeros(npes, dtype="int32")
    dest = shmem.full(npes, -999, dtype="int32")

    if mype == 0:
        for i in range(npes):
            source[i] = i + 1

    shmem.barrier_all()

    shmem.broadcast(dest, source, 0)

    print(f"{mype}: {dest}")


The following output is expected::

    $ oshrun -np 6 python -u broadcast.py
    0: [1 2 3 4 5 6]
    1: [1 2 3 4 5 6]
    2: [1 2 3 4 5 6]
    3: [1 2 3 4 5 6]
    4: [1 2 3 4 5 6]
    5: [1 2 3 4 5 6]


Approximate the value of Pi with reductions
-------------------------------------------

The following example approximates the value of Pi following the C example given
by Sandia SOS (`pi_reduce.c <https://github.com/Sandia-OpenSHMEM/SOS/blob/main/examples/pi_reduce.c>`_)::

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


Here we can see that as the total number of points depends on the number of PEs,
the more processes we use, the more accurate the approximation is::

    $ oshrun -np 1 python -u pi.py
    Pi from [10000] points on 1 PEs: [3.1336]
    $ oshrun -np 25 python -u pi.py
    Pi from [250000] points on 25 PEs: [3.1392]
    $ oshrun -np 100 python -u pi.py
    Pi from [1000000] points on 100 PEs: [3.140364]
    $ oshrun -np 250 python -u pi.py
    Pi from [2500000] points on 250 PEs: [3.1413872]


Collect the same number of elements from each PE
---------------------------------------------------
.. hint::
    MPI programmers will see the close resemblance of `fcollect` to `MPI_Allgather <https://rookiehpc.org/mpi/docs/mpi_allgatherv/index.html>`_.

The following example gathers one element from the ``src`` array from each PE into a single array available on all the PEs.
It is a port of the `C OpenSHMEM example (fcollect.c) <https://github.com/openshmem-org/openshmem-examples/blob/master/c/fcollect.c>`_::

    from shmem4py import shmem

    npes = shmem.n_pes()
    me = shmem.my_pe()

    dst = shmem.full(npes, 10101, dtype="int32")
    src = shmem.zeros(1, dtype="int32")
    src[0] = me + 100

    print(f"BEFORE: dst[{me}/{npes}] = {dst}")

    shmem.barrier_all()
    shmem.fcollect(dst, src)
    shmem.barrier_all()

    print(f"AFTER: dst[{me}/{npes}] = {dst}")


As we can see in the output, the results are available on every PE::

   $ oshrun -np 6 python -u ./fcollect.py
    BEFORE: dst[0/6] = [10101 10101 10101 10101 10101 10101]
    BEFORE: dst[1/6] = [10101 10101 10101 10101 10101 10101]
    BEFORE: dst[2/6] = [10101 10101 10101 10101 10101 10101]
    BEFORE: dst[3/6] = [10101 10101 10101 10101 10101 10101]
    BEFORE: dst[4/6] = [10101 10101 10101 10101 10101 10101]
    BEFORE: dst[5/6] = [10101 10101 10101 10101 10101 10101]
    AFTER: dst[0/6] = [100 101 102 103 104 105]
    AFTER: dst[2/6] = [100 101 102 103 104 105]
    AFTER: dst[4/6] = [100 101 102 103 104 105]
    AFTER: dst[3/6] = [100 101 102 103 104 105]
    AFTER: dst[1/6] = [100 101 102 103 104 105]
    AFTER: dst[5/6] = [100 101 102 103 104 105]



Collect a different number of elements from each PE
---------------------------------------------------
.. hint::
    MPI programmers will see the close resemblance of `collect` to `MPI_Allgatherv <https://rookiehpc.org/mpi/docs/mpi_allgatherv/index.html>`_.

The following example gathers a different number of elements from each PE into a single array available on all the PEs.
It is a port of the `C OpenSHMEM example (collect64.c) <https://github.com/openshmem-org/openshmem-examples/blob/master/c/collect64.c>`_.
Each PE has a symmetric array of 4 elements (``[11, 12, 13, 14]``). ``me+1`` elements from each PE are collected into a single array::

    from shmem4py import shmem

    npes = shmem.n_pes()
    me = shmem.my_pe()

    src = shmem.array([11,12,13,14])
    dst = shmem.full(npes*(1+npes)//2, -1)

    shmem.barrier_all()

    shmem.collect(dst, src, me+1)

    print(f"AFTER: dst[{me}/{npes}] = {dst}")


As we can see in the output, the results are available on every PE::

    $ oshrun -np 4 python -u collect.py
    AFTER: dst[0/4] = [11 11 12 11 12 13 11 12 13 14]
    AFTER: dst[1/4] = [11 11 12 11 12 13 11 12 13 14]
    AFTER: dst[2/4] = [11 11 12 11 12 13 11 12 13 14]
    AFTER: dst[3/4] = [11 11 12 11 12 13 11 12 13 14]


Atomic conditional swap on a remote data object
-----------------------------------------------

This example is ported from the `OpenSHMEM Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_ (Example 21).
In it, the first PE to execute the conditional swap will successfully write its PE number to ``race_winner`` array on PE 0::

    from shmem4py import shmem

    race_winner = shmem.array([-1])

    mype = shmem.my_pe()
    oldval = shmem.atomic_compare_swap(race_winner, -1, mype, 0)

    if oldval == -1:
        print(f"PE {mype} was first")

As expected, the order of the PEs is not guaranteed::

    $ oshrun -np 64 python -u race_winner.py
    PE 0 was first
    $ oshrun -np 64 python -u race_winner.py
    PE 32 was first
    $ oshrun -np 64 python -u race_winner.py
    PE 32 was first
    $ oshrun -np 64 python -u race_winner.py
    PE 48 was first


Test if condition is met
------------------------

.. tip::
    Note the usage of ``wait_vars[idx:idx+1]`` to refer to a mutable slice containing one value of the array in this example.
    ``wait_vars[idx]`` would be a read-only value and cannot be updated.

This example is ported from the `OpenSHMEM Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_ (Example 40).
In this example, each non-zero PE updates a value in an array on PE ``0``. PE ``0`` returns once the first process completed the update::

    from shmem4py import shmem

    mype = shmem.my_pe()
    npes = shmem.n_pes()

    wait_vars = shmem.zeros(npes, dtype='i')

    if mype == 0:
        idx = 0
        while not shmem.test(wait_vars[idx:idx+1], shmem.CMP.NE, 0):
            idx = (idx + 1) % npes
        print(f"PE {mype} observed first update from PE {idx}")

    else:
        shmem.atomic_set(wait_vars[mype:mype+1], mype, 0)

As before, the order of the updates is not guaranteed::

    $ oshrun -np 64 python -u race_winner_test.py
    PE 0 observed first update from PE 12
    $ oshrun -np 64 python -u race_winner_test.py
    PE 0 observed first update from PE 3


All to all communication
------------------------

This example is ported from the `OpenSHMEM Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_ (Example 31).
All pairs of PEs exchange two integers::

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


We see the transposition in the destination array::

    $ oshrun -np 3 python -u alltoall.py
    0: source = [0 0 1 1 2 2]
    1: source = [3 3 4 4 5 5]
    2: source = [6 6 7 7 8 8]
    0: dest = [0 0 3 3 6 6]
    1: dest = [1 1 4 4 7 7]
    2: dest = [2 2 5 5 8 8]


Locking
-------

This example is ported from the `OpenSHMEM Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_ (Example 45).
A lock is used to make sure that only one process modifies the array on PE ``0``::

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


Alternatively, ``shmem4py`` provides a more object-oriented interface to achieve the same::

    from shmem4py import shmem

    lock = shmem.Lock()
    mype = shmem.my_pe()

    count = shmem.array([0], dtype='i')
    val = shmem.array([0], dtype='i')

    lock.acquire()
    shmem.get(val, count, 0)
    print(f"{mype}: count is {val[0]}")
    val[0] += 1
    shmem.put(count, val, 0)
    lock.release()


Both examples produce the same output::

    $ oshrun -np 7 python -u lock_oo.py
    4: count is 0
    3: count is 1
    2: count is 2
    1: count is 3
    0: count is 4
    5: count is 5
    6: count is 6