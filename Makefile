Game: game.o mmu.o chip_8.o
	g++ game.o mmu.o chip_8.o -o Game

game.o: game.cpp chip_8.h
	g++ -std=c++14 -c game.cpp

mmu.o: mmu.cpp mmu.h
	g++ -std=c++14 -c mmu.cpp

chip_8.o: chip_8.cpp chip_8.h mmu.h
	g++ -std=c++14 -c chip_8.cpp

clean:
	rm Game *.o