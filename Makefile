CC=clang
OPTIMIZE=-O4
WARN=-Wall -Wextra -pedantic -Werror
CFLAGS += -std=c99 -g ${WARN} ${OPTIMIZE}

OBJECTS=tree.o round_grid.o

test_forestfire: test_forestfire.o ${OBJECTS}

HEADERS=condition.h greatest.h main.h round_grid.h round_node.h tree.h

*.o: Makefile 

tree.o: condition.h

tags:
	etags *.[ch] -o tags

clean:
	rm -f *.o test_forestfire
