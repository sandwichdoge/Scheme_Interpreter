#include "Parser.h"
#include <iostream>

Parser::Parser() {}
Parser::~Parser() {}

void Parser::setTokens(std::vector<std::string> tokens) {
    _tokens = tokens;
}

int Parser::parse(SyntaxTreeNode *root) {
    if (_tokens.empty()) return 0;
    std::string tok = _tokens[0];
    _tokens.erase(_tokens.begin());

    if (tok == "(") {
        SyntaxTreeNode *node = root->createChildNode();
        std::cout << "[";
        parse(node);
    } else if (tok == ")") {
        std::cout << "]";
        parse(root->parent);
    } else {
        if (root->keywordType != KEYWORD_UNKNOWN) { // Parent has been visited before.
            std::cout << "Error. Stray node. Please wrap all arguments in parentheses.\n";
            std::cout << "At[" << root->token << "].\n";
            exit(1);
        }
        root->token = tok;
        root->identifyKeyword();
        /* TODO no parentheses needed for constants
        if (root->keywordType == KEYWORD_OPERATOR) {
            SyntaxTreeNode *node = createSyntaxTreeNode(root);
            parse(node);
        }*/

        std::cout << tok;
        //std::cout << "[" << root->keywordType << "]";
        std::cout << ",";

        parse(root);
    }
    return 0;
}
