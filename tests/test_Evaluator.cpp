#include "gtest/gtest.h"
#include "../Evaluator.h"
#include "../Parser.h"
#include "../Lexer.h"

TEST(Evaluator, basic) {
    std::string code = "(+ 5 6 1)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root)._doubledata;
    EXPECT_FLOAT_EQ(ret, 12);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, if) {
    std::string code = "(if  \
    (&& \
        (< (1) (2)) \
        (1) \
    )  \
    (+ (554) (1)) \
    (666) \
)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root)._doubledata;
    EXPECT_FLOAT_EQ(ret, 555);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, if2) {
    std::string code = "(define (x) (9)) \
(if (1) \
    ( \
        ( define (x) (+ (x) (1)) ) \
        (x) \
    ) \
    (x) \
)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root)._doubledata;
    EXPECT_FLOAT_EQ(ret, 10);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, lambda_recursion) {
    std::string code = "(lambda inc a\n"
"    (+ 1 a)\n"
")\n"
"(lambda (dec) (a)\n"
"    (- a 1)\n"
")\n"
"(lambda (factorial) (n)\n"
"    (if (<= n 1)\n"
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

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root)._doubledata;
    EXPECT_FLOAT_EQ(ret, 40320);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, lambda_zeroarg) {
    std::string code = "(lambda retone () (1)) \
(lambda rettwo () (2)) \
(if 1 \
    (retone) \
    (rettwo()) \
)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root)._doubledata;
    EXPECT_FLOAT_EQ(ret, 1);

    root->cleanSyntaxTree();
    delete root;
}

TEST(Evaluator, fibonacci) {
    std::string code = "(lambda fibo n\
    (if (< n 2) \
        n\
        (+ (fibo (- n 1)) (fibo (- n 2)))\
    )\
    )\
    (fibo 9)";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);

    Parser pParser;
    pParser.setTokens(tokens);
    SyntaxTreeNode *root = new SyntaxTreeNode;
    pParser.parse(root);

    Evaluator pEvaluator;
    double ret = pEvaluator.eval(root)._doubledata;
    EXPECT_FLOAT_EQ(ret, 34);

    root->cleanSyntaxTree();
    delete root;
}