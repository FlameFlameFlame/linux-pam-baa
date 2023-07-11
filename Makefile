SRC_DIR=src
BIN_DIR=bin
VENDOR_DIR=$(SRC_DIR)/vendor
SRC_BAA_DIR=$(SRC_DIR)/baa

CC=gcc
CFLAGS_LIB_COMPILE=-fPIC -DPIC -O3 -c -W -Wall -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable
CFLAGS_LIB_LINK=-shared -fPIC -DPIC -g -O3
LIBS_INCLUDE_DIRS=-I$(VENDOR_DIR)/linux-pam/libpam/include -I$(VENDOR_DIR)/linux-pam -I$(VENDOR_DIR)/curl/include
LIBPAM_LIB=$(VENDOR_DIR)/linux-pam/libpam/.libs/libpam.so
LIBCURL_LIB=$(VENDOR_DIR)/curl/lib/libcurl.so

.PHONY: clean

all: pam_baa.so

pam_baa.so: $(LIBPAM_LIB) pam_baa.o
	$(CC) $(CFLAGS_LIB_LINK) $(LIBS_INCLUDE_DIRS) $(BIN_DIR)/pam_baa.o $(LIBPAM_LIB) $(LIBCURL_LIB) -o $(BIN_DIR)/pam_baa.so

pam_baa.o:
	$(CC) $(CFLAGS_LIB_COMPILE) $(LIBS_INCLUDE_DIRS) $(SRC_BAA_DIR)/main.cpp -o $(BIN_DIR)/pam_baa.o

$(LIBPAM_LIB):
	cd $(VENDOR_DIR)/linux-pam && ./autogen.sh && ./configure && make

$(LIBCURL_LIB):
	cd $(VENDOR_DIR)/curl && cmake . && make

libpam: $(LIBPAM_LIB)

