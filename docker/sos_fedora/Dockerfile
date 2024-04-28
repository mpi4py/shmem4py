# adapted from https://github.com/Sandia-OpenSHMEM/SOS/blob/master/scripts/docker/Dockerfile

FROM fedora:latest
SHELL ["/bin/bash", "-c"]

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel \
                   libevent libevent-devel python3 python3-devel python3-pip mpich && \
    dnf clean all

ENV CC=gcc
ENV CXX=g++

# Build Libfabric
RUN cd $INSTALL_DIR                                                       && \
    git clone --depth 10 https://github.com/ofiwg/libfabric.git libfabric && \
    cd libfabric                                                          && \
    ./autogen.sh                                                          && \
    ./configure --prefix=$INSTALL_DIR/libfabric/install                   && \
    make -j && make install

# Build SOS
RUN cd $INSTALL_DIR                                                                         && \
    git clone --recursive https://github.com/Sandia-OpenSHMEM/SOS.git                       && \
    cd SOS                                                                                  && \
    ./autogen.sh                                                                            && \
    # To build SOS w/ basic Libfabric                                                          \
    ./configure --prefix=$INSTALL_DIR/SOS/install --with-ofi=$INSTALL_DIR/libfabric/install    \
                --without-ucx --without-portals4 --enable-pmi-simple --disable-fortran      && \
    make -j && make install                                                                 && \
    make check TESTS= -j

ENV PATH="/home/shmem/SOS/install/bin:/usr/lib64/mpich/bin:${PATH}"
RUN python3 -m venv /venv
RUN source /venv/bin/activate && pip install numpy cffi setuptools
