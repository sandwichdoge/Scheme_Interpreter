#include "Evaluator.h"
#include <iostream>
#include "StringUtils.h"
#include <cassert>

Evaluator::Evaluator() {
}

Evaluator::~Evaluator(){
}

double Evaluator::eval(SyntaxTreeNode *root) {
    // Traverse and eval all children.
    std::cout << "eval:" << root->token << "\n";
    std::cout << "Child nodes count:" << root->childNodes.size() << "\n";
    std::vector<double> results;
    for (std::size_t i = 0; i < root->childNodes.size(); ++i) {
        double ret = eval(root->childNodes[i]);
        results.push_back(ret);
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

    // TODO if token is a conditional, call conditionalHandler.

    // TODO if token is a UDF, its children are its arguments. Map to its definition.
    
    if (results.size() > 0) {
        return results[0];
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
        assert(vOperands.size() == 2 && "Error. Substraction only takes 2 operands.");
        ret = vOperands.at(0) - vOperands.at(1);
    } else if (op == "*") {
        ret = vOperands.at(0);
        for (std::size_t i = 1; i < vOperands.size(); ++i) {
            ret *= vOperands.at(i);
        }
    } else if (op == "/") {
        assert(vOperands.size() == 2 && "Error. Division only takes 2 operands.");
        ret = vOperands.at(0) / vOperands.at(1);
    } else if (op == "<") {
        assert(vOperands.size() == 2 && "Error. Comparison only takes 2 operands.");
        ret = (double)(vOperands.at(0) < vOperands.at(1));
    } else if (op == ">") {
        assert(vOperands.size() == 2 && "Error. Comparison only takes 2 operands.");
        ret = (double)(vOperands.at(0) > vOperands.at(1));
    } else if (op == "=") {
        assert(vOperands.size() == 2 && "Error. Comparison only takes 2 operands.");
        ret = (double)(vOperands.at(0) == vOperands.at(1));
    } else if (op == "&") {
        assert(vOperands.size() == 2 && "Error. Comparison only takes 2 operands.");
        ret = (double)(vOperands.at(0) && vOperands.at(1));
    }
    return ret;
}
