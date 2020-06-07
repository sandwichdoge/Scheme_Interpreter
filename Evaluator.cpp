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
    std::vector<double> results; // Evaluted results of all children.
    
    // Evaluate IF test before clauses.
    if (root->keywordType == KEYWORD_CONDITIONAL) {
        ret = evalConditional(root);
    } else if (root->keywordType == KEYWORD_VARIABLE_DEF) {
        evalVarDef(root);
    } else if (root->keywordType == KEYWORD_LAMBDA_DEF) {
        evalLambdaDef(root);
    } else { // For non-if clauses, evaluate everything first.
        for (std::size_t i = 0; i < root->childNodes.size(); ++i) {
            ret = eval(root->childNodes[i]);
            results.push_back(ret);
        }
    }

    // If keyword is a constant, convert it to double and return it.
    if (root->keywordType == KEYWORD_CONSTANT) {
        double ret = 0;
        if (StringUtils::stringToDouble(root->token, ret) == true) {
            return ret;
        } else {
            db("Error parsing constant: " << root->token);
            exit(1);
        }
    }

    // If token is an operator, calculate result from its children and return evaluated value.
    if (root->keywordType == KEYWORD_OPERATOR) {
        ret = mapOp(root->token, results);
        return ret;
    }

    // TODO if token is a UDF, its children are its arguments. Map to its definition.
    if (root->keywordType == KEYWORD_SYMBOL) {
        db("Symbol:" << root->token);
        return evalSymbol(root);
    }

    // In case of something like ((2)) or ((1) (2)), this happens.
    root->evaluated = true;
    root->value = ret;
    return ret;
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
        eassert(vOperands.size() == 2, "Error. Division takes 2 operands.");
        ret = vOperands.at(0) / vOperands.at(1);
    } else if (op == "<") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) < vOperands.at(1));
    } else if (op == ">") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) > vOperands.at(1));
    } else if (op == "=") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) == vOperands.at(1));
    } else if (op == "&") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) && vOperands.at(1));
    } else if (op == "|") {
        eassert(vOperands.size() == 2, "Error. Comparison takes 2 operands.");
        ret = (double)(vOperands.at(0) || vOperands.at(1));
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
    auto it = node->symbolTable.find(node->token);
    if (it == node->symbolTable.end()) {
        db("Undefined symbol " << node->token);
        exit(1);
    }
    if (it->second.type == SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR) {
        db("Variable " << it->second.value);
        return it->second.value;
    } else {
        db("Lambdas not yet implemented.");
        // Check and replace all children nodes with argument nodes, make a copy of node then eval.
        // Make a node in place, traverse, 
        // swap all nodes whose token equals argSymbol with real argValue.
        SyntaxTreeNode argValue = *(node->childNodes[0]); // Real value
        std::string argSymbol = it->second.funcDef->childNodes[1]->token; // In def
        SyntaxTreeNode *lambdaDef = it->second.funcDef->childNodes[2]; // Lambda def's syntax node
        // No more use for arguments
        for (std::size_t i = 0; i < node->childNodes.size(); ++i) {
            delete node->childNodes[i];
        }
        node->childNodes.clear();

        // Copy lambda def into node. Lambda def is just a blueprint.
        node->token = lambdaDef->token;
        node->keywordType = lambdaDef->keywordType;
        for (std::size_t i = 0; i < lambdaDef->childNodes.size(); ++i) {
            SyntaxTreeNode *child = new SyntaxTreeNode();
            *child = *(lambdaDef->childNodes[i]);
            node->childNodes.push_back(child);
        }
    
        // Replace argSymbol with real argValue. Only keep children of argValue.
        //expandVar(node, argSymbol, &argValue);

        // Evaluate self
        //eval(node);

        // Clean up
        for (std::size_t i = 0; i < node->childNodes.size(); ++i) {
            delete node->childNodes[i];
        }
        node->childNodes.clear();
        return 0;
    }
}

void Evaluator::expandVar(SyntaxTreeNode* functionNode, const std::string& argSymbol, SyntaxTreeNode* val) {
    for (std::size_t i = 0; i < functionNode->childNodes.size(); ++i) {
        expandVar(functionNode->childNodes[i], argSymbol, val);
    }
    if (functionNode->keywordType == KEYWORD_SYMBOL && functionNode->token == argSymbol) {
        // Keep children of val.
        
    }
}

#define EPSILON 0.001
bool Evaluator::isEqual(double x, double y) {
    return (abs(x - y) < EPSILON);
}
