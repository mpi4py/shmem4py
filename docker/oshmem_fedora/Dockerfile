FROM fedora:latest

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel pmix pmix-devel libevent libevent-devel python3 python3-devel python3-pip valgrind valgrind-devel && \
    dnf clean all

RUN cd $INSTALL_DIR && \
    git clone https://github.com/openucx/ucx && \
    cd ucx && ./autogen.sh && \
    ./contrib/configure-devel --prefix=$INSTALL_DIR/ucx-master/install                && \
    make -j && make install

RUN cd $INSTALL_DIR                                                                     && \
    wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.4.tar.bz2   && \
    tar xf openmpi-4.1.4.tar.bz2                                                        && \
    cd openmpi-4.1.4                                                                    && \
    ./configure --enable-oshmem --prefix=$INSTALL_DIR/openmpi-4.1.4/install                \
                --with-ucx=/home/shmem/ucx-master/install                               && \
    make -j && make install

ENV PATH=/home/shmem/openmpi-4.1.4/install/bin:"${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN ln -s /usr/bin/python3 /usr/bin/python
RUN python -m pip install setuptools cffi numpy
