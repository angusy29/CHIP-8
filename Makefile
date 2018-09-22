CC=g++
CFLAGS=-std=c++14
SDL_INC=/usr/local/Cellar/sdl2/2.0.8/include
SDL_LIB=/usr/local/Cellar/sdl2/2.0.8/lib
SDL_VERSION=SDL2-2.0.0

Game: game.o mmu.o chip_8.o graphics.o
	$(CC) game.o mmu.o chip_8.o graphics.o -o Game -I $(SDL_INC) -L $(SDL_LIB) -l $(SDL_VERSION)

game.o: game.cpp chip_8.h mmu.h graphics.h
	$(CC) $(CFLAGS) -c game.cpp

mmu.o: mmu.cpp mmu.h
	$(CC) $(CFLAGS) -c mmu.cpp

graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) -c graphics.cpp

chip_8.o: chip_8.cpp chip_8.h mmu.h graphics.h
	$(CC) $(CFLAGS) -c chip_8.cpp

clean:
	rm Game *.o