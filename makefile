# variables
CC=g++
CFlags=-c
SDL=-framework SDL2
BUILD=build/
INST=$(BUILD)instantcg.o -iquote .
EXAMP=examples/

# an example of instantCG to make sure things are building correctly
all: instantcg helloWorld

# compile InstantCG as an .o file
instantcg:
	$(CC) -c instantcg.cpp -o $(BUILD)instantcg.o

# compile an example and link it with instant cg
helloWorld: $(EXAMP)helloWorld.cpp
	$(CC) $(EXAMP)helloWorld.cpp $(INST) $(SDL) -o helloWorld.out

# delete temporary files
clean:
	rm -rf *.o *.out
