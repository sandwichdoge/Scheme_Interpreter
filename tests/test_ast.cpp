#include "gtest/gtest.h"
#include "../AbstractSyntaxTree.h"

TEST(AST, Sanity) {
    EXPECT_EQ(1, 1);
}

TEST(AST, SingleConstruction) {
    SyntaxTreeNode *root = new SyntaxTreeNode;
    root->createChildNode();
    EXPECT_EQ(root->childNodes.size(), 1);

    root->cleanSyntaxTree();
    delete root;
}
