FROM gcc:13.1

RUN apt-get -qq update
RUn apt-get install -qq --no-install-suggests --no-install-recommends autoconf automake autopoint bison bzip2 docbook5-xml docbook-xsl-ns flex gettext libaudit-dev libdb-dev libfl-dev libselinux1-dev libssl-dev libtool libxml2-utils make pkg-config sed w3m xsltproc xz-utils

WORKDIR /linux-pam-baa
RUN mkdir src

COPY Makefile ./
COPY ./src/vendor ./src/vendor
RUN make libpam

RUN mkdir bin
COPY ./src/baa ./src/baa
