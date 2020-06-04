#include "Interpreter.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Interpreter::Interpreter() {
    astRoot = new SyntaxTreeNode();
    pLexer = new Lexer();
    pParser = new Parser();
    pEvaluator = new Evaluator();
    pSyntaxChecker = new SyntaxChecker();
}

Interpreter::~Interpreter() {
    astRoot->cleanSyntaxTree();
    if (astRoot) delete astRoot;
    if (pParser) delete pParser;
    if (pLexer) delete pLexer;
    if (pEvaluator) delete pEvaluator;
    if (pSyntaxChecker) delete pSyntaxChecker;
}

int Interpreter::loadFile(const std::string &path) {
    std::ifstream fd;
    fd.open(path);
    std::stringstream buf;

    if (fd.is_open()) {
        buf << fd.rdbuf();
    } else {
        return -1;
    }

    fd.close();
    _code = buf.str();
    return 0;
}

int Interpreter::lex() {
    pLexer->lex(_code, _tokens);
    return 0;
}

int Interpreter::checkSyntax() {
    return pSyntaxChecker->checkSyntax(_code);
}

int Interpreter::parse() {
    pParser->setTokens(_tokens);
    pParser->parse(astRoot);
    return 0;
}

double Interpreter::eval() {
    return pEvaluator->eval(astRoot);
}

int Interpreter::run(double& result) {
    // Check basic syntax.
    if (checkSyntax() < 0) return -1;
    // Split source into word tokens.
    if (lex() < 0) return -2;
    // Parse tokens into AST.
    if (parse() < 0) return -3;
    // Evaluate AST.
    result = eval();
    
    return 0;
}
