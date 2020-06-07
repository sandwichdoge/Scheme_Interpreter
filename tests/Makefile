INCLUDE=-Igoogletest/googletest/include

OBJECTS=test_ast.o

all: $(OBJECTS)
	$(CXX) test_main.cpp $(OBJECTS) -pthread -lgtest -o a.out $(INCLUDE) -L.
	./a.out

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ $(INCLUDE)

clean:
	rm -f *.o *.out