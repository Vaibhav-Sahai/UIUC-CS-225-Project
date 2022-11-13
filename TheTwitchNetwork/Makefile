output: bin/main.o bin/graph.o
	g++ bin/main.o bin/graph.o -o bin/output

bin/main.o: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o

bin/graph.o: src/graph.cpp src/graph.hpp
	g++ -c src/graph.cpp -o bin/graph.o

clean:
	rm bin/*.o bin/output

