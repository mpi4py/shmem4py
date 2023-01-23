FROM fedora:latest

ENV INSTALL_DIR=/home/shmem
RUN mkdir /home/shmem

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel \
                   pmix pmix-devel libevent libevent-devel python3 python3-devel python3-pip && \
    dnf clean all

RUN cd $INSTALL_DIR                                                                        && \
    git clone https://github.com/dalcinl/oshmpi -b fix-api-1.5 --recurse-submodules        && \
    cd oshmpi                                                                              && \
    ./autogen.sh                                                                           && \
    ./configure CC=/usr/bin/mpicc CXX=/usr/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi/install && \
    make -j && make install

ENV PATH="/home/shmem/oshmpi/install/bin/:${PATH}"
RUN ln -s /usr/bin/python3 /usr/bin/python
RUN python -m pip install numpy cffi