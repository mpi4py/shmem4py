# adapted from https://github.com/Sandia-OpenSHMEM/SOS/blob/master/scripts/docker/Dockerfile

FROM ubuntu:latest
SHELL ["/bin/bash", "-c"]

ENV INSTALL_DIR=/home/shmem
RUN mkdir -p $INSTALL_DIR
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
  libevent-dev                              \
  mpich                                     \
  python3 python3-pip python-is-python3 python3-venv

# Build Libfabric
RUN cd $INSTALL_DIR                                                           && \
    git clone --depth 10 https://github.com/ofiwg/libfabric.git libfabric-src && \
    cd libfabric-src                                                          && \
    ./autogen.sh                                                              && \
    ./configure --prefix=$INSTALL_DIR/libfabric/                              && \
    make -j $(nproc) && make install && cd .. && rm -rf libfabric-src

# Build SOS
RUN cd $INSTALL_DIR                                                                    && \
    git clone --recursive https://github.com/Sandia-OpenSHMEM/SOS.git SOS-src          && \
    cd SOS-src                                                                         && \
    ./autogen.sh                                                                       && \
    # To build SOS w/ basic Libfabric                                                     \
    ./configure --prefix=$INSTALL_DIR/SOS/ --with-ofi=$INSTALL_DIR/libfabric/             \
                --without-ucx --without-portals4 --enable-pmi-simple --disable-fortran && \
    make -j $(nproc) && make install                                                   && \
    make check TESTS= -j $(nproc) && cd .. && rm -rf SOS-src

ENV PATH="$INSTALL_DIR/SOS/bin:${PATH}"
RUN python3 -m venv /venv
RUN source /venv/bin/activate && pip install numpy cffi setuptools
