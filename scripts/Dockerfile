FROM ubuntu:latest

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y build-essential
RUN apt-get install -y gcc-aarch64-linux-gnu
RUN apt-get install -y gdb-multiarch

VOLUME /root/os-dev
WORKDIR /root/os-dev
