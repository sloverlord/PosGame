# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image
CCC=g++

run: main.o 
	$(CCC) $(CFLAGS) main.cpp -o run $(SDL_LIB)

main.o: main.cpp
	$(CCC) $(CFLAGS) -c main.cpp

clean:
	rm -f run *.o
	rm -f *~
