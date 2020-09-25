#include "../AbstractSyntaxTree.h"
#include "../Lexer.h"
#include "../Parser.h"
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

TEST(Parser, ParseRecursion) {
    std::string code =
        "(lambda inc a\n"
        "    (+ 1 a)\n"
        ")\n"
        "(lambda (dec) (a)\n"
        "    (- a 1)\n"
        ")\n"
        "(lambda (factorial) (n)\n"
        "    (if (== n 1)\n"
        "        (1)\n"
        "        (*\n"
        "            (factorial (dec n))\n"
        "            (n)\n"
        "        )\n"
        "    )\n"
        ")\n"
        "\n"
        "(factorial (inc 7))";
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