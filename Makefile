OPTIONS=-Ofast -Wall -std=c++11 -pedantic

all: bin/naive bin/vm bin/stencil

bin/naive: bin
	g++ $(OPTIONS) naive.cpp -o bin/naive

bin/vm: bin
	g++ $(OPTIONS) vm.cpp -o bin/vm

bin/stencil: bin
	g++ $(OPTIONS) stencil.cpp -o bin/stencil

bin:
	mkdir -p bin

clean:
	rm bin/*
	rmdir bin
