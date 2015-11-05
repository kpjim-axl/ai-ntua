# File: Makefile
# Encoding: utf-8
# Purpose: AI class - A* search algorithm implementation
# Author: Konstantinos Papadimitriou <k.s.papadimitriou@gmail.com>

.PHONY: clean dist-clean

CC=gcc
CFLAGS=-Wall -g -lm
OBJECT=object_files

default: main

main: $(OBJECT)/move.o $(OBJECT)/main.o $(OBJECT)/heuristics.o $(OBJECT)/heap.o $(OBJECT)/route.o
	$(CC) $(CFLAGS) -o main $^

$(OBJECT)/%.o: %.c %.h $(OBJECT)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT):
	mkdir $(OBJECT)

testcase_generator: testcase_generator.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) -r *~ $(OBJECT)

dist-clean: clean
	$(RM) main testcase_generator
