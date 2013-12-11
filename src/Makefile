IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -ansi -pedantic

ODIR=obj
LDIR =../lib

LIBS=

_DEPS = stranslate.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = stranslate.o strans_print.o strans_stream.o strans_util.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

default: stranslate

stranslate: $(OBJ)
	ar rcs libstranslate.a $^

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ libstranslate.a $(INCDIR)/*~ 
