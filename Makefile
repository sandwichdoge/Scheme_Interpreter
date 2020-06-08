OBJECTS=main.o \
		Utils/StringUtils.o \
		Utils/AssertError.o \
		Interpreter.o \
		SyntaxChecker.o \
		Lexer.o \
		AbstractSyntaxTree.o \
		Parser.o \
		Evaluator.o 
		
DEBUG = -g -fsanitize=address #-DDEBUG
CFLAGS = -std=c++11 -march=native  -Wall -Wpedantic $(DEBUG)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

all: $(OBJECTS)
	$(CXX) $(CFLAGS) $^ -o interpreter.out 

clean:
	rm -f *.o *.out *.a
	rm -f Utils/*.o Utils/*.a