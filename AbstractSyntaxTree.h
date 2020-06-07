#ifndef INCLUDE_AST_H
#define INCLUDE_AST_H
#include <vector>
#include <map>
#include <string>

enum KEYWORD_TYPE {KEYWORD_UNKNOWN, KEYWORD_OPERATOR, KEYWORD_CONSTANT, KEYWORD_CONDITIONAL, 
    KEYWORD_SYMBOL, KEYWORD_LAMBDA_DEF, KEYWORD_VARIABLE_DEF};

class SyntaxTreeNode {
public:
    class Symbol {
    public:
        enum SYMBOL_TYPE {SYMBOL_TYPE_VAR, SYMBOL_TYPE_LAMBDA};
        enum SYMBOL_TYPE type;
        double value = 0;
        SyntaxTreeNode* funcDef = nullptr; // Node containing definition of function.
        Symbol& operator=(const Symbol& other) {
            if (this != &other) {
                this->type = other.type;
                this->value = other.value;
            }
            return *this;
        }
    };
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
    std::map<std::string, SyntaxTreeNode::Symbol> symbolTable;
    // Add symbol to all children's symbol table.
    void propagateSymbol(std::pair<std::string, SyntaxTreeNode::Symbol> symbol);
    std::size_t nodeid;
private:
    static std::size_t allocated;

};
#endif