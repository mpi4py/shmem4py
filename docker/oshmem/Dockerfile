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
  python3 python3-pip python-is-python3

RUN mkdir /home/shmem

# Build UCX
RUN cd $INSTALL_DIR                                                                     && \
    wget -c https://github.com/openucx/ucx/releases/download/v1.12.1/ucx-1.12.1.tar.gz  && \
    tar xf ucx-1.12.1.tar.gz                                                            && \
    cd ucx-1.12.1                                                                       && \
    ./contrib/configure-release --prefix=$INSTALL_DIR/ucx-1.12.1/install                && \
    make -j && make install

# Build OpenMPI
RUN cd $INSTALL_DIR                                                                     && \
    wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.4.tar.bz2   && \
    tar xf openmpi-4.1.4.tar.bz2                                                        && \
    cd openmpi-4.1.4                                                                    && \
    ./configure --enable-oshmem --prefix=$INSTALL_DIR/openmpi-4.1.4/install                \
                --with-ucx=/home/shmem/ucx-1.12.1/install                               && \
    make -j && make install

ENV PATH="/home/shmem/openmpi-4.1.4/install/bin:${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python -m pip install numpy cffi
