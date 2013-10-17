OPTIONS=-Ofast -Wall -std=c++11

all: naive vm

naive: bin_
	g++ $(OPTIONS) naive.cpp -o bin/naive

vm: bin_
	g++ $(OPTIONS) vm.cpp -o bin/vm

bin_:
	mkdir -p bin

clean:
	rm bin/*
	rmdir bin
