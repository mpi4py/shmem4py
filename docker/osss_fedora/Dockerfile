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

# Patch Open MPI 4.1.7 for Fedora 44/GCC 16, which rejects its over-braced
# scalar initializers in oshmem/mca/memheap/base/memheap_base_frame.c.
RUN cd $INSTALL_DIR                                                                   && \
    wget -c https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.7.tar.bz2 && \
    tar xf openmpi-4.1.7.tar.bz2                                                      && \
    cd openmpi-4.1.7                                                                  && \
    sed -i -e 's/opal_list_t mca_memheap_base_components_opened = {{0}};/opal_list_t mca_memheap_base_components_opened = {0};/' \
           -e 's/mca_memheap_map_t mca_memheap_base_map = {{{{0}}}};/mca_memheap_map_t mca_memheap_base_map = {0};/' \
           oshmem/mca/memheap/base/memheap_base_frame.c                               && \
    ./configure --disable-dependency-tracking --disable-debug --disable-mem-debug --disable-mem-profile \
                --disable-sphinx --disable-man-pages --disable-mpi-fortran --disable-dlopen             \
                --with-ucx=$INSTALL_DIR/ucx/                                                            \
                --with-pmix=/usr --with-libevent=/usr                                                   \
                --enable-oshmem --prefix=$INSTALL_DIR/openmpi                                        && \
    make -j $(nproc) install && cd .. && rm -rf openmpi-4.1.7 openmpi-4.1.7.tar.bz2

RUN cd $INSTALL_DIR && \
    git clone https://github.com/openshmem-org/osss-ucx osss-ucx-src                                                                         && \
    cd osss-ucx-src/                                                                                                                         && \
    ./autogen.sh                                                                                                                             && \
    ./configure CFLAGS="-std=gnu17" --prefix=$INSTALL_DIR/osss-ucx/ --enable-debug --enable-logging --with-pmix --with-ucx=$INSTALL_DIR/ucx/ && \
    make -j $(nproc) && make install && cd .. && rm -rf osss-ucx-src

ENV PATH=$INSTALL_DIR/osss-ucx/bin:$INSTALL_DIR/openmpi/bin:"${PATH}" \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python3 -m venv /venv
RUN source /venv/bin/activate && pip install setuptools cffi numpy
