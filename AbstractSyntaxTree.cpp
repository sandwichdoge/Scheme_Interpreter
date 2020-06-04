#include "AbstractSyntaxTree.h"
#include "StringUtils.h"

SyntaxTreeNode::SyntaxTreeNode() {

}

SyntaxTreeNode::~SyntaxTreeNode() {
}

SyntaxTreeNode* SyntaxTreeNode::createChildNode() {
    SyntaxTreeNode *ret = new SyntaxTreeNode;
    ret->parent = this;
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
    } else {
        this->keywordType = KEYWORD_UDF;
    } 
}