myc: main.cc
	clang++ -std=c++11 main.cc -o myc

test: myc
	./test.sh
clean:
	rm -rf *.s myc tmp *.out *.dSYM

.PHONY: clean test
