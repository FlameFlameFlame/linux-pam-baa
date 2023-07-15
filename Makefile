DIR_SRC=src
DIR_BIN=build

LIB_NAME=pam_baa
LIB_NAME_SRC=$(LIB_NAME).cpp
LIB_NAME_O=$(LIB_NAME).o
LIB_NAME_SO=$(LIB_NAME).so

LIB_SRC=$(DIR_SRC)/$(LIB_NAME_SRC)
LIB_O=$(DIR_BIN)/$(LIB_NAME_O)
LIB_SO=$(DIR_BIN)/$(LIB_NAME_SO)

CC=gcc
CFLAGS_COMPILE=-fPIC -O3 -c -Wall -Wextra -Wno-unused-parameter
CFLAGS_LINK=-shared -lcurl -lpam

.PHONY: clean

all: $(LIB_SO)

$(LIB_SO): $(LIB_O)
	$(CC) $(CFLAGS_LINK) $(LIB_O) -o $(LIB_SO)

$(LIB_O):
	$(CC) $(CFLAGS_COMPILE) $(LIB_SRC) -o $(LIB_O)

clean:
	rm -f $(LIB_O) $(LIB_SO)
