# adapted from https://github.com/Sandia-OpenSHMEM/SOS/blob/master/scripts/docker/Dockerfile

FROM ubuntu:22.04

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem
ENV DEBIAN_FRONTEND=noninteractive
ENV CC=gcc
ENV CXX=g++

RUN apt-get update -y && apt-get install -y \
  git                                       \
  vim                                       \
  build-essential                           \
  wget                                      \
  automake                                  \
  libtool                                   \
  flex                                      \
  libhwloc-dev                              \
  mpich                                     \
  python3 python3-pip python-is-python3

# Build Libevent
RUN cd $INSTALL_DIR                                                                                                     && \
    wget -c https://github.com/libevent/libevent/releases/download/release-2.1.10-stable/libevent-2.1.10-stable.tar.gz  && \
    tar -xzvf libevent-2.1.10-stable.tar.gz                                                                             && \
    cd libevent-2.1.10-stable                                                                                           && \
    ./autogen.sh                                                                                                        && \
    ./configure --prefix=$INSTALL_DIR/libevent-2.1.10-stable/install                                                    && \
    make clean all install

# Build Libfabric
RUN cd $INSTALL_DIR                                                                 && \
    git clone -b v1.7.x --depth 10 https://github.com/ofiwg/libfabric.git libfabric && \
    cd libfabric                                                                    && \
    ./autogen.sh                                                                    && \
    ./configure --prefix=$INSTALL_DIR/libfabric/install                             && \
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

ENV PATH="/home/shmem/SOS/install/bin:${PATH}"

WORKDIR $INSTALL_DIR/SOS/examples

RUN python -m pip install numpy cffi setuptools
