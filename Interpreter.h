#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include <string>
#include <vector>

#include "AbstractSyntaxTree.h"
#include "Evaluator.h"
#include "Lexer.h"
#include "Parser.h"
#include "SyntaxChecker.h"
#include "DataType.h"

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
    DataType eval();

    int run(DataType &result);

    std::vector<std::string> getTokens() { return _tokens; }
    std::string getCode() { return _code; }

   private:
    SyntaxTreeNode *astRoot = nullptr;
    bool isDelimChar(char c);
    std::string _code;
    std::vector<std::string> _tokens;
    Lexer *pLexer;
    Parser *pParser;
    Evaluator *pEvaluator;
    SyntaxChecker *pSyntaxChecker;
};
#endif