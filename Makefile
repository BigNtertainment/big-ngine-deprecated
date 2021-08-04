output:
	g++ --std=c++17 .\source\main.cpp .\source\input.cpp .\source\game.cpp -I.\source\SDL2\include -L.\source\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o .\build\main.exe

run:
	cd .\build\ && main.exe
