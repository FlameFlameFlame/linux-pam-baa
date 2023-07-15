FROM gcc:13.1

RUN apt -y update

#
# build dependencies
#
RUN apt install -y libcurl4-openssl-dev libpam0g-dev pamtester

WORKDIR /linux-pam-baa
COPY Makefile ./
COPY ./src ./src
RUN mkdir build
RUN make
RUN cp ./build/pam_baa.so /usr/lib/

COPY ./test/pam_baa /etc/pam.d/baa
