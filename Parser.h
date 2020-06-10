#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H
#include "AbstractSyntaxTree.h"
#include <vector>
#include <string>

class Parser {
public:
    Parser();
    ~Parser();
    int parse(SyntaxTreeNode *root);
    void setTokens(std::vector<std::string> tokens);
private:
    // Consume next token, put its value in out.
    int consume(std::string& out);
    std::vector<std::string> _tokens;
    bool _quotesOpen = false;
};

#endif