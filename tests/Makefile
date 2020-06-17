INCLUDE=-Igoogletest/googletest/include

OBJECTS=test_ast.o \
	test_Lexer.o \
	test_Parser.o \
	test_Evaluator.o \
	test_Evaluator2.o

CFLAGS+=-g -fsanitize=address -march=native -DDEBUG

all: $(OBJECTS)
	$(CXX) $(CFLAGS) test_main.cpp $(OBJECTS) -pthread -lgtest -o a.out $(INCLUDE) -L. -lschemeinterp
	./a.out #--gtest_filter=*Evaluator*

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@ $(INCLUDE)

clean:
	rm -f *.o *.out