# Makefile para Juego de Dominó C++

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = domino
SOURCES = main.cpp ficha.cpp jugador.cpp historial.cpp juego_domino.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

debug: CXXFLAGS += -DDEBUG -g
debug: $(TARGET)

clean:
	rm -f $(TARGET) *.o historial_domino.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run debug