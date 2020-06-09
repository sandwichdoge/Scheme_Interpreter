#include "gtest/gtest.h"
#include "../Lexer.h"

TEST(Lexer, Quotes) {
    std::string code = "(\"hello world\")";
    Lexer pLexer;
    std::vector<std::string> tokens;
    pLexer.lex(code, tokens);
    EXPECT_EQ(tokens.size(), 5);
    EXPECT_EQ(tokens[2], "hello world");
}