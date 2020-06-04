#ifndef INCLUDE_SYNTAXCHECKER_H
#define INCLUDE_SYNTAXCHECKER_H

#include <string>

// Syntax checker for Lisp
class SyntaxChecker {
public:
    SyntaxChecker();
    ~SyntaxChecker();
    int checkSyntax(const std::string& code);
};

#endif