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

TEST(Evaluator, multiargs) {
    std::string code = "(lambda sum a b c \
        (+ a b c) \
    ) \
    (sum 2 3 1)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 6);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, multiargs_fault_handle) {
    std::string code = "(lambda sum a b c \
        (+ a b c) \
    ) \
    (sum 2 3)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    bool success = false;
    try {
        Evaluator pEvaluator;
        double ret = pEvaluator.eval(root);
    } catch (...) {
        success = true;
    }
    EXPECT_EQ(success, true);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, multiargs2) {
    std::string code = "(lambda sum a b\
        (+ a b)\
    )\
    (lambda dec a b\
        (- a b)\
    ) \
    (sum 5 (dec 1 1))";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 5);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, multiargs3) {
    std::string code = "(lambda sum a b\
        (+ a b)\
    )\
    (lambda diff a b\
        (\
            (define x (- a b))\
            (if (> x 0)\
                x\
                (- 0 x)\
            )\
        )\
    )\
    (sum 5 (diff 1 2))";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 6);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, multiargs4) {
    std::string code = "(lambda sum a b\
        (+ a b)\
    )\
    (lambda abs n\
        (if (> n 0)\
            n\
            (- 0 n)\
        )\
    )\
    (lambda diff a b\
        (\
            (define x (- a b))\
            (abs x)\
        )\
    )\
    (sum 5 (diff 1 4))";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root);
    EXPECT_FLOAT_EQ(ret, 8);

    root->cleanSyntaxTree();
    delete root;
}