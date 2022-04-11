graph: main.o graf.o graf_fun.o io.o arg_pars.o
	cc *.o -o graph

main.o: src/main.c
	cc -c src/main.c

graf.o: src/graf.c src/graf.h
	cc -c src/graf.c

graf_fun.o: src/graf_fun.c src/graf_fun.h
	cc -c src/graf_fun.c

io.o: src/io.c src/io.h
	cc -c src/io.c

arg_pars.o: src/arg_pars.c src/arg_pars.h
	cc -c src/arg_pars.c

clean:
	rm *.o graph

# TARGET   = graph

# IDIR= ./inc
# ODIR= ./obj
# SDIR= ./src
# BDIR= ./bin

# SOURCES  := $(wildcard $(SDIR)/*.c)
# INCLUDES := $(wildcard $(IDIR)/*.h)

# InCFLAGS= -I$(IDIR) -Wall -Wextra -pedantic


# OBJECTS  := $(SOURCES:$(SDIR)/%.c=$(ODIR)/%.o)

# $(BDIR)/$(TARGET): $(OBJECTS)
# 	$(CC) -o $@ $(LFLAGS) $(OBJECTS)

# $(OBJECTS): $(ODIR)/%.o : $(SDIR)/%.c
# 	$(CC) $(CFLAGS) $(InCFLAGS) -c $< -o $@
	