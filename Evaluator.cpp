#include "Evaluator.h"
#include <iostream>
#include "StringUtils.h"
#include <cassert>
#include <cmath>

Evaluator::Evaluator() {
}

Evaluator::~Evaluator(){
}

double Evaluator::eval(SyntaxTreeNode *root) {
    // Traverse and eval all children.
    std::cout << "eval:" << root->token << "\n";
    std::cout << "Child nodes count:" << root->childNodes.size() << "\n";
    std::vector<double> results;
    
    // Evaluate IF test before clauses.
    if (root->keywordType == KEYWORD_CONDITIONAL) {
        double ret = evalConditional(root);
        results.push_back(ret);
    } else if (root->keywordType == KEYWORD_VARIABLE_DEF) {
        evalVarDef(root);
    } else { // For non-if clauses, evaluate everything first.
        for (std::size_t i = 0; i < root->childNodes.size(); ++i) {
            double ret = eval(root->childNodes[i]);
            results.push_back(ret);
        }
    }

    // If keyword is a constant, convert it to double and return it.
    if (root->keywordType == KEYWORD_CONSTANT) {
        double ret = 0;
        if (StringUtils::stringToDouble(root->token, ret) == true) {
            return ret;
        } else {
            std::cout << "Error parsing constant: " << root->token << "\n";
            exit(1);
        }
    }

    // If token is an operator, calculate result from its children and return evaluated value.
    if (root->keywordType == KEYWORD_OPERATOR) {
        double ret = mapOp(root->token, results);
        std::cout << root->token << " returns [" << ret << "]\n";
        return ret;
    }

    // TODO if token is a UDF, its children are its arguments. Map to its definition.
    if (root->keywordType == KEYWORD_SYMBOL) {
        std::cout << "Symbol:" << root->token << "\n";
        return evalSymbol(root);
    }

    // In case of something like ((2)) or ((1) (2)), this happens.
    if (results.size() > 0) {
        return results[results.size() - 1]; // Return last result.
    } else {
        return 0;
    }
}

double Evaluator::mapOp(const std::string &op, std::vector<double> vOperands) {
    double ret = 0;
    if (op == "+") {
        for (std::size_t i = 0; i < vOperands.size(); ++i) {
            ret += vOperands.at(i);
        }
    } else if (op == "-") {
        assert(vOperands.size() == 2 && "Error. Substraction takes 2 operands.");
        ret = vOperands.at(0) - vOperands.at(1);
    } else if (op == "*") {
        ret = vOperands.at(0);
        for (std::size_t i = 1; i < vOperands.size(); ++i) {
            ret *= vOperands.at(i);
        }
    } else if (op == "/") {
        assert(vOperands.size() == 2 && "Error. Division takes 2 operands.");
        ret = vOperands.at(0) / vOperands.at(1);
    } else if (op == "<") {
        assert(vOperands.size() == 2 && "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) < vOperands.at(1));
    } else if (op == ">") {
        assert(vOperands.size() == 2 && "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) > vOperands.at(1));
    } else if (op == "=") {
        assert(vOperands.size() == 2 && "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) == vOperands.at(1));
    } else if (op == "&") {
        assert(vOperands.size() == 2 && "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) && vOperands.at(1));
    } else if (op == "|") {
        assert(vOperands.size() == 2 && "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) || vOperands.at(1));
    }
    return ret;
}

double Evaluator::evalConditional(SyntaxTreeNode *node) {
    assert((node->childNodes.size() == 2 || node->childNodes.size() == 3) && "Error. Conditional takes 2-3 arguments.");

    double test = eval(node->childNodes[0]);
    double ret = 0;
    if (!isEqual(test, 0)) {
        ret = eval(node->childNodes[1]);
    } else if (node->childNodes.size() > 2) {
        ret = eval(node->childNodes[2]);
    }
    return ret;
}

// Eval "define" token. When a variable is defined, it must be evaluable.
void Evaluator::evalVarDef(SyntaxTreeNode *node) {
    double val = eval(node->childNodes[1]);
    std::string id = node->childNodes[0]->token;

    SyntaxTreeNode::Symbol sym;
    sym.type = SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR;
    sym.value = val;

    std::cout << "Adding symbol " << id << "=" << val << "\n";
    node->parent->propagateSymbol({id, sym});
}

double Evaluator::evalSymbol(SyntaxTreeNode *node) {
    // Look up node's symbolTable, get value
    std::cout << "NodeID " << node->nodeid << "\n";
    auto it = node->symbolTable.find(node->token);
    if (it == node->symbolTable.end()) {
        std::cout << "Undefined symbol " << node->token << "\n";
        exit(1);
    }
    if (it->second.type == SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR) {
        std::cout << "Variable " << it->second.value << "\n";
        return it->second.value;
    } else {
        std::cout << "Lambdas not yet implemented.\n";
        exit(1);
    }
}

#define EPSILON 0.001
bool Evaluator::isEqual(double x, double y) {
    return (abs(x - y) < EPSILON);
}
