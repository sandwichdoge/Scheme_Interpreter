#include "gtest/gtest.h"
#include "../Evaluator.h"
#include "../Parser.h"
#include "../Lexer.h"

TEST(Evaluator, Sane) {
    EXPECT_EQ(-1, -1);
}
