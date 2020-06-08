#include "Parser.h"
#include "Utils/Debug.h"
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
    db("Current token:[" << tok << "]");

    SyntaxTreeNode *node;
    if (tok == "(") {
        node = root->createChildNode();
        //std::cout << "[";
        parse(node);
    } else if (tok == ")") {
        //std::cout << "]";
        parse(root->parent);
    } else {
        switch (root->keywordType) { 
            case KEYWORD_UNKNOWN:
                root->token = tok;
                root->identifyKeyword();
                parse(root);
                break;
            default: // Parent has been visited before.
                node = root->createChildNode();
                node->token = tok;
                node->identifyKeyword();
                parse(root);
                break;
        }
    }
    return 0;
}
