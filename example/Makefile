IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -Wall -ansi -pedantic

ODIR=obj
LDIR =../src

LIBS=$(LDIR)/libstranslate.a

_DEPS = stranslate.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = foo.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	@mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

default: foo

libstranslate.a:
	cd ../src; make

foo: $(OBJ) libstranslate.a
	gcc -o $@ $(OBJ) $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ foo $(INCDIR)/*~ 
