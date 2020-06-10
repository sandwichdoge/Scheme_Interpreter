#include "SyntaxChecker.h"
#include <vector>
#include <iostream>
#include <thread>
#include <future>

SyntaxChecker::SyntaxChecker(){}
SyntaxChecker::~SyntaxChecker(){}

int SyntaxChecker::checkSyntax(const std::string& code) {
    auto futureParens = std::async(&SyntaxChecker::checkBalancedParens, this, code);
    auto futureQuotes = std::async(&SyntaxChecker::checkBalancedQuotes, this, code);
    int ret = futureParens.get();
    if (ret < 0) return ret;
    ret = futureQuotes.get();
    if (ret < 0) return ret;
    return 0;
}

int SyntaxChecker::checkBalancedParens(const std::string& code) {
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

int SyntaxChecker::checkBalancedQuotes(const std::string& code) {
    int quoteCount = 0;
    for (std::size_t i = 0; i < code.size(); ++i) {
        if (code[i] == '"') {
            quoteCount++;
        }
    }
    if (quoteCount % 2) {
        std::cout << "Error. Unbalanced quotes.\n";
        return -1;
    } else {
        return 0;
    }
}