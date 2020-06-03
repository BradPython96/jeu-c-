CXX = g++
CXXFLAGS = -Wall -Wextra -g -O0 -Iinclude

LDFLAGS = # Paramètres : -L
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

HDR = $(wildcard include/*.hpp) # Liste des fichiers d'entêtes
SRC = $(wildcard src/*.cpp) # Liste des fichiers sources
OBJ = $(SRC:.cpp=.o) # Liste des fichiers objets
BIN = jeu # Nom de l'exécutable

SRCT = $(wildcard test/*.cpp)
OBJT = $(SRCT:.cpp=.o)  $(OBJ)
BINT = Test #Nom de l'executable des tests

all: build Test 

Test : test.o $(OBJT)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(BINT) $^ $(LDLIBS)
	
build: main.o $(OBJ)
	$(CXX) $(LDFLAGS) -o $(BIN) $^ $(LDLIBS)

%.o: $(HDR)

.PHONY: clear
clear:
	rm -rf $(OBJ) main.o $(OBJT)

.PHONY: vclear
vclear: clear
	rm -rf $(BIN)

rebuild: vclear all
