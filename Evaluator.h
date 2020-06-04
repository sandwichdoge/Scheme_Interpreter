#ifndef INCLUDE_EVALUATOR_H
#define INCLUDE_EVALUATOR_H
#include "AbstractSyntaxTree.h"

class Evaluator {
public:
    Evaluator();
    ~Evaluator();
    double mapOp(const std::string &op, std::vector<double> vOperands);
    double eval(SyntaxTreeNode *root);
private:
    bool isEqual(double x, double y);
};

#endif