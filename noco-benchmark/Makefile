CFLAGS :=
MULT := 1

build: 
	g++ $(CFLAGS) -DMULT=$(MULT) -o3 -o test test.cpp

run: build
	time ./test

run64: CFLAGS := -DX64BIT
run64: build
	time ./test

all: build
