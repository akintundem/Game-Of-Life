# Makefile

# Compiler settings
CXX = nvcc
CXXFLAGS = -std=c++11

# OpenCV settings for OpenCV 2
OPENCV = `pkg-config --cflags --libs opencv`

# Target executable name
TARGET = Lab5

# Source file
SRC = Lab5.cu

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(OPENCV)

# Clean
clean:
	rm -f $(TARGET)


# # Compiler settings
# CXX = g++
# CXXFLAGS = -Wall -std=c++11

# # OpenCV settings for OpenCV 2
# OPENCV = `pkg-config --cflags --libs opencv`

# # Target executable name
# TARGET = GameOfLife

# # Source file
# SRC = GameOfLife.cpp

# # Build target
# $(TARGET): $(SRC)
# 	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(OPENCV)

# # Clean
# clean:
# 	rm -f $(TARGET)