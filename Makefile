CXX = g++
CXXFLAGS = -Wall -g

tictactoe: tictactoe.o
	$(CXX) $(CXXFLAGS) -o tictactoe tictactoe-v1.0.cpp 

tictactoe.o: tictactoe-v1.0.cpp header.hpp
	$(CXX) $(CXXFLAGS) -c tictactoe-v1.0.cpp

clean: rm *o main