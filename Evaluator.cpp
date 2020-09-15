#include "Evaluator.h"
#include <iostream>
#include "Utils/StringUtils.h"
#include "Utils/AssertError.h"
#include "Utils/Debug.h"
#include <cmath>

Evaluator::Evaluator() {
}

Evaluator::~Evaluator(){
}

double Evaluator::eval(SyntaxTreeNode *root) {
    // Traverse and eval all children.
    db("eval:" << root->token);
    db("Child nodes count:" << root->childNodes.size());
    double ret = 0;
    
    switch (root->keywordType) {
        case (KEYWORD_CONDITIONAL): {
            ret = evalConditional(root);
            break;
        }
        case (KEYWORD_VARIABLE_DEF): {
            evalVarDef(root);
            break;
        }
        case (KEYWORD_LAMBDA_DEF): {
            evalLambdaDef(root);
            break;
        }
        case (KEYWORD_CONSTANT): {
            if (root->evaluated) {
                ret = root->value;
            } else {
                bool tmp = StringUtils::stringToDouble(root->token, ret);
                root->evaluated = true;
                eassert(tmp == true, "Error. Invalid number:" + root->token);
            }
            break;
        }
        // For tokens with potentially unlimited children, evaluate everything first.
        default: {
            for (std::size_t i = 0; i < root->childNodes.size(); ++i) {
                ret = eval(root->childNodes[i]);
            }
            break;
        }
    }

    switch (root->keywordType) {
        // If token is an operator, calculate result from its children and return evaluated value.
        case (KEYWORD_OPERATOR): {
            ret = evalOp(root);
            break;
        }
        // If token is a symbol, map to its definition.
        case (KEYWORD_SYMBOL): {
            db("Symbol:" << root->token);
            ret = evalSymbol(root);
            break;
        }
        default: { // Empty token.
            break;
        }
    }

    // In case of something like ((2)) or ((1) (2)), i.e empty tokens, this happens.
    root->evaluated = true;
    root->value = ret;
    return ret;
}

double Evaluator::evalOp(SyntaxTreeNode *node) {
    std::vector<double> results; // Evaluted results of all children.
    for (std::size_t i = 0; i < node->childNodes.size(); ++i) {
        eassert(node->childNodes[i]->evaluated == true, "Error. Failed to evaluate operator, children not evaluted.");
        results.push_back(node->childNodes[i]->value);
    }
    return mapOp(node->token, results);
}

double Evaluator::mapOp(const std::string &op, std::vector<double> vOperands) {
    double ret = 0;
    if (op == "+") {
        for (std::size_t i = 0; i < vOperands.size(); ++i) {
            ret += vOperands.at(i);
        }
    } else if (op == "-") {
        eassert(vOperands.size() == 2, "Error. Substraction takes 2 operands.");
        ret = vOperands.at(0) - vOperands.at(1);
    } else if (op == "*") {
        ret = vOperands.at(0);
        for (std::size_t i = 1; i < vOperands.size(); ++i) {
            ret *= vOperands.at(i);
        }
    } else if (op == "/") {
        eassert(vOperands.size() == 2, "Error. Division takes 2 operands:" + op);
        ret = vOperands.at(0) / vOperands.at(1);
    } else if (op == "<") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) < vOperands.at(1));
    } else if (op == ">") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) > vOperands.at(1));
    } else if (op == "==") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) == vOperands.at(1));
    } else if (op == "&&") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) && vOperands.at(1));
    } else if (op == "||") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) || vOperands.at(1));
    } else if (op == "<=") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) <= vOperands.at(1));
    } else if (op == ">=") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)(vOperands.at(0) >= vOperands.at(1));
    } else if (op == "%") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands:" + op);
        ret = (double)((long)vOperands.at(0) % (long)vOperands.at(1));
    }
    return ret;
}

double Evaluator::evalConditional(SyntaxTreeNode *node) {
    eassert((node->childNodes.size() == 2 || node->childNodes.size() == 3), "Error. Conditional takes 2-3 arguments.");

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
    eassert(node->childNodes.size() == 2, "Error. Variable def only takes 2 arguments." + node->token);
    double val = eval(node->childNodes[1]);
    std::string id = node->childNodes[0]->token;

    SyntaxTreeNode::Symbol sym;
    sym.type = SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR;
    sym.value = val;

    db("Adding symbol " << id << "=" << val);
    node->parent->propagateSymbol({id, sym});
}

// (lambda (symbol) (var1) (definition))
void Evaluator::evalLambdaDef(SyntaxTreeNode *node) {
    eassert(node->childNodes.size() >= 3, "Error. Syntax error in lambda definition: " + node->childNodes[0]->token);
    db("Lambda def: " << node->childNodes[0]->token);
    SyntaxTreeNode::Symbol sym;
    sym.type = SyntaxTreeNode::Symbol::SYMBOL_TYPE_LAMBDA;
    sym.funcDef = node;
    std::string id = node->childNodes[0]->token;
    node->parent->propagateSymbol({id, sym});
}

double Evaluator::evalSymbol(SyntaxTreeNode *node) {
    // Look up node's symbolTable, get value
    db("NodeID " << node->nodeid);
    db("symbolTable size:" << node->symbolTable.size());
    auto symbolTableEntry = node->symbolTable.find(node->token);
    eassert(symbolTableEntry != node->symbolTable.end(), "Undefined symbol " + node->token);
    if (symbolTableEntry->second.type == SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR) {
        db("Variable " << symbolTableEntry->second.value);
        return symbolTableEntry->second.value;
    } else { // SYMBOL_TYPE_FUNCTION
        //eassert(node->childNodes.size() <= 1, "Lambdas only takes 0-1 argument: " + node->token);
        std::size_t lambdaDefIndex = symbolTableEntry->second.funcDef->childNodes.size() - 1;
        SyntaxTreeNode *lambdaDef = symbolTableEntry->second.funcDef->childNodes[lambdaDefIndex]; // Lambda def's syntax node

        // Try to process arguments accordingly to definition.
        std::vector<double> argValue;
        std::vector<std::string> argSymbol;
        if (node->childNodes.size() > 0) { // Lambda takes argument.
            for (std::size_t i = 0; i < node->childNodes.size(); ++i) {
                eassert(node->childNodes[i]->evaluated == true, "Child node has not been evaluated.");
                argValue.push_back(node->childNodes[i]->value); // Real value
                argSymbol.push_back(symbolTableEntry->second.funcDef->childNodes[1 + i]->token); // In def
            }
            // Ignore "lambda" keyword and lambda definition. So we subtract 2.
            eassert(symbolTableEntry->second.funcDef->childNodes.size() - 2 == argSymbol.size(), "Error. Argument count mismatch in function: " + node->token);
        }

        // Copy lambda def into node. Lambda def is just a blueprint. This changes node's content.
        node->constructLambdaNode(lambdaDef);
    
        // Recursively replace argSymbol with real argValue for all children. This changes node's content.
        if (node->childNodes.size() > 0) { // Lambda takes argument.
            expandVar(node, argSymbol, argValue);
        }

        // Evaluate self
        db("Evaluating self");
        double ret = eval(node);

        // Clean up
        node->cleanSyntaxTree();
        node->childNodes.clear();
        db("Return from func:" << ret);
        return ret;
    }
}

void Evaluator::expandVar(SyntaxTreeNode* functionNode, const std::vector<std::string>& argSymbols, const std::vector<double>& vals) {
    eassert(argSymbols.size() == vals.size(), "Error. Argument number mismatch.");
    db("arg count:" << argSymbols.size());
    db("children count:" << functionNode->childNodes.size());
    db("parent:" << functionNode->parent);
    db("parent's token:" << functionNode->parent->token);
    db("self's token:" << functionNode->token);
    db("self's keywordType:[SYMBOL=4]" << functionNode->keywordType);
    //__asm__("int $3");
    for (std::size_t i = 0; i < argSymbols.size(); ++i) {
        std::string argSymbol = argSymbols[i];
        double val = vals[i];
        if (functionNode->keywordType == KEYWORD_SYMBOL && functionNode->token == argSymbol) {
            db("Found symbol " + argSymbol);
            functionNode->keywordType = KEYWORD_CONSTANT;
            functionNode->evaluated = true;
            functionNode->value = val;
        }
    }

    for (std::size_t i = 0; i < functionNode->childNodes.size(); ++i) {
        expandVar(functionNode->childNodes[i], argSymbols, vals);
    }
}

#define EPSILON 0.001
bool Evaluator::isEqual(double x, double y) {
    return (fabs(x - y) < EPSILON);
}
