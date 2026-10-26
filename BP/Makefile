CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
SRC := src/agenda.cpp src/main.cpp
BIN := agenda

.PHONY: all run docs clean

all: $(BIN)

$(BIN): $(SRC) include/agenda.hpp
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN)

## Gera a documentação de API em docs/html a partir dos comentários Doxygen do código.
## Requer o doxygen instalado (ex.: sudo dnf install doxygen graphviz).
docs:
	doxygen Doxyfile

clean:
	rm -f $(BIN)
	rm -rf docs/html docs/latex
