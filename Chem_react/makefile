ChemReax: main.o rand_c.o Reax.o ValidIO.o
	clang++ -o ChemReax main.o rand_c.o Reax.o ValidIO.o

main.o: main.cpp rand_c.hpp Reax.hpp
	clang++ -c main.cpp

rand_c.o: rand_c.hpp

Reax.o: Reax.hpp ValidIO.hpp

ValidIO.o: ValidIO.hpp

clean:
	rm -rf *.o
