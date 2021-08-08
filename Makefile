CC := g++
SRC := source
BLD := build
OBJ := obj
FLAGS := --std=c++17 -I.\source\SDL2\include -I.\source\Box2D\include -L.\source\SDL2\lib -L.\source\Box2D\lib -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lBox2D

SOURCES := $(wildcard $(SRC)/*.cpp)
SOURCES += $(wildcard $(SRC)/global/*/*.cpp)
SOURCES += $(wildcard $(SRC)/types/*/*.cpp)
SOURCES += $(wildcard $(SRC)/behaviours/*/*.cpp)
SOURCES += $(wildcard $(SRC)/Box2D/*/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))

output: $(OBJECTS)
	$(CC) $^ $(FLAGS) -o $(BLD)/main.exe

$(OBJ)/%.o: $(SRC)/%.cpp
	@if not exist "$(subst /,\,$(dir $@))" mkdir $(subst /,\,$(dir $@))
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	rd /s /q "$(OBJ)/" && mkdir $(OBJ)
	del "$(BLD)\main.exe"

run:
	cd $(BLD) && main.exe

penis:
	@echo "8===>"