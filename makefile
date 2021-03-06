TARGET   = graph

IDIR= ./inc
ODIR= ./obj
SDIR= ./src
BDIR= ./bin

SOURCES  := $(wildcard $(SDIR)/*.c)
INCLUDES := $(wildcard $(IDIR)/*.h)

InCFLAGS= -I$(IDIR) -Wall -Wextra -pedantic -g


OBJECTS  := $(SOURCES:$(SDIR)/%.c=$(ODIR)/%.o)

$(BDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(LFLAGS) $(OBJECTS)

$(OBJECTS): $(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) $(InCFLAGS) -c $< -o $@

test: $(OBJECTS) $(BDIR)/$(TARGET)
	./tests.sh

clean:
	rm $(ODIR)/*.o $(BDIR)/*