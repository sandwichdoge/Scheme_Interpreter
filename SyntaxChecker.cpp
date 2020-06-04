#include "SyntaxChecker.h"
#include <vector>
#include <iostream>

SyntaxChecker::SyntaxChecker(){}
SyntaxChecker::~SyntaxChecker(){}

int SyntaxChecker::checkSyntax(const std::string& code) {
    // Check balanced parentheses
    std::vector<std::size_t> parenStack;
    for (std::size_t i = 0; i < code.size(); ++i) {
        if (code[i] == '(') {
            parenStack.push_back(i);
        } else if (code[i] == ')') {
            if (parenStack.size() == 0) {
                std::cout << "Unbalanced parenthesis at position " << i << ".\n";
                return -1;
            } else {
                parenStack.pop_back();
            }
        }
    }
    if (parenStack.size() != 0) {
        std::cout << "Unterminated parenthesis at position ";
        for (std::size_t i = 0; i < parenStack.size(); ++i) {
            std::cout << parenStack.at(i) << ", ";
        }
        std::cout << "\n";
        return -1;
    }
    return 0;
}
