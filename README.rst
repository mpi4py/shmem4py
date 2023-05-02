==============================
shmem4py: OpenSHMEM for Python
==============================

.. image::  https://github.com/mpi4py/shmem4py/actions/workflows/native.yml/badge.svg
   :target: https://github.com/mpi4py/shmem4py/actions/workflows/native.yml
.. image::  https://github.com/mpi4py/shmem4py/actions/workflows/containers.yml/badge.svg
   :target: https://github.com/mpi4py/shmem4py/actions/workflows/containers.yml
.. image::  https://readthedocs.org/projects/shmem4py/badge/?version=latest
   :target: https://shmem4py.readthedocs.io/en/latest/

Overview
--------

This package provides Python bindings for `OpenSHMEM <http://openshmem.org/>`_.
OpenSHMEM is a Partitioned Global Address Space (PGAS) programming model that
provides low-latency, high-bandwidth communication for use in parallel
applications. The OpenSHMEM project aims to standardize several implementations
of the different SHMEM APIs. shmem4py exposes an API which grounds on the
`OpenSHMEM 1.5 specification <http://openshmem.org/site/sites/default/site_files/OpenSHMEM-1.5.pdf>`_;
however, it also supports legacy 1.4 implementations.

Supported implementations
-------------------------

- `Cray OpenSHMEMX <https://cray-openshmemx.readthedocs.io/>`_
- `Open Source Software Solutions (OSSS) OpenSHMEM <https://github.com/openshmem-org/osss-ucx>`_
- `Open MPI OpenSHMEM <https://www.open-mpi.org/doc/v3.1/man3/OpenSHMEM.3.php>`_
- `OSHMPI <https://pmodels.github.io/oshmpi-www/>`_
- `Sandia OpenSHMEM <https://github.com/Sandia-OpenSHMEM/SOS>`_

Dependencies
------------

- `Python <https://www.python.org/>`_ 3.7 or newer
- A working `OpenSHMEM <http://openshmem.org/>`_ implementation with its dependencies
- Python modules: `CFFI <https://cffi.readthedocs.io/>`_, `NumPy <https://numpy.org/>`_

Documentation
-------------

- Read the Docs: `https://shmem4py.readthedocs.io/ <https://shmem4py.readthedocs.io/>`_


Acknowledgments
---------------

This project was partially supported by the
Extreme Computing Research Center (ECRC),
King Abdullah University of Science and Technology (KAUST).
