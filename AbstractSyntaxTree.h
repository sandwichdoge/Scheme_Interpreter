#ifndef INCLUDE_AST_H
#define INCLUDE_AST_H
#include <map>
#include <string>
#include <vector>
#include "DataType.h"

enum KEYWORD_TYPE {
    KEYWORD_UNKNOWN,
    KEYWORD_OPERATOR,
    KEYWORD_CONSTANT,
    KEYWORD_CONDITIONAL,
    KEYWORD_SYMBOL,
    KEYWORD_LAMBDA_DEF,
    KEYWORD_VARIABLE_DEF,
    KEYWORD_EMPTY,
    KEYWORD_STRING
};

class SyntaxTreeNode {
   public:
    class Symbol {
       public:
        enum SYMBOL_TYPE { SYMBOL_TYPE_VAR, SYMBOL_TYPE_LAMBDA };
        enum SYMBOL_TYPE type;
        DataType value;
        SyntaxTreeNode* funcDef = nullptr;  // Node containing definition of function.
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
    SyntaxTreeNode* createChildNode();
    // Clean up all children.
    void cleanSyntaxTree();

    SyntaxTreeNode* parent;
    std::string token;
    std::vector<SyntaxTreeNode*> childNodes;
    enum KEYWORD_TYPE keywordType = KEYWORD_UNKNOWN;
    std::map<std::string, SyntaxTreeNode::Symbol> symbolTable;
    // Add symbol to all children's symbol table.
    void propagateSymbol(std::pair<std::string, SyntaxTreeNode::Symbol> symbol);
    void propagateSymbolTable(std::map<std::string, SyntaxTreeNode::Symbol> table);
    void propagateSymbolTable_Lambdas(std::map<std::string, SyntaxTreeNode::Symbol> table);

    bool evaluated = false;
    DataType value;
    std::size_t nodeid;
    // Make a copy of another node, recursively duplicate all children. Copy everything except symbolTable.
    // Preserve root pointer, throw away children.
    void constructLambdaNode(const SyntaxTreeNode* defNode);

   private:
    static std::size_t allocated;
    // Return root of new duplicated tree. Symbol table and is not copied because scoping.
    // Must cleanSyntaxTree() before calling this.
    SyntaxTreeNode* duplicate(const SyntaxTreeNode* other);
};
#endif