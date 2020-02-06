
CXX = g++
CXXFLAGS = -Wall -g

QuickHull.exe: main.o ConvexHull.o
	$(CXX) $(CXXFLAGS) -o QuickHull.exe main.o ConvexHull.o

main.o: main.cpp ConvexHull.o
	$(CXX) $(CXXFLAGS) -c QuickHull.exe main.cpp ConvexHull.o

ConvexHull.o: Object.h ThreeDDet.h Point.h Line.h Facet.h Triangle.h ConvexHull.h 

clean:
	rm *.o  *.gch
