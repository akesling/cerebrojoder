all: cj

cj: bin_
	g++ -Ofast -Wall cj.cpp -o bin/cj

bin_:
	mkdir -p bin

clean:
	rm bin/*
	rmdir bin
