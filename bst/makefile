CXXFLAGS += -Wall -O3
TARGETS=bst

all: $(TARGETS)

bst: bst.o bst_test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.o $(TARGETS)
