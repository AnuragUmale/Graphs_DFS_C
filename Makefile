# ==========================================
# Name: Anurag Prashant Umale              =
# Student Id: 1887255                      =
# E-mail: aumale@ucsc.edu                  =
# File: Makefile						   =
# Class: CSE 101 Spring 2023               =
# ==========================================

CC = gcc
CFLAGS = -std=c17 -Wall

all: FindComponents GraphTest

FindComponents: FindComponents.o Graph.o List.o
	$(CC) -o $@ $^

GraphTest: GraphTest.o Graph.o List.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f FindComponents GraphTest *.o

checkTest:
	valgrind --leak-check=full ./GraphTest

checkComponent:
	valgrind --leak-check=full ./FindComponents input.txt output.txt