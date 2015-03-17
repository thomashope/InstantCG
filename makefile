CC=g++
CFlags=-c
SDL=-framework SDL2
BUILD=build/
EXAMP=examples/

instantcg.o: instantcg.cpp
	$(CC) $(CFLAGS) instantcg.cpp $(BUILD)instantcg.o

clean:
	rm -rf *.o *.out
