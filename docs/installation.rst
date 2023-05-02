.. installation:

Installation
============

Requirements
------------
A working OpenSHMEM implementation is required. Currently,
`Cray OpenSHMEMX <https://cray-openshmemx.readthedocs.io/>`_,
`Open Source Software Solutions (OSSS) OpenSHMEM <https://github.com/openshmem-org/osss-ucx>`_,
`Open MPI OpenSHMEM`_,
`OSHMPI`_, and
`Sandia OpenSHMEM`_
are supported.
Generally speaking, ``shmem4py`` will be installed using the OpenSHMEM
implementation's ``oshcc`` wrapper found in the ``$PATH``.

For an example setup of ``shmem4py`` using the OSHMPI/MPICH backend, see
`INSTALL.rst <https://github.com/mpi4py/shmem4py/blob/master/INSTALL.rst>`_.


Containers
----------
We encourage users to use Docker/Podman containers or follow the steps executed in the
`Dockerfiles <https://github.com/mpi4py/shmem4py/tree/master/docker>`_. Containers
based on those files are meant to show minimal configurations for building and running
``shmem4py`` with different OpenSHMEM implementations. Those images are used in GitHub
Actions CI/CD and we consider them tested configurations.
Currently, we test with OSSS OpenSHMEM, Open MPI OpenSHMEM, OSHMPI and Sandia OpenSHMEM
on the latest releases of Fedora and Ubuntu.


Recommended versions
--------------------
There exist many combinations of the operating system and software package
versions that may work with ``shmem4py``. We recommend to use the combinations
which are tested in ``shmem4py``'s CI/CD pipeline. As of 28/04/2023, the
following package versions all work correctly:

+-----------------------------+----------------------+-----------------------------------------+-----------------------------------+----------------------+
| **OpenSHMEM distribution**  | **Operating system** | **Required packages (package manager)** | **Required packages (make)**      | **Dockerfile**       |
+-----------------------------+----------------------+-----------------------------------------+-----------------------------------+----------------------+
| `Open MPI OpenSHMEM`_ 4.1.4 | Fedora 37            | Python 3.11                             | `UCX`_ latest                     | `oshmem_fedora`_     |
|                             +----------------------+-----------------------------------------+-----------------------------------+----------------------+
|                             | Ubuntu 22.04         | Python 3.10                             | `UCX`_ latest                     | `oshmem_ubuntu`_     |
+-----------------------------+----------------------+-----------------------------------------+-----------------------------------+----------------------+
| `OSHMPI`_ latest            | Fedora 37            | Python 3.11, MPICH 4.0                  |                                   | `oshmpi_fedora`_     |
|                             +----------------------+-----------------------------------------+-----------------------------------+----------------------+
|                             | Ubuntu 22.04         | Python 3.10, MPICH 4.0                  |                                   | `oshmpi_ubuntu`_     |
+-----------------------------+----------------------+-----------------------------------------+-----------------------------------+----------------------+
| `OSSS OpenSHMEM`_ latest    | Fedora 37            | Python 3.11, PMIX 4.1.2                 | `Open MPI`_ 4.1.4, `UCX`_ latest  | `osss_fedora`_       |
|                             +----------------------+-----------------------------------------+-----------------------------------+----------------------+
|                             | Ubuntu 22.04         | Python 3.10, PMIX 4.1.2                 | `Open MPI`_ 4.1.4, `UCX`_ latest  | `osss_ubuntu`_       |
+-----------------------------+----------------------+-----------------------------------------+-----------------------------------+----------------------+
| `Sandia OpenSHMEM`_ latest  | Fedora 37            | Python 3.11, MPICH 4.0                  | `libfabric`_ latest               | `sos_fedora`_        |
|                             +----------------------+-----------------------------------------+-----------------------------------+----------------------+
|                             | Ubuntu 22.04         | Python 3.10, MPICH 4.0                  | `libfabric`_ latest               | `sos_ubuntu`_        |
+-----------------------------+----------------------+-----------------------------------------+-----------------------------------+----------------------+

.. _Open MPI OpenSHMEM: https://www.open-mpi.org/doc/v3.1/man3/OpenSHMEM.3.php
.. _Open MPI: https://www.open-mpi.org/
.. _OSHMPI: https://pmodels.github.io/oshmpi-www/
.. _OSSS OpenSHMEM: https://github.com/openshmem-org/osss-ucx
.. _Sandia OpenSHMEM: https://github.com/Sandia-OpenSHMEM/SOS
.. _ucx: https://github.com/openucx/ucx
.. _libfabric: https://github.com/ofiwg/libfabric

.. _oshmem_fedora: https://github.com/mpi4py/shmem4py/blob/master/docker/oshmem_fedora/Dockerfile
.. _oshmem_ubuntu: https://github.com/mpi4py/shmem4py/blob/master/docker/oshmem_ubuntu/Dockerfile
.. _oshmpi_fedora: https://github.com/mpi4py/shmem4py/blob/master/docker/oshmpi_fedora/Dockerfile
.. _oshmpi_ubuntu: https://github.com/mpi4py/shmem4py/blob/master/docker/oshmpi_ubuntu/Dockerfile
.. _osss_fedora: https://github.com/mpi4py/shmem4py/blob/master/docker/osss_fedora/Dockerfile
.. _osss_ubuntu: https://github.com/mpi4py/shmem4py/blob/master/docker/osss_ubuntu/Dockerfile
.. _sos_fedora: https://github.com/mpi4py/shmem4py/blob/master/docker/sos_fedora/Dockerfile
.. _sos_ubuntu: https://github.com/mpi4py/shmem4py/blob/master/docker/sos_ubuntu/Dockerfile


Installing shmem4py
-----------------------

Once a working OpenSHMEM implementation is installed, ``shmem4py`` can be
installed using ``pip``::

    git clone https://github.com/mpi4py/shmem4py
    cd shmem4py
    python -m pip install .

You sure then test if everything works as expected::

    make test-1
    make test-2

Next steps
----------

With the installation complete, you can now proceed to run the `examples`.
and try to base your code on them.
