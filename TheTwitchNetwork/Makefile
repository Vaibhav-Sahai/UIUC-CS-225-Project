output: bin/main.o bin/graph.o
	g++ -std=c++20 bin/main.o bin/graph.o -o bin/output
	rm bin/*.o 

test: bin/test.o bin/graph.o
	g++ -std=c++20 bin/test.o bin/graph.o -o bin/test
	rm bin/*.o

bin/main.o: src/main.cpp
	g++ -std=c++20 -c src/main.cpp -o bin/main.o

bin/graph.o: src/graph.cpp src/graph.hpp
	g++ -std=c++20 -c src/graph.cpp -o bin/graph.o

bin/test.o: bin/catch.o tests/tests.cpp
	g++ -std=c++20 -c tests/tests.cpp -o bin/test.o

bin/catch.o: tests/catch.hpp
	g++ -std=c++20 -c tests/catch.hpp -o bin/catch.o

clean:
	rm bin/*.o bin/output bin/test



