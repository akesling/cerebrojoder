OPTIONS=-Ofast -Wall -std=c++11 -pedantic

all: bin bin/naive bin/vm bin/stencil

bin/naive: naive.cpp
	g++ $(OPTIONS) naive.cpp -o $@

bin/vm: vm.cpp
	g++ $(OPTIONS) vm.cpp -o $@

bin/stencil: stencil.cpp
	g++ $(OPTIONS) stencil.cpp -o $@

bin:
	mkdir -p bin

clean:
	rm bin/*
	rmdir bin
