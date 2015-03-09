TARGET       := fnf-detect
VERSION      := "\"$(shell git log -1 --pretty=format:"%h")\""

SRC          := $(wildcard *.c)
OBJ          := $(patsubst %.c,%.o,$(SRC))

CCV_PATH     := liuliu-ccv/lib
CASCADE_PATH := "\"$(shell pwd)/liuliu-ccv/samples/face.sqlite3\""
LIBCCV       := $(CCV_PATH)/libccv.a
CCV_TARBALL  := liuliu-ccv.tar.gz

CFLAGS       += -W -Wall -O3 -ffast-math -std=c99 -I$(CCV_PATH)
CFLAGS       += -DVERSION=$(VERSION) -DCASCADE_PATH=$(CASCADE_PATH)
LDFLAGS      += -L$(CCV_PATH) -lccv `cat $(CCV_PATH)/.deps`

.PHONY: all clean mrproper ccv
all: $(TARGET)
	@echo Done.

$(TARGET): $(LIBCCV) $(OBJ) Makefile
	$(CC) -o $(TARGET) $(OBJ) $(VENDOR) $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm $(OBJ) $(TARGET)

distclean: clean
	-rm -rf $(CCV_PATH)

ccv: $(LIBCCV)
	cd $(CCV_PATH) && ./configure && make

$(CCV_PATH): $(CCV_TARBALL)
	tar xvzf $(CCV_TARBALL)
	ln -s liuliu-ccv-* liuliu-ccv

$(CCV_TARBALL):
	wget -O $(CCV_TARBALL) https://github.com/liuliu/ccv/tarball/stable
