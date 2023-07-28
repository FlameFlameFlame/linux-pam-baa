DIR_SRC=src
DIR_BIN=build

LIB_NAME=pam_baa
LIB_NAME_SRC=$(LIB_NAME).cpp
LIB_NAME_O=$(LIB_NAME).o
LIB_NAME_A=$(LIB_NAME).a
LIB_NAME_SO=$(LIB_NAME).so

LIB_SRC=$(DIR_SRC)/$(LIB_NAME_SRC)
LIB_O=$(DIR_BIN)/$(LIB_NAME_O)
LIB_A=$(DIR_BIN)/$(LIB_NAME_A)
LIB_SO=$(DIR_BIN)/$(LIB_NAME_SO)

CC=gcc
CFLAGS_COMPILE=-O3 -fPIC -c -Wall -Wextra -Wno-unused-parameter

AR=ar
AFLAGS_RCS=rcs

.PHONY: clean

all: $(LIB_SO)

$(LIB_SO): $(LIB_A)
	$(CC) -shared -o $(LIB_SO) -lcurl -lpam -Wl,--whole-archive $(LIB_A) -Wl,--no-whole-archive

$(LIB_A): $(LIB_O)
	$(AR) $(AFLAGS_RCS) $(LIB_A) $(LIB_O)

$(LIB_O):
	$(CC) $(CFLAGS_COMPILE) $(LIB_SRC) -o $(LIB_O)

clean:
	rm -f $(LIB_O) $(LIB_A) $(LIB_SO)
