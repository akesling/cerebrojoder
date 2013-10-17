all: naive

naive: bin_
	g++ -Ofast -Wall naive.cpp -o bin/naive

vm: bin_
	g++ -Ofast -Wall vm.cpp -o bin/vm

bin_:
	mkdir -p bin

clean:
	rm bin/*
	rmdir bin
