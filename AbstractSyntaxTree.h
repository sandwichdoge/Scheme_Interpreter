#ifndef INCLUDE_AST_H
#define INCLUDE_AST_H
#include <vector>
#include <string>

enum KEYWORD_TYPE {KEYWORD_UNKNOWN, KEYWORD_OPERATOR, KEYWORD_CONSTANT, KEYWORD_CONDITIONAL, 
    KEYWORD_UDF, KEYWORD_UDF_DEF};

class SyntaxTreeNode {
public:
    SyntaxTreeNode();
    ~SyntaxTreeNode();
    // Create a child AST node.
    SyntaxTreeNode *createChildNode();
    // Clean up self and all children.
    void cleanSyntaxTree();

    SyntaxTreeNode *parent;
    std::string token;
    std::vector<SyntaxTreeNode *> childNodes;
    void identifyKeyword();
    enum KEYWORD_TYPE keywordType = KEYWORD_UNKNOWN;
    enum KEYWORD_TYPE what() {return keywordType;}
};
#endif