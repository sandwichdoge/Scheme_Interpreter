#include "Parser.h"
#include "Utils/Debug.h"
#include <iostream>

Parser::Parser() {}
Parser::~Parser() {}

void Parser::setTokens(std::vector<std::string> tokens) {
    _tokens = tokens;
}

int Parser::parse(SyntaxTreeNode *root) {
    std::string tok;
    if (consume(tok) < 0) return 0; // No more tokens
    db("Current token:[" << tok << "]");

    SyntaxTreeNode *node;
    if (tok == "(") {
        node = root->createChildNode();
        parse(node);
    } else if (tok == ")") {
        parse(root->parent);
    } else if (tok == "\"") {
        if (!_quotesOpen) {
            db("Open quote");
            consume(tok);
            node = root->createChildNode();
            node->token = tok;
            node->keywordType = KEYWORD_STRING;
            db("Token " << tok);
        } else {
            db("Close quote");
        }
        _quotesOpen = !_quotesOpen;
        parse(root);
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

int Parser::consume(std::string& out) {
    if (_tokens.empty()) return -1;
    out = _tokens[0];
    _tokens.erase(_tokens.begin());
    return 0;
}