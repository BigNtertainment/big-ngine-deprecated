CC := clang++
SRC := source
BLD := build
OBJ := obj

CFLAGS := -std=c++20 -Wall -Wextra -I./$(SRC)/external/Box2D/include \
		  -I./$(SRC)/external/Box2D/src -I./$(SRC)/external/GLFW/include -I./$(SRC)/external/GLAD \
		  -I./$(SRC)/external/STBI -I./$(SRC)/external/FreeType/include -I./$(SRC)
LDFLAGS := -L./$(SRC)/external/GLFW/lib -lglfw3dll -L./$(SRC)/external/FreeType/lib -lfreetype

SOURCES := $(wildcard $(SRC)/*.cpp)
SOURCES += $(wildcard $(SRC)/global/*/*.cpp)
SOURCES += $(wildcard $(SRC)/types/*/*.cpp)
SOURCES += $(wildcard $(SRC)/behaviours/*/*.cpp)
SOURCES += $(SRC)/external/GLAD/glad.c
SOURCES += $(SRC)/external/STBI/stb.cpp
SOURCES += $(wildcard $(SRC)/external/Box2D/*/*/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))

output: $(OBJECTS)
	$(CC) $^ -o $(BLD)/main.exe $(LDFLAGS)

release: $(OBJECTS)
	$(CC) $(filter-out $(SRC)/main.cpp, $^) -o $(BLD)/bigngine.dll $(LDFLAGS) -shared
	llvm-ar rc 	$(BLD)/bigngine.lib $(OBJECTS) \
				$(SRC)/external/GLFW/lib/glfw3dll.lib \
				$(SRC)/external/FreeType/lib/freetype.lib
	ar ruv 	$(BLD)/bigngine.lib $(OBJECTS) \
			$(SRC)/external/GLFW/lib/glfw3dll.lib \
			$(SRC)/external/FreeType/lib/freetype.lib
	ranlib $(BLD)/bigngine.a

$(OBJ)/%.o: $(SRC)/%.cpp
	@if not exist "$(subst /,\,$(dir $@))" mkdir $(subst /,\,$(dir $@))
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rd /s /q "$(OBJ)/" && mkdir $(OBJ)
	del "$(BLD)\main.exe"

run:
	cd $(BLD) && main.exe

build_and_run:
	make && make run

penis:
	@echo "8===>"

all:
	$(CC) $(SOURCES) $(CFLAGS) $(LDFLAGS) -o $(BLD)/main.exe