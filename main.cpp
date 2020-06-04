#include "StringUtils.h"
#include "Interpreter.h"

#define DEBUG

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please specify a Scheme source file.\n";
        return -1;
    }

    std::string sourceFile = argv[1];

    Interpreter *pInterpreter = new Interpreter;

    if (pInterpreter->loadFile(sourceFile) < 0) {
        std::cout << "Failure: Could not open source file.\n";
        return -2;
    }
    if (pInterpreter->checkSyntax() < 0) {
        std::cout << "Failure: Invalid syntax.\n";
        return -3;
    }

    double final = 0;
    pInterpreter->run(final);
    std::cout << final << "\n";
    delete pInterpreter;
    return 0;
}