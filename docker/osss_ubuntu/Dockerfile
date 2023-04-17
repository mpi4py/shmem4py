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
  pkg-config                                \
  libpmix-bin libpmix-dev                   \
  python3 python3-pip python-is-python3

RUN cd $INSTALL_DIR                                                                                                  && \
    git clone https://github.com/openucx/ucx                                                                         && \
    cd ucx && ./autogen.sh                                                                                           && \
    ./configure --prefix=$INSTALL_DIR/ucx-master/install --disable-debug --disable-assertions --disable-params-check && \
    make -j && make install

RUN cd $INSTALL_DIR                                                                   && \
    wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.5.tar.bz2 && \
    tar xf openmpi-4.1.5.tar.bz2                                                      && \
    cd openmpi-4.1.5                                                                  && \
    ./configure --enable-oshmem --prefix=$INSTALL_DIR/openmpi-4.1.5/install              \
                --with-ucx=/home/shmem/ucx-master/install                             && \
    make -j && make install

RUN cd $INSTALL_DIR && \
    git clone https://github.com/openshmem-org/osss-ucx osss-ucx                                                                             && \
    cd osss-ucx/                                                                                                                             && \
    ./autogen.sh                                                                                                                             && \
    ./configure --prefix=$INSTALL_DIR/osss-ucx/install --enable-debug --enable-logging --with-pmix --with-ucx=/home/shmem/ucx-master/install && \
    make -j && make install

ENV PATH=$INSTALL_DIR/osss-ucx/install/bin:/home/shmem/openmpi-4.1.5/install/bin:"${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python -m pip install setuptools cffi numpy
