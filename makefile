CXX = g++
CXXFLAGS = -g -Wall

Driver: LazyBST.o Driver.cpp
	$(CXX) $(CXXFLAGS) LazyBST.o Driver.cpp -o Driver

LazyBST.o: LazyBST.cpp LazyBST.h
	$(CXX) $(CXXFLAGS) -c LazyBST.cpp
clean:
	rm *.o

run:
	./Driver