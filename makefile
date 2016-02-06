CXX:= g++

CXXFLAGS:= --std=c++11 -Wall -g
SOURCES:= Main.cpp
LIBS:= -L./Utils/lib/ -lUtils
OUT:= Test

$(OUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(OUT) $(LIBS)

