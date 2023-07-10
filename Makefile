SRC_DIR=src
BIN_DIR=bin

CC=gcc
CFLAGS_LIB_COMPILE=-fPIC -DPIC -O3 -c -W -Wall -Wno-unused-parameter
CFLAGS_LIB_LINK=-shared -fPIC -DPIC -g -O3
LIBPAM_INCLUDE_DIRS=-I./src/vendor/linux-pam/libpam/include -I./src/vendor/linux-pam
LIBPAM_LIB=./src/vendor/linux-pam/libpam/.libs/libpam.so

.PHONY: clean

all: pam_baa.so

pam_baa.so: $(LIBPAM_LIB) pam_baa.o
	$(CC) $(CFLAGS_LIB_LINK) $(LIBPAM_INCLUDE_DIRS) ./bin/pam_baa.o $(LIBPAM_LIB) -o ./bin/pam_baa.so

pam_baa.o:
	$(CC) $(CFLAGS_LIB_COMPILE) $(LIBPAM_INCLUDE_DIRS) src/baa/main.cpp -o ./bin/pam_baa.o

$(LIBPAM_LIB):
	cd ./src/vendor/linux-pam && ./autogen.sh && ./configure && make

libpam: $(LIBPAM_LIB)

