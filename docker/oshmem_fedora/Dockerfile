FROM fedora:latest
SHELL ["/bin/bash", "-c"]

ENV INSTALL_DIR=/home/shmem
RUN mkdir -p $INSTALL_DIR

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel \
                   pmix pmix-devel libevent libevent-devel python3 python3-devel python3-pip gawk && \
    dnf clean all

RUN cd $INSTALL_DIR                                                                                                                   && \
    wget https://github.com/openucx/ucx/archive/refs/tags/v1.19.0.tar.gz                                                              && \
    tar xf v1.19.0.tar.gz                                                                                                             && \
    cd ucx-1.19.0 && ./autogen.sh                                                                                                     && \
    ./configure CFLAGS="-Wno-error -std=gnu17" --prefix=$INSTALL_DIR/ucx/ --disable-debug --disable-assertions --disable-params-check && \
    make -j $(nproc) && make install && cd .. && rm -rf ucx-1.19.0 v1.19.0.tar.gz

RUN cd $INSTALL_DIR                                                                   && \
    wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.7.tar.bz2 && \
    tar xf openmpi-4.1.7.tar.bz2                                                      && \
    cd openmpi-4.1.7                                                                  && \
    ./configure --disable-dependency-tracking --disable-debug --disable-mem-debug --disable-mem-profile \
                --disable-sphinx --disable-man-pages --disable-mpi-fortran --disable-dlopen             \
                --with-ucx=$INSTALL_DIR/ucx/                                                            \
                --with-pmix=/usr --with-libevent=/usr                                                   \
                --enable-oshmem --prefix=$INSTALL_DIR/openmpi                                        && \
    make -j $(nproc) install && cd .. && rm -rf openmpi-4.1.7 openmpi-4.1.7.tar.bz2

ENV PATH=$INSTALL_DIR/openmpi/bin:"${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python3 -m venv /venv
RUN source /venv/bin/activate &&  pip install setuptools cffi numpy
