CC = g++
CFLAGS = -Wall -O3 -Iinclude -std=c++17

SOURCE_DIR = src/
INCLUDE_DIR = include/
BINARY_DIR = bin/

factor.exe: main.o primeFactorization.o
	$(CC) -o $(BINARY_DIR)factor.exe main.o primeFactorization.o $(CFLAGS)

main.o: $(SOURCE_DIR)main.cpp $(INCLUDE_DIR)primeFactorization.h 
	$(CC) -c -o main.o $(SOURCE_DIR)main.cpp $(CFLAGS)

primeFactorization.o: $(SOURCE_DIR)primeFactorization.cpp $(INCLUDE_DIR)primeFactorization.h
	$(CC) -c -o primeFactorization.o $(SOURCE_DIR)primeFactorization.cpp $(CFLAGS)

test.exe: test.o primeFactorization.o
	$(CC) -o $(BINARY_DIR)test.exe test.o primeFactorization.o $(CFLAGS)

test.o:	test/test.cpp $(INCLUDE_DIR)primeFactorization.h
	$(CC) -c -o test.o test/test.cpp $(CFLAGS)