
src = $(wildcard src/*.c) \
	  $(wildcard src/pc/*.c) \
	  $(wildcard src/test/*.c)
_OBJ = $(src:.c=.o)

CFLAGS = 
ODIR=obj
BIN=bin
OBJ =  $(patsubst %,$(ODIR)/%,$(_OBJ))
LDFLAGS =

.PHONY: all clean directories test

all: directories carma1

carma1: $(OBJ)
	@$(CC) -o bin/$@ $^ $(LDFLAGS)

test: carma1
	bin/carma1 -test

directories: $(ODIR) $(BIN)

$(BIN):
	@mkdir -p bin

$(ODIR):
	@mkdir -p $(ODIR)/src/pc $(ODIR)/src/test

$(ODIR)/%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf $(ODIR) $(BIN)