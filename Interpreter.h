#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include <string>
#include <vector>
#include "SyntaxChecker.h"
#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"
#include "AbstractSyntaxTree.h"

class Interpreter {
   public:
    Interpreter();
    virtual ~Interpreter();

    int loadFile(const std::string &path);
    int loadCode(const std::string &code);

    int checkSyntax();
    // Get tokens from source code
    int lex();
    // Parse tokens
    int parse();
    double eval();

    int run(double &result);

    std::vector<std::string> getTokens() { return _tokens; }
    std::string getCode() { return _code; }

   private:
    SyntaxTreeNode *astRoot = nullptr;
    bool isDelimChar(char c);
    double mapOp(const std::string &op, std::vector<double>);
    std::string _code;
    std::vector<std::string> _tokens;
    Lexer *pLexer;
    Parser *pParser;
    Evaluator *pEvaluator;
    SyntaxChecker *pSyntaxChecker;
};
#endif