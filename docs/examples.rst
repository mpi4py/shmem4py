.. examples:

Usage examples
==============

Hello world
-----------

The simplest "Hello world" example analog to that of `C implementation <https://github.com/openshmem-org/osss-ucx/blob/main/example/hello.c>`_
reads:

.. literalinclude:: ../demo/hello.py
    :language: python
    :linenos:

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
of ``src`` from the first process (``% npes``):

.. literalinclude:: ../demo/rotget.py
    :language: python
    :linenos:

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
The following code can be used to broadcast an array from a chosen rank (here ``0``, the third argument of `broadcast` routine):

.. literalinclude:: ../demo/broadcast.py
    :language: python
    :lines: 3-
    :linenos:

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
by Sandia SOS (`pi_reduce.c <https://github.com/Sandia-OpenSHMEM/SOS/blob/main/examples/pi_reduce.c>`_):

.. literalinclude:: ../demo/pi.py
    :language: python
    :lines: 3-
    :linenos:

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
It is a port of the `C OpenSHMEM example (fcollect.c) <https://github.com/openshmem-org/openshmem-examples/blob/master/c/fcollect.c>`_:

.. literalinclude:: ../demo/fcollect.py
    :language: python
    :lines: 3-
    :linenos:

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
Each PE has a symmetric array of 4 elements (``[11, 12, 13, 14]``). ``me+1`` elements from each PE are collected into a single array:

.. literalinclude:: ../demo/collect.py
    :language: python
    :lines: 3-
    :linenos:

As we can see in the output, the results are available on every PE::

    $ oshrun -np 4 python -u collect.py
    AFTER: dst[0/4] = [11 11 12 11 12 13 11 12 13 14]
    AFTER: dst[1/4] = [11 11 12 11 12 13 11 12 13 14]
    AFTER: dst[2/4] = [11 11 12 11 12 13 11 12 13 14]
    AFTER: dst[3/4] = [11 11 12 11 12 13 11 12 13 14]


Atomic conditional swap on a remote data object
-----------------------------------------------

This example is ported from the `OpenSHMEM Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_ (Example 21).
In it, the first PE to execute the conditional swap will successfully write its PE number to ``race_winner`` array on PE 0:

.. literalinclude:: ../demo/race_winner.py
    :language: python
    :lines: 3-
    :linenos:

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
In this example, each non-zero PE updates a value in an array on PE ``0``. PE ``0`` returns once the first process completed the update:

.. literalinclude:: ../demo/race_winner_test.py
    :language: python
    :lines: 3-
    :linenos:

As before, the order of the updates is not guaranteed::

    $ oshrun -np 64 python -u race_winner_test.py
    PE 0 observed first update from PE 12
    $ oshrun -np 64 python -u race_winner_test.py
    PE 0 observed first update from PE 3


All to all communication
------------------------

This example is ported from the `OpenSHMEM Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_ (Example 31).
All pairs of PEs exchange two integers:

.. literalinclude:: ../demo/alltoall.py
    :language: python
    :lines: 3-
    :linenos:

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
A lock is used to make sure that only one process modifies the array on PE ``0``:

.. literalinclude:: ../demo/lock.py
    :language: python
    :lines: 3-
    :linenos:

Alternatively, ``shmem4py`` provides a more object-oriented interface to achieve the same:

.. literalinclude:: ../demo/lock_oo.py
    :language: python
    :lines: 3-
    :linenos:

Both examples produce the same output::

    $ oshrun -np 7 python -u lock_oo.py
    4: count is 0
    3: count is 1
    2: count is 2
    1: count is 3
    0: count is 4
    5: count is 5
    6: count is 6