#ifndef INCLUDE_EVALUATOR_H
#define INCLUDE_EVALUATOR_H
#include "AbstractSyntaxTree.h"
#include <map>

class Evaluator {
public:
    Evaluator();
    ~Evaluator();
    double eval(SyntaxTreeNode *root);
private:
    double mapOp(const std::string &op, std::vector<double> vOperands);
    double evalOp(SyntaxTreeNode *node);
    void evalVarDef(SyntaxTreeNode *node);
    void evalLambdaDef(SyntaxTreeNode *node);
    double evalConditional(SyntaxTreeNode *node);
    double evalSymbol(SyntaxTreeNode* node);
    // Traverse node, swap all nodes whose token = argSymbol with val.
    void expandVar(SyntaxTreeNode* functionNode, const std::vector<std::string>& argSymbol, const std::vector<double>& vals);
    bool isEqual(double x, double y);
};

#endif