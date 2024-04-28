FROM ubuntu:latest
SHELL ["/bin/bash", "-c"]

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
  pkg-config                                \
  libpmix-bin libpmix-dev                   \
  python3 python3-pip python-is-python3 python3-venv

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

RUN cd $INSTALL_DIR && \
    git clone https://github.com/openshmem-org/osss-ucx osss-ucx                                                                      && \
    cd osss-ucx/                                                                                                                      && \
    ./autogen.sh                                                                                                                      && \
    ./configure --prefix=$INSTALL_DIR/osss-ucx/install --enable-debug --enable-logging --with-pmix --with-ucx=/home/shmem/ucx/install && \
    make -j && make install

ENV PATH=$INSTALL_DIR/osss-ucx/install/bin:/home/shmem/openmpi-4.1.6/install/bin:"${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python3 -m venv /venv
RUN source /venv/bin/activate && pip install setuptools cffi numpy
