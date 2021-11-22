IDIR =../include
CC=gcc
CDBG += -w
CFLAGS+=$(CDBG)

ODIR=obj

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o functions.o listas.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

start.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 