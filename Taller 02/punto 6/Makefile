CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
TARGET = domino
OBJECTS = ficha.o jugador.o juego_domino.o main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

ficha.o: ficha.cpp ficha.h
	$(CXX) $(CXXFLAGS) -c ficha.cpp

jugador.o: jugador.cpp jugador.h ficha.h
	$(CXX) $(CXXFLAGS) -c jugador.cpp

juego_domino.o: juego_domino.cpp juego_domino.h jugador.h ficha.h
	$(CXX) $(CXXFLAGS) -c juego_domino.cpp

main.o: main.cpp juego_domino.h jugador.h ficha.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
