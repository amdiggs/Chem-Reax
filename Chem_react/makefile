REAX: main.o rand_c.o Reax.o
	g++ -o REAX main.o rand_c.o Reax.o

main.o: main.cpp rand_c.hpp Reax.hpp
	g++ -c main.cpp

rand_c.o: rand_c.hpp

Reax.o: Reax.hpp

clean:
	rm *.o
