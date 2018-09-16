Game: game.o mmu.o chip_8.o graphics.o
	g++ game.o mmu.o chip_8.o graphics.o -o Game -I include -L lib -l SDL2-2.0.0

game.o: game.cpp chip_8.h mmu.h graphics.h
	g++ -std=c++14 -c game.cpp -I include -L lib -l SDL2-2.0.0

mmu.o: mmu.cpp mmu.h
	g++ -std=c++14 -c mmu.cpp

graphics.o: graphics.cpp graphics.h
	g++ -std=c++14 -c graphics.cpp

chip_8.o: chip_8.cpp chip_8.h mmu.h graphics.h
	g++ -std=c++14 -c chip_8.cpp

clean:
	rm Game *.o