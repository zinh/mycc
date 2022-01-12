myc: main.cc
	clang++ main.cc -o myc

test: myc
	./test.sh
clean:
	rm *.s myc tmp

.PHONY: clean
