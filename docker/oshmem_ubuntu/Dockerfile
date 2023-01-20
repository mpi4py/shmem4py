FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -y \
  git                                       \
  vim                                       \
  build-essential                           \
  automake                                  \
  libtool                                   \
  openmpi-bin libopenmpi-dev                \
  python3 python3-pip python-is-python3

ENV OMPI_ALLOW_RUN_AS_ROOT=1 \
    OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

RUN python -m pip install numpy cffi
