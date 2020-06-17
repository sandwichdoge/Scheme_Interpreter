OBJECTS=main.o \
		Utils/StringUtils.o \
		Utils/AssertError.o \
		Interpreter.o \
		SyntaxChecker.o \
		Lexer.o \
		AbstractSyntaxTree.o \
		Parser.o \
		Evaluator.o 

CFLAGS += -std=c++11 -march=native -Wall -Wpedantic

all: $(OBJECTS)
	$(CXX) $(CFLAGS) $^ -o interpreter.out -pthread

debug: CFLAGS+=-g -fsanitize=address -DDEBUG
debug: LDFLAGS+=-g
debug: all
debug:
	$(AR) crf tests/libschemeinterp.a $(OBJECTS)

test:
	cd tests && make

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.out *.a
	rm -f Utils/*.o Utils/*.a
