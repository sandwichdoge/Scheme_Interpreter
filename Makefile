OBJECTS=main.o \
		StringUtils.o \
		Interpreter.o \
		SyntaxChecker.o \
		Lexer.o \
		AbstractSyntaxTree.o \
		Parser.o \
		Evaluator.o 
		

CFLAGS = -std=c++11 -march=native -g -fsanitize=address -Wall -Wpedantic

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

all: $(OBJECTS)
	$(CXX) $(CFLAGS) $^ -o interpreter.out 

clean:
	rm -f *.o *.out *.a
