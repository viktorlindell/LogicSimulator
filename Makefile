CXX = g++
CPPFLAGS = -std=c++17 -Wextra -pedantic -Weffc++

LIBS=-lsfml-graphics -lsfml-window -lsfml-system
SRC=src/
OBJ=objects/

RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

all: logicsimulator

make run: logicsimulator
	./logicsimulator

connector.o: $(SRC)connector.cpp
		@echo $(GREEN) "** Building the connector class **" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)connector.cpp" -o $(OBJ)connector.o

component.o: $(SRC)component.cpp
		@echo $(GREEN) "** Building the component class **" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)component.cpp" -o $(OBJ)component.o

event_manager.o: $(SRC)event_manager.cpp
		@echo $(GREEN) "** Building the event_manager class **" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)event_manager.cpp" -o $(OBJ)event_manager.o

object_manager.o: $(SRC)object_manager.cpp
		@echo $(GREEN) "** Building the object_manager class **" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)object_manager.cpp" -o $(OBJ)object_manager.o

game.o: $(SRC)game.cpp
		@echo $(GREEN) "** Building the game class **" $(NC)
		$(CXX) $(CPPFLAGS) -c "$(SRC)game.cpp" -o $(OBJ)game.o

main.o: $(SRC)main.cpp
		$(CXX) $(CPPFLAGS) -c "$(SRC)main.cpp" -o $(OBJ)main.o

logicsimulator: connector.o component.o event_manager.o object_manager.o game.o main.o
		@echo $(GREEN) "** Building the game **" $(NC)
		$(CXX) $(CPPFLAGS) -o logicsimulator \
			$(OBJ)connector.o $(OBJ)component.o $(OBJ)event_manager.o $(OBJ)object_manager.o $(OBJ)game.o $(OBJ)main.o \
			$(LIBS)

clean:
		@echo $(GREEN) "** Removing object files and executable... **" $(NC)
		rm -f logicsimulator $(OBJ)*.o