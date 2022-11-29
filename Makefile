CXX = g++
CPPFLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++

LIBS=-lsfml-graphics -lsfml-window -lsfml-system
SRC=src/
OBJ=objects/

RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

all: logicsimulator

connector.o: $(SRC)connector.cpp
		@echo $(GREEN) "** Building the connector class" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)connector.cpp" -o $(OBJ)connector.o

component.o: $(SRC)component.cpp
		@echo $(GREEN) "** Building the component class" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)component.cpp" -o $(OBJ)component.o

game.o: $(SRC)game.cpp
		@echo $(GREEN) "** Building the game class" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)game.cpp" -o $(OBJ)game.o

main.o: $(SRC)main.cpp
		$(CXX) $(CPPFLAGS) -c "$(SRC)main.cpp" -o $(OBJ)main.o

logicsimulator: connector.o component.o game.o main.o
		@echo $(GREEN) "** Building the game" $(NC)
		$(CXX) $(CPPFLAGS) -o logicsimulator \
			$(OBJ)connector.o $(OBJ)component.o $(OBJ)game.o $(OBJ)main.o \
			$(LIBS)

clean:
		@echo $(GREEN) "** Removing object files and executable..." $(NC)
		rm -f logicsimulator $(OBJ)*.o