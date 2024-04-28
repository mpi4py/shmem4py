FROM fedora:latest
SHELL ["/bin/bash", "-c"]

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel \
                   pmix pmix-devel libevent libevent-devel python3 python3-devel python3-pip && \
    dnf clean all

RUN cd $INSTALL_DIR                                                                                                             && \
    wget https://github.com/openucx/ucx/archive/refs/tags/v1.15.0.tar.gz                                                        && \
    tar xf v1.15.0.tar.gz                                                                                                       && \
    cd ucx-1.15.0 && ./autogen.sh                                                                                               && \
    ./configure CFLAGS=-Wno-error --prefix=$INSTALL_DIR/ucx/install --disable-debug --disable-assertions --disable-params-check && \
    make -j && make install

RUN cd $INSTALL_DIR                                                                   && \
    wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.6.tar.bz2 && \
    tar xf openmpi-4.1.6.tar.bz2                                                      && \
    cd openmpi-4.1.6                                                                  && \
    ./configure --disable-dependency-tracking --enable-debug --enable-mem-debug          \
                --disable-sphinx --disable-man-pages --disable-mpi-fortran               \
                --with-ucx=/home/shmem/ucx/install                                       \
                --enable-oshmem --prefix=$INSTALL_DIR/openmpi-4.1.6/install          &&  \
    make -j 2 install

ENV PATH=/home/shmem/openmpi-4.1.6/install/bin:"${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python3 -m venv /venv
RUN source /venv/bin/activate &&  pip install setuptools cffi numpy
