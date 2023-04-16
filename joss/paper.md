---
title: 'shmem4py: OpenSHMEM for Python'
tags:
  - Python
  - PGAS
  - OpenSHMEM
  - shared memory
  - High Performance Computing
authors:
  - name: Marcin Rogowski
    orcid: 0000-0002-5662-2082
    equal-contrib: true
    corresponding: true
    affiliation: 1
  - name: Lisandro Dalcin
    orcid: 0000-0001-8086-0155
    equal-contrib: true
    affiliation: 1
  - name: Jeff R. Hammond
    orcid: 0000-0003-3181-8190
    equal-contrib: false
    affiliation: 2
  - name: David E. Keyes
    orcid: 0000-0002-4052-7224
    equal-contrib: false
    affiliation: 1
affiliations:
 - name: King Abdullah University of Science and Technology, Saudi Arabia
   index: 1
 - name: NVIDIA Helsinki Oy, Finland
   index: 2
date: 13 April 2023
bibliography: paper.bib

---

# Summary

`shmem4py` brings the Partitioned Global Address Space (PGAS) programming model to Python by exposing the functionality of the OpenSHMEM Application Programming Interface (API) specification. The feature set includes one-sided communication, shared memory access, atomic memory operations, and collective operations. The Python implementation of `shmem4py` emphasizes using NumPy arrays, providing convenient access to the symmetric memory allocations central to OpenSHMEM's programming model. Thanks to Python's versatility and OpenSHMEM implementations' focus on performance, `shmem4py` offers a seamless experience on a variety of hardware, from laptops to supercomputers, and for a wide range of applications and users. `shmem4py` API grounds in OpenSHMEM 1.5 specification; however, it also supports legacy 1.4 implementations.

# Statement of Need

Python applications can be scaled to multiple processes and compute nodes in various ways.
When working on a single node, the `multiprocessing` or `concurrent.futures` packages from the Python standard library offer solutions for task-based parallelism. As we expand beyond a single node, more advanced frameworks like Dask [@dask], Ray [@ray] or `mpi4py.futures` [@mpi4py.futures] are commonly used. Typically, these high-level frameworks handle interprocess communication transparently to the user.

More challenging applications often require specialized communication patterns. In those cases, Python applications can leverage communication frameworks originally designed for high-performance computing. One such example is `mpi4py` [@mpi4py], which offers MPI bindings for Python.
`shmem4py` adopts a similar approach, providing Python bindings to OpenSHMEM [@introducing-shmem] implementations with a Python-centric and high-level API built on top of a low-level CFFI [@cffi] module.
This way, `shmem4py` is accessible to a diverse audience while offering a proven programming model with reliable performance.

`shmem4py` complements `mpi4py` in the same way that OpenSHMEM complements MPI.
MPI is extremely popular in high-performance computing because of its combination of a rich feature set and generality. OpenSHMEM is based on a different philosophy, which provides a smaller set of features that better match high-performance computing system hardware capabilities. For example, OpenSHMEM one-sided communication and atomic operations are aligned with networking capabilities such as remote direct memory access (RDMA) such that no intervention is required on the remote side [@mvapich-openshmem-perf]. In contrast, MPI's one-sided communication functionality includes many more features, some of which are known to make implementations based strictly on RDMA more difficult [@casper; @oshmpi]. Another aspect of the tradeoff between generality and close-to-hardware features is observed in the context of specialized processors, such as GPUs. It has been shown that OpenSHMEM-like APIs can be implemented natively on GPUs, e.g., NVSHMEM [@nvshmem; @nvshmem-ib]. On the other hand, implementing MPI send and receive operations in the same context poses significant challenges.
In fact, `shmem4py` will provide the backbone for future extensions supporting inter-GPU communication.

We envision two distinct groups of users that may be interested in `shmem4py`.
The first, and likely most numerous, group includes Python programmers who lack the expertise or the time to write low-level code in C and have applications well-suited for the PGAS paradigm.
The second group comprises high-performance computing professionals familiar with OpenSHMEM who want to prototype or port parts of their applications to Python.
Both groups of users can benefit greatly from the ease of development in Python, `shmem4py`'s convenience functions for manipulating NumPy arrays in symmetric memory, and all of OpenSHMEM features.
We also expect that current users of `mpi4py` may want to try `shmem4py` as a complementary communication model for the same reasons that OpenSHMEM is used alongside MPI.

# Supported OpenSHMEM Implementations

The `shmem4py` package supports, and is tested with, all major implementations of the OpenSHMEM specification:

- Cray OpenSHMEMX
- Open MPI OpenSHMEM
- Open Source Software Solutions (OSSS) OpenSHMEM
- OSHMPI
- Sandia OpenSHMEM

# Acknowledgements

The authors thank the KAUST Supercomputing Laboratory for their computing resources.

# References
