first_bs: first_bs.o main.o
	g++ -o first_bs first_bs.o main.o
first_bs.o: first_bs.cpp
	g++ -c first_bs.cpp
main.o: main.cpp
	g++ -c main.cpp
clean:
	rm first_bs *.o