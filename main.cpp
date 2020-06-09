#include "Interpreter.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please specify a Scheme source file.\n";
        return -1;
    }

    std::string sourceFile = argv[1];

    Interpreter *pInterpreter = new Interpreter;

    if (pInterpreter->loadFile(sourceFile) < 0) {
        std::cout << "Failure: Could not open source file.\n";
        delete pInterpreter;
        return -2;
    }
    double final = 0;
    try {
        pInterpreter->run(final);
    } catch (...) {
        std::cout << "Error occurred!\n";
    }
    
    std::cout << final << "\n";

    delete pInterpreter;
    return 0;
}