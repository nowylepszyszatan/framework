CXX:= g++
CXXFLAGS:= -std=c++11 -Wall -g
OBJECTS:= LogMgr.o Logger.o GlobalConfig.o DataDictionary.o StringUtils.o ThreadPool.o Program.o
LIB:= lib/libUtils.a

$(LIB): $(OBJECTS)
	rm -rf lib
	mkdir lib
	ar rcs $(LIB) $(OBJECTS)
	rm *.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

