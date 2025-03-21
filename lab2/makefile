CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
GTEST_DIR = /usr/src/gtest
GTEST_LIB = -lgtest -lgtest_main

all: lab2_test

lab2_test: main.o main.test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

main.test.o: main.test.cpp
	$(CXX) $(CXXFLAGS) -c main.test.cpp

clean:
	rm -f *.o lab2_test