.PHONY: all test game_of_life clang clean cppcheck rebuild cla cla-i
CC = gcc
FLAGS = -Wall -Wextra -Werror -lm -g -std=c11
FLAGSWNO = -Wall -Wextra -Werror -lm -g -std=c11 -Wno-stringop-truncation 
LINUX=-lsubunit -lrt
LIBS=-lcheck -lm -lpthread
OPEN = firefox


all: make

make: game_of_life

game_of_life:
	@$(CC) *.c -o play.out

cpp: clean
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	@rm -f *.out

rebuild:
	make clean
	make

cla:
	clang-format -n *.c


cla-i:
	clang-format -i *.c
