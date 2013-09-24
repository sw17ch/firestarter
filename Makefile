CC=clang
OPTIMIZE=-O4
WARN=-Wall -Wextra -pedantic -Werror
CFLAGS += -std=c99 -g ${WARN} ${OPTIMIZE}

test_tree: test_tree.o tree.o

HEADERS=condition.h greatest.h main.h round_grid.h round_node.h tree.h

*.o: Makefile 

tags:
	etags *.[ch] -o tags

clean:
	rm -f *.o test_tree
