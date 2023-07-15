FROM gcc:13.1

RUN apt-get -qq update

#
# build dependencies
#
RUN apt-get install -qq --no-install-suggests --no-install-recommends libcurl4-openssl-dev libpam0g-dev pamtester

WORKDIR /linux-pam-baa
COPY Makefile ./
COPY ./src ./src
RUN mkdir build
RUN make
RUN cp ./build/pam_baa.so /usr/lib/

COPY ./test/pam_baa /etc/pam.d/baa
