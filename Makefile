#Makefile
CXX = g++
LDLIBS = -lcppunit
OBJS = testCTP.o

all : Tests

Tests: $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

testCTP.o: testCTP.cpp

clean:
	rm *.o $(EXEC)
