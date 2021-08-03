output: ./build/main.o
	g++ --std=c++17 -I..\source\SDL2\include -L..\source\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -c ..\source\main.cpp