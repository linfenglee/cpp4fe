hello_world: hello_world.o main.o
	g++ -o hello_world hello_world.o main.o
hello_world.o: hello_world.cpp
	g++ -c hello_world.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm hello_world *.o