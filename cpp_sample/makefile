all: a.out

a.out: jackknife.cpp jackknife.hpp
	g++ -O3 $< -o $@

.PHONY: clean

clean:
	rm -f a.out
