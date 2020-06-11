#include "gtest/gtest.h"
#include "../Evaluator.h"
#include "../Parser.h"
#include "../Lexer.h"

TEST(Evaluator, Sane) {
    EXPECT_EQ(-1, -1);
}

TEST(Evaluator, nothing) {
    std::string code = "( () () )";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 0);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, nothing2) {
    std::string code = "";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 0);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, fault) {
    std::string code = "(< (1) (2) (3))";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    bool testSuccess = false;
    Evaluator pEvaluator;
    try {
        double ret = pEvaluator.eval(root);
    } catch (...) {
        testSuccess = true;
    }
    EXPECT_EQ(testSuccess, true);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, logical_ops) {
    std::string code = "( && \
    (== 5 5) \
    (< (1) 2))";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 1);

    root->cleanSyntaxTree();
    delete root;
}
