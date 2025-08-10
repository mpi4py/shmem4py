FROM fedora:latest
SHELL ["/bin/bash", "-c"]

ENV INSTALL_DIR=/home/shmem
RUN mkdir -p $INSTALL_DIR

RUN dnf update -y && \
    dnf install -y git vim wget pkg-config make automake gcc gcc-c++ kernel-devel libtool lbzip2 hwloc hwloc-devel \
                   libevent libevent-devel python3 python3-devel python3-pip mpich mpich-devel gawk && \
    dnf clean all

RUN cd $INSTALL_DIR                                                                                        && \
    git clone https://github.com/pmodels/oshmpi --recurse-submodules oshmpi-src                            && \
    cd oshmpi-src                                                                                          && \
    ./autogen.sh                                                                                           && \
    ./configure CC=/usr/lib64/mpich/bin/mpicc CXX=/usr/lib64/mpich/bin/mpicxx --prefix=$INSTALL_DIR/oshmpi && \
    make -j $(nproc) && make install && cd .. && rm -rf oshmpi-src

ENV PATH="$INSTALL_DIR/oshmpi/bin/:/usr/lib64/mpich/bin/:${PATH}"
RUN python3 -m venv /venv
RUN source /venv/bin/activate && pip install numpy cffi
ENV PSM3_DEVICES="self,shm"
