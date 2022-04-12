# TARGET   = graph

# IDIR= ./inc
# ODIR= ./obj
# SDIR= ./src
# BDIR= ./bin


# $(IDIR)FLAGS= -I$(IDIR) -Wall -Wextra -pedantic



# $(BDIR)/graph: $(ODIR)/main.o $(ODIR)/graf.o $(ODIR)/graf_fun.o $(ODIR)/io.o $(ODIR)/arg_pars.o $(ODIR)/testy.o
# 	cc -Wall -Werror -pedantic -g -lm *.o -o $(BDIR)/graph

# $(ODIR)/main.o: $(SDIR)/main.c
# 	cc -c $(SDIR)/main.c

# $(ODIR)/graf.o: $(SDIR)/graf.c $(IDIR)/graf.h
# 	cc -c $(SDIR)/graf.c

# $(ODIR)/graf_fun.o: $(SDIR)/graf_fun.c $(IDIR)/graf_fun.h
# 	cc -c $(SDIR)/graf_fun.c

# $(ODIR)/io.o: $(SDIR)/io.c $(IDIR)/io.h
# 	cc -c $(SDIR)/io.c

# $(ODIR)/arg_pars.o: $(SDIR)/arg_pars.c $(IDIR)/arg_pars.h
# 	cc -c $(SDIR)/arg_pars.c

# $(ODIR)/testy.o: $(SDIR)/testy.c $(IDIR)/testy.h
# 	cc -c $(SDIR)/testy.c

# test1: graph
# 	./$(BDIR)/graph test --kopiec 10 2.0 5.0

# test2: graph
# 	./$(BDIR)/graph test --kolejka 10

# test3: graph
# 	./$(BDIR)/graph make dane/plik_wyjscowy 5 5 1 10

# test4: graph
# 	./$(BDIR)/graph check dane/dane1

# test5: graph
# 	./$(BDIR)/graph path dane/dane1 1 1 2 2

# clean:
# 	rm *.o graph

TARGET   = graph

IDIR= ./inc
ODIR= ./obj
SDIR= ./src
BDIR= ./bin

SOURCES  := $(wildcard $(SDIR)/*.c)
INCLUDES := $(wildcard $(IDIR)/*.h)

InCFLAGS= -I$(IDIR) -Wall -Wextra -pedantic


OBJECTS  := $(SOURCES:$(SDIR)/%.c=$(ODIR)/%.o)

$(BDIR)/$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(LFLAGS) $(OBJECTS)

$(OBJECTS): $(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) $(InCFLAGS) -c $< -o $@

test: $(OBJECTS) $(BDIR)/$(TARGET)
	./tests.sh

clean:
	rm $(ODIR)/*.o $(BDIR)/*