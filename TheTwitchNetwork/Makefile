output: bin/main.o bin/graph.o
	g++ -std=c++20 bin/main.o bin/graph.o -o bin/output
	rm bin/*.o 

bin/main.o: src/main.cpp
	g++ -std=c++20 -c src/main.cpp -o bin/main.o

bin/graph.o: src/graph.cpp src/graph.hpp
	g++ -std=c++20 -c src/graph.cpp -o bin/graph.o

clean:
	rm bin/*.o bin/output

