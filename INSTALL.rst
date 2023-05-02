==============================
Installation
==============================

Overview
--------

`shmem4py` provides Python bindings for `OpenSHMEM <http://openshmem.org/>`_, hence
a working OpenSHMEM installation is a prerequisite.
`Cray OpenSHMEMX <https://cray-openshmemx.readthedocs.io/>`_,
`Open Source Software Solutions (OSSS) OpenSHMEM <https://github.com/openshmem-org/osss-ucx>`_,
`Open MPI OpenSHMEM <https://www.open-mpi.org/doc/v3.1/man3/OpenSHMEM.3.php>`_,
`OSHMPI <https://pmodels.github.io/oshmpi-www/>`_, and
`Sandia OpenSHMEM <https://github.com/Sandia-OpenSHMEM/SOS>`_
are supported at the moment. Generally speaking, ``shmem4py`` will be installed using
the OpenSHMEM implementation's ``oshcc`` wrapper found in the ``$PATH``.

For detailed installation instructions, please refer to the `Installation <https://shmem4py.readthedocs.io/en/latest/installation.html>`_
page in the documentation.

Below, we provide an example of how to install `shmem4py` with OHMPI on Ubuntu and Fedora.

Containers
----------

We encourage users to use Docker/Podman containers or follow the steps executed in the
`Dockerfiles <https://github.com/mpi4py/shmem4py/tree/master/docker>`_. Containers
based on those files are meant to show minimal configurations for building and running
`shmem4py` with different OpenSHMEM implementations. Those images are used in GitHub
Actions CI/CD and we consider them tested configurations.
Currently, we test with OSSS OpenSHMEM, Open MPI OpenSHMEM, OSHMPI and Sandia OpenSHMEM
on the latest releases of Fedora and Ubuntu.


shmem4py with OSHMPI (Ubuntu)
-----------------------------

Install necessary prerequisites including MPICH using the package manager::

    sudo apt-get update
    sudo apt-get install git build-essential wget automake libtool mpich python3 python3-pip python-is-python3


Define ``$INSTALL_DIR`` to be used in the following steps, such as::

    export INSTALL_DIR="/home/$(whoami)/shmem"


Install OSHMPI::

    mkdir -p $INSTALL_DIR
    cd $INSTALL_DIR
    git clone https://github.com/pmodels/oshmpi --recurse-submodules
    cd oshmpi
    ./autogen.sh
    ./configure CC=/usr/bin/mpicc CXX=/usr/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi/install
    make -j
    make install
    cd ..


Update ``$PATH``. It might also be beneficial to add this line in one's ``.bashrc`` file::

    export PATH="${INSTALL_DIR}/oshmpi/install/bin/:${PATH}"


Install ``numpy`` and ``cffi`` modules::

    python -m pip install numpy cffi


With all the prerequisites in place, we can install ``shmem4py``::

    git clone https://github.com/mpi4py/shmem4py
    cd shmem4py
    python -m pip install .


Test if everything works as expected::

    make test-1
    make test-2


shmem4py with OSHMPI (Fedora)
-----------------------------

Install necessary prerequisites including MPICH using the package manager::

    sudo dnf update
    sudo dnf install git pkg-config make automake gcc gcc-c++ kernel-devel libtool \
        lbzip2 hwloc hwloc-devel libevent libevent-devel \
        python3 python3-devel python3-pip mpich mpich-devel

Define ``$INSTALL_DIR`` to be used in the following steps, such as::

    export INSTALL_DIR="/home/$(whoami)/shmem"


Install OSHMPI::

    mkdir -p $INSTALL_DIR
    cd $INSTALL_DIR
    git clone https://github.com/pmodels/oshmpi --recurse-submodules
    cd oshmpi
    ./autogen.sh
    ./configure CC=/usr/lib64/mpich/bin/mpicc CXX=/usr/lib64/mpich/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi/install
    make -j
    make install
    cd ..


Update ``$PATH``. It might also be beneficial to add the below line in one's ``.bashrc`` file.
Alternatively, Fedora's ``mpi/mpich-x86_64`` module can be used instead of adding MPICH to the ``$PATH``. Run::

    export PATH="${INSTALL_DIR}/oshmpi/install/bin/:/usr/lib64/mpich/bin/:${PATH}"

If ``python`` does not exist or points to a Python 2 interpreter, it might be
necessary to either use ``python3`` instead of ``python`` in the following commands or create a symbolic link::

    ln -s /usr/bin/python3 /usr/bin/python

Install ``numpy`` and ``cffi`` modules::

    python -m pip install numpy cffi


With all the prerequisites in place, we can install ``shmem4py``::

    git clone https://github.com/mpi4py/shmem4py
    cd shmem4py
    python -m pip install .


Test if everything works as expected::

    make test-1
    make test-2

Next steps
----------

With the installation complete, you can now proceed to run the `Examples <https://shmem4py.readthedocs.io/en/latest/examples.html>`_
and try to base your code on them.