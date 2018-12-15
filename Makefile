
src = $(wildcard src/*.c) \
	  $(wildcard src/pc/*.c)
_OBJ = $(src:.c=.o)

CFLAGS = 
ODIR=obj
BIN=bin
OBJ =  $(patsubst %,$(ODIR)/%,$(_OBJ))
LDFLAGS =

.PHONY: all clean directories

all: directories carma1

carma1: $(OBJ)
	@$(CC) -o bin/$@ $^ $(LDFLAGS)

directories: $(ODIR) $(BIN)

$(BIN):
	@mkdir -p bin

$(ODIR):
	@mkdir -p $(ODIR)/src/pc

$(ODIR)/%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@rm -rf $(ODIR) $(BIN)