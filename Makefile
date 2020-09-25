FLAGS=-O3 -Wall -Wextra
CC=g++
GIT_HOOKS := .git/hooks/applied

all: test1.out test1_ext1.out test1_ext2.out test2.out test3.out test4.out \
	test5.out test6.out
clean:
	rm -f test1.out test1_ext1.out test1_ext2.out test2.out test3.out \
	test4.out test5.out test6.out

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

test1.out: test1.cc
	$(CC) $(FLAGS) test1.cc -o test1.out

test1_ext1.out: test1_ext1.cc
	$(CC) $(FLAGS) test1_ext1.cc -o test1_ext1.out

test1_ext2.out: test1_ext2.cc
	$(CC) $(FLAGS) test1_ext2.cc -o test1_ext2.out

test2.out: test2.cc
	$(CC) $(FLAGS) test2.cc -o test2.out

test3.out: test3.cc
	$(CC) -O0 -Wall -Wextra -Ijemalloc jemalloc/div.c test3.cc -o test3.out

test4.out: test4.cc
	$(CC) $(FLAGS) test4.cc -o test4.out

test5.out: test5.cc
	$(CC) $(FLAGS) test5.cc -o test5.out

test6.out: test6.cc
	$(CC) $(FLAGS) test6.cc -o test6.out
