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
    void evalVarDef(SyntaxTreeNode *node);
    void evalLambdaDef(SyntaxTreeNode *node);
    double evalConditional(SyntaxTreeNode *node);
    double evalSymbol(SyntaxTreeNode* node);
    bool isEqual(double x, double y);
};

#endif