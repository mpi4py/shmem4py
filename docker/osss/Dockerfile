FROM fedora:37

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel pmix pmix-devel ucx ucx-devel libevent libevent-devel python3 python3-devel python3-pip prrte && \
    dnf clean all

RUN cd $INSTALL_DIR && \
    git clone https://github.com/openshmem-org/osss-ucx osss-ucx                                              && \
    cd osss-ucx/                                                                                              && \
    ./autogen.sh                                                                                              && \
    ./configure --prefix=$INSTALL_DIR/osss-ucx/install --enable-debug --enable-logging --with-pmix --with-ucx && \
    make -j && make install

ENV PATH=$INSTALL_DIR/osss-ucx/install/bin:"${PATH}" \
    PRTE_ALLOW_RUN_AS_ROOT=1 \
    PRTE_ALLOW_RUN_AS_ROOT_CONFIRM=1 \
    OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN ln -s /usr/bin/python3 /usr/bin/python
RUN python -m pip install setuptools cffi numpy
