CXXFLAGS += -Wall -O3
TARGETS=kdtree

all: $(TARGETS)

kdtree: kdtree.o kdtree_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.o $(TARGETS)
