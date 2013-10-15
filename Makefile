all: cj

cj: bin_
	g++ cj.cpp -o bin/cj

bin_:
	mkdir -p bin

clean:
	rm bin/*
	rmdir bin
