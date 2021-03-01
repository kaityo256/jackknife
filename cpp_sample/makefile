all: a.out

CPPFLAGS=-O3 -std=c++11 -Wall -Wextra 

a.out: jackknife.cpp jackknife.hpp
	g++ $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f a.out
