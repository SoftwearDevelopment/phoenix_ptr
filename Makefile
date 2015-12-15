.PHONY: run-tests clean

run-tests: tests
	@./tests && echo "ALL TESTS SUCCEEDED"

tests:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) --std=c++14 -DDEBUG=1 -g -O0 ./tests.cc -I./include -Wall -Wextra -Wpedantic -o tests

clean:
	rm tests
