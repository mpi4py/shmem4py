.. introduction:

Introduction
============

OpenSHMEM
---------

`OpenSHMEM <http://openshmem.org/>`_ is a `Partitioned Global Address Space (PGAS) <https://en.wikipedia.org/wiki/Partitioned_global_address_space>`_
programming model that provides low-latency, high-bandwidth communication for use in parallel applications.
The OpenSHMEM project aims to standardize several implementations of the different SHMEM APIs.

OpenSHMEM programs follow a single program, multiple data (SPMD) style, where processing elements (PEs) perform computation on subdomains of the larger problem and communicate periodically to exchange information. The PEs all start at the same time, and they all run the same program. Typically, each PE performs computations on its own subdomain and communicates with other PEs to exchange information required for the next computation phase.
OpenSHMEM is optimized for low-latency data transfers and supports one-sided communication, making it ideal for applications with irregular communication patterns involving small/medium-sized data transfers.

OpenSHMEM routines provide support for

- put operations - data transfer to a different PE
- get operations - data transfer from a different PE
- remote pointers - allow for direct references to data objects owned by another PE
- atomic memory operations - such as an atomic read-and-update operation, fetch-and-increment, on a remote or local data object
- barrier synchronization
- group synchronization
- data broadcast
- data reduction
- data collection
- distributed locking of critical regions
- data and process accessibility queries to other PEs

shmem4py
--------

``shmem4py`` is a Python wrapper for the OpenSHMEM API, and requires a working OpenSHMEM implementation installed.
It is built using `CFFI <https://cffi.readthedocs.io/en/latest/>`_ for Python-C interoperability,
and uses `NumPy <https://numpy.org/>`_ arrays to represent data objects.

Symmetric variables
-------------------

OpenSHMEM relies on the concept of symmetric variables. Those variables exist on all PEs and have the same size, type and relative address.
Only symmetric variables can be accessed remotely by other PEs.
In ``shmem4py``, symmetric variables are allocated using routines such as `alloc` for raw memory allocations or
`array`, `empty`, `zeros`, `ones`, and `full` for NumPy array allocations.

.. tip::
    Python built-in data types such as `bool`, `int`, `float`, and `complex` are immutable, i.e., they cannot be modified after creation.
    As a consequence of this, ``shmem4py`` uses NumPy arrays to represent symmetric variables.

.. warning::
    Even though NumPy arrays are mutable, one has to be careful when addressing them, as the individual array elements are immutable:
        >>> a = np.ones(2)
        >>> a[0].flags.writeable
        False
    However, an array slice representing the same value returns a mutable array:
        >>> a[0:1].flags.writeable
        True


Resources
---------

We do not aim to provide a comprehensive OpenSHMEM introduction in this documentation,
focusing on the specifics of the Python bindings provided in ``shmem4py``.
For a more comprehensive introduction to OpenSHMEM, we refer to the following resources:

- `OpenSHMEM.org <http://openshmem.org/>`_
- `OpenSHMEM.org Tutorials <http://openshmem.org/site/Documentation/Tutorials>`_
- `OpenSHMEM tutorial from the 2014 OpenSHMEM Workshop <https://www.csm.ornl.gov/workshops/openshmem2013/documents/presentations_and_tutorials/Tutorials/OpenSHMEM_Tutorial_OSHWorkshop2014.pdf>`_
- `Parallel Research Kernels repository <https://github.com/ParRes/Kernels/>`_ contains some `C <https://github.com/ParRes/Kernels/tree/default/SHMEM>`_ and `Python <https://github.com/ParRes/Kernels/tree/default/PYTHON>`_ OpenSHMEM examples

Acknowledgements
----------------

Our documentation is heavily-based on the `OpenSHMEM 1.5 Specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_.
The Dockerfiles we use were initially based on `Sandia OpenSHMEM's container specification <https://github.com/Sandia-OpenSHMEM/SOS/tree/main/scripts/docker>`_.
``shmem4py`` relies on `NumPy <https://numpy.org/>`_ and `CFFI <https://cffi.readthedocs.io/en/latest/>`_.