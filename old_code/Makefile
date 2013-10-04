CC=~/.llvm/bin/clang
OPTIMIZE=-O3
WARN=-Wall -Wextra -pedantic -Werror
ANALYSIS=-fsanitize=undefined
CFLAGS += -std=c99 -g ${WARN} ${OPTIMIZE} ${ANALYSIS}

MAIN=forestfire.c
TEST=test_forestfire.c

OTHER=round_grid.c tree.c
HEADERS= condition.h configuration.h defines.h forestfire.h greatest.h \
				 random.h round_grid.h round_node.h tree.h

all: forestfire test_forestfire

forestfire: ${MAIN} ${OTHER} ${HEADERS}
	${CC} ${CFLAGS} ${MAIN} ${OTHER} -o forestfire

test_forestfire: ${TEST} ${OTHER} ${HEADERS}
	${CC} ${CFLAGS} ${TEST} ${OTHER} -o test_forestfire

tags:
	etags *.[ch] -o tags

clean:
	rm -f *.o test_forestfire forestfire
