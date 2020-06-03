CXX = g++
CXXFLAGS = -Wall -Wextra -g -O0

LDFLAGS = # Paramètres : -L
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

HDR = $(wildcard include/*.hpp) # Liste des fichiers d'entêtes
SRC = $(wildcard src/*.cpp) # Liste des fichiers sources
OBJ = $(SRC:.cpp=.o) # Liste des fichiers objets
BIN = jeu # Nom de l'exécutable

SRCT = $(wildcard test/*.cpp)
OBJT = $(SRC:.cpp=.o)  $(OBJ)
BINT = Test #Nom de l'executable des tests

all: build test 

test : $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BINT) $^
	
build: src/main.o $(OBJ)
	$(CXX) $(LDFLAGS) -o $(BIN) $^ $(LDLIBS)

%.o: $(HDR)

.PHONY: clear
clear:
	rm -rf $(OBJ)

.PHONY: vclear
vclear: clear
	rm -rf $(BIN)

rebuild: vclear build
