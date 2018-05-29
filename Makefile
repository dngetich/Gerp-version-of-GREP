CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -O2

DEPS = HashTable.h Gerp.h DirNode.h FSTree.h StringProcessing.h 

%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS) 

gerp: HashTable.o main.o Gerp.o DirNode.o FSTree.o StringProcessing.o
	$(CC) -o gerp HashTable.o main.o Gerp.o DirNode.o FSTree.o StringProcessing.o

test-hash: HashTable.o testHashTable.o
	$(CC) -o test-hash HashTable.o testHashTable.o

clean:
	rm -f *.o core* *~ gerp