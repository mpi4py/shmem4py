FROM ubuntu:latest
SHELL ["/bin/bash", "-c"]

ENV INSTALL_DIR=/home/shmem
RUN mkdir -p $INSTALL_DIR
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -y \
  git                                       \
  vim                                       \
  build-essential                           \
  wget                                      \
  automake                                  \
  libtool                                   \
  mpich                                     \
  python3 python3-pip python-is-python3 python3-venv

RUN cd $INSTALL_DIR                                                                && \
    git clone https://github.com/pmodels/oshmpi --recurse-submodules oshmpi-src    && \
    cd oshmpi-src                                                                  && \
    ./autogen.sh                                                                   && \
    ./configure CC=/usr/bin/mpicc CXX=/usr/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi && \
    make -j $(nproc) && make install && cd .. && rm -rf oshmpi-src

ENV PATH=$INSTALL_DIR/oshmpi/bin:"${PATH}"
RUN python3 -m venv /venv
RUN source /venv/bin/activate && pip install numpy cffi
