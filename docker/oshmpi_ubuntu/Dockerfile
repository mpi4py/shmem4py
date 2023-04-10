FROM ubuntu:latest

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem
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

RUN cd $INSTALL_DIR                                                                        && \
    git clone https://github.com/pmodels/oshmpi --recurse-submodules                       && \
    cd oshmpi                                                                              && \
    ./autogen.sh                                                                           && \
    ./configure CC=/usr/bin/mpicc CXX=/usr/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi/install && \
    make -j && make install

ENV PATH="/home/shmem/oshmpi/install/bin/:${PATH}"
RUN python -m pip install numpy cffi
