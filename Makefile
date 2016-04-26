CC ?= gcc
CFLAGS_common ?= -Wall -O2 -Os -Wall -Wextra -pedantic -Wstrict-overflow -fno-strict-aliasing
CFLAGS_opt = -flto -march=native
CFLAGS_test = -pg -Werror -Wshadow
EXEC = generateCSV

generateCSV: generateCSV.c
	$(CC) $(CFLAGS_common) $(CFLAGS_test) $^ -o $@

.PHONY: clean convert

convert:
	./generateCSV $(shell ls ./html/utf8/*.htm)
clean:
	rm $(EXEC)
