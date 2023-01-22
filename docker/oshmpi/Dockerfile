FROM ubuntu:22.04

ENV INSTALL_DIR=/home/shmem
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -y \
  git                                       \
  vim                                       \
  build-essential                           \
  wget                                      \
  automake                                  \
  libtool                                   \
  mpich                                     \
  python3 python3-pip python-is-python3

RUN mkdir /home/shmem

RUN cd $INSTALL_DIR                                                                        && \
    git clone https://github.com/dalcinl/oshmpi -b fix-api-1.5 --recurse-submodules        && \
    cd oshmpi                                                                              && \
    ./autogen.sh                                                                           && \
    ./configure CC=/usr/bin/mpicc CXX=/usr/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi/install && \
    make -j && make install

ENV PATH="/home/shmem/oshmpi/install/bin/:${PATH}"
RUN python -m pip install numpy cffi
