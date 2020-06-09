#include "../Parser.h"
#include "../Lexer.h"
#include "../AbstractSyntaxTree.h"
#include "gtest/gtest.h"

TEST(Parser, Basic) {
    std::string code = "(+ 5 6)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    // Parser here
    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    root->cleanSyntaxTree();
    delete root;
}
/*
TEST(Parser, Basic) {
    std::string code = "(list 4 5 6)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    // Parser here
    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    root->cleanSyntaxTree();
    delete root;
}*/