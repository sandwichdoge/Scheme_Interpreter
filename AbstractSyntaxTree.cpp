#include "AbstractSyntaxTree.h"
#include "Utils/StringUtils.h"
#include "Utils/Debug.h"

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
        childNodes[i]->propagateSymbol(symbol);
        if (childNodes[i]->symbolTable.find(symbol.first) == childNodes[i]->symbolTable.end()) {
            childNodes[i]->symbolTable.insert(symbol);
        } else {
            childNodes[i]->symbolTable[symbol.first] = symbol.second;
        }
    }
}

void SyntaxTreeNode::propagateSymbolTable(std::map<std::string, SyntaxTreeNode::Symbol> table) {
    for (std::size_t i = 0; i < childNodes.size(); ++i) {
        childNodes[i]->propagateSymbolTable(table);
        childNodes[i]->symbolTable = table;
    }
}


void SyntaxTreeNode::copyFrom(const SyntaxTreeNode* other, bool preserveParent) {
    cleanSyntaxTree();
    this->childNodes.clear();
    SyntaxTreeNode* newRoot = duplicate(other); // Root of duplicated tree.
    this->keywordType = other->keywordType;
    this->token = other->token;
    this->value = other->value;
    this->evaluated = other->evaluated;
    for (std::size_t i = 0; i < newRoot->childNodes.size(); ++i) {
        this->childNodes.push_back(newRoot->childNodes[i]);
        this->childNodes[i]->parent = this;
    }
    delete newRoot;
    if (!preserveParent) {
        this->parent = other->parent;
    }
}

SyntaxTreeNode* SyntaxTreeNode::duplicate(const SyntaxTreeNode* other) {
    SyntaxTreeNode *newNode = new SyntaxTreeNode;
    newNode->keywordType = other->keywordType;
    newNode->token = other->token;
    newNode->value = other->value;
    newNode->evaluated = other->evaluated;
    newNode->parent = nullptr;

    for (std::size_t i = 0; i < other->childNodes.size(); ++i) {
        newNode->childNodes.push_back(duplicate(other->childNodes[i]));
    }
    for (std::size_t i = 0; i < newNode->childNodes.size(); ++i) {
        newNode->childNodes[i]->parent = newNode;
    }
    return newNode;
}
