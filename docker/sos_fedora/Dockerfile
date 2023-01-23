# adapted from https://github.com/Sandia-OpenSHMEM/SOS/blob/master/scripts/docker/Dockerfile

FROM fedora:latest

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel \
                   libevent libevent-devel python3 python3-devel python3-pip mpich && \
    dnf clean all

ENV CC=gcc
ENV CXX=g++

# Build Libfabric
RUN cd $INSTALL_DIR                                                                  && \
    git clone -b v1.13.x --depth 10 https://github.com/ofiwg/libfabric.git libfabric && \
    cd libfabric                                                                     && \
    ./autogen.sh                                                                     && \
    ./configure --prefix=$INSTALL_DIR/libfabric/install                              && \
    make -j && make install

# Build SOS
RUN cd $INSTALL_DIR                                                                         && \
    git clone https://github.com/Sandia-OpenSHMEM/SOS.git                                   && \
    cd SOS                                                                                  && \
    ./autogen.sh                                                                            && \
    # To build SOS w/ basic Libfabric                                                          \
    ./configure --prefix=$INSTALL_DIR/SOS/install --with-ofi=$INSTALL_DIR/libfabric/install    \
                --without-ucx --without-portals4 --enable-pmi-simple --disable-fortran      && \
    make -j && make install                                                                 && \
    make check TESTS= -j

ENV PATH="/home/shmem/SOS/install/bin:/usr/lib64/mpich/bin:${PATH}"
RUN ln -s /usr/bin/python3 /usr/bin/python
RUN python -m pip install numpy cffi setuptools
