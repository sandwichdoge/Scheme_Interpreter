#ifndef INCLUDE_EVALUATOR_H
#define INCLUDE_EVALUATOR_H
#include <map>

#include "AbstractSyntaxTree.h"

class Evaluator {
   public:
    Evaluator();
    ~Evaluator();
    DataType eval(SyntaxTreeNode *root);

   private:
    DataType mapOp(const std::string &op, std::vector<DataType> vOperands);
    DataType evalOp(SyntaxTreeNode *node);
    void evalVarDef(SyntaxTreeNode *node);
    void evalLambdaDef(SyntaxTreeNode *node);
    DataType evalConditional(SyntaxTreeNode *node);
    DataType evalSymbol(SyntaxTreeNode *node);
    // Traverse node, swap all nodes whose token = argSymbol with val.
    void expandVar(SyntaxTreeNode *functionNode, const std::vector<std::string> &argSymbol,
                   const std::vector<DataType> &vals);
};

#endif