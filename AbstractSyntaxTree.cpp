#include "AbstractSyntaxTree.h"
#include "StringUtils.h"

std::size_t SyntaxTreeNode::allocated = 0;

SyntaxTreeNode::SyntaxTreeNode() {
    allocated++;
    this->nodeid = allocated;
}

SyntaxTreeNode::~SyntaxTreeNode() {
}

SyntaxTreeNode* SyntaxTreeNode::createChildNode() {
    SyntaxTreeNode *ret = new SyntaxTreeNode;
    ret->parent = this;
    ret->symbolTable = this->symbolTable;
    childNodes.push_back(ret);
    return ret;
}

void SyntaxTreeNode::cleanSyntaxTree() {
    for (std::size_t i = 0; i < childNodes.size(); ++i) {
        childNodes.at(i)->cleanSyntaxTree();
        delete childNodes.at(i);
    }
}

void SyntaxTreeNode::identifyKeyword() {
    std::string tok = this->token;

    if (tok == "*" || tok == "+" || tok == "-" || tok == "/" || tok == "<" || tok == ">" || 
        tok == "=" || tok == "&" || tok == "|") {
        this->keywordType = KEYWORD_OPERATOR;
    } else if (StringUtils::isValidNumberString(tok)) {
        this->keywordType = KEYWORD_CONSTANT;
    } else if (tok == "if") {
        this->keywordType = KEYWORD_CONDITIONAL;
    } else if (tok == "define") {
        this->keywordType = KEYWORD_VARIABLE_DEF;
    } else if (tok == "lambda") { // Function definition
        this->keywordType = KEYWORD_LAMBDA_DEF;
    } else {
        this->keywordType = KEYWORD_SYMBOL;
    } 
}

void SyntaxTreeNode::propagateSymbol(std::pair<std::string, SyntaxTreeNode::Symbol> symbol) {
    for (std::size_t i = 0; i < childNodes.size(); ++i) {
        std::cout << "Adding symbol to node " << childNodes[i]->nodeid << "\n";
        std::cout << "Type " << symbol.second.type << "\n";
        childNodes[i]->propagateSymbol(symbol);
        childNodes[i]->symbolTable.insert(symbol);
    }
}