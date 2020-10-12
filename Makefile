CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wpedantic -pthread

.PHONY: check check-leaks check-threads clean

example: client.o threadpool.o
	$(CXX) $(CXXFLAGS) -o $@ $^

check: check-leaks check-threads

check-leaks: example
	valgrind --quiet ./$<

check-threads: example
	valgrind --tool=helgrind --quiet ./$<

clean:
	rm -f *.o example
