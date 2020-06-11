#include "Parser.h"
#include "Utils/Debug.h"
#include "Utils/StringUtils.h"

Parser::Parser() {}
Parser::~Parser() {}

void Parser::setTokens(std::vector<std::string> tokens) {
    _tokens = tokens;
}

int Parser::parse(SyntaxTreeNode *root) {
    std::string tok;
    if (consume(tok) < 0) return 0; // No more tokens

    SyntaxTreeNode *node;
    if (tok == "(") {
        node = root->createChildNode();
        parse(node);
    } else if (tok == ")") {
        parse(root->parent);
    } else if (tok == "\"") {
        if (!_quotesOpen) {
            consume(tok);
            node = root->createChildNode();
            node->token = tok;
            node->keywordType = KEYWORD_STRING;
        }
        _quotesOpen = !_quotesOpen;
        parse(root);
    } else {
        switch (root->keywordType) { 
            case KEYWORD_UNKNOWN:
                root->token = tok;
                root->keywordType = identifyKeyword(tok);
                parse(root);
                break;
            default: // Parent has been visited before.
                node = root->createChildNode();
                node->token = tok;
                node->keywordType = identifyKeyword(tok);
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
    db("Consume token:[" << out << "]");
    return 0;
}

enum KEYWORD_TYPE Parser::identifyKeyword(const std::string& token) {
    std::string tok = token;
    enum KEYWORD_TYPE keywordType;

    if (tok == "*" || tok == "+" || tok == "-" || tok == "/" || tok == "<" || tok == ">" || 
        tok == "=="|| tok == "&&"|| tok == "||"|| tok == ">="|| tok == "<=") {
        keywordType = KEYWORD_OPERATOR;
    } else if (StringUtils::isValidNumberString(tok)) {
        keywordType = KEYWORD_CONSTANT;
    } else if (tok == "if") {
        keywordType = KEYWORD_CONDITIONAL;
    } else if (tok == "define") {
        keywordType = KEYWORD_VARIABLE_DEF;
    } else if (tok == "lambda") { // Function definition
        keywordType = KEYWORD_LAMBDA_DEF;
    } else if (tok.empty()) {
        keywordType = KEYWORD_EMPTY;
        db("Warning. Empty keyword");
    } else {
        keywordType = KEYWORD_SYMBOL;
    } 
    return keywordType;
}
