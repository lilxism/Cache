simulation: Block.o Cache.o Set.o Simulation.o
	g++ Block.o Cache.o Set.o Simulation.o -o simulation

Simulation.o: Simulation.cc Cache.o
	g++ Simulation.cc  -c

Block.o: Block.cc Block.h
	g++ Block.cc -c

Set.o: Set.cc Set.h Block.o
	g++ Set.cc -c

Cache.o: Cache.cc Cache.h Set.o Block.o
	g++ Cache.cc -c

clean: 
	rm *.o
	rm simulation
