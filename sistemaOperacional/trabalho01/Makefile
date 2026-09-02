CXX      = g++
CXXFLAGS = -O3 -Wall -pthread
TARGET   = varredor
SRC      = main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean
clean:
	rm -f $(TARGET)
