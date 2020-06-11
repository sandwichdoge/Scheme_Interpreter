#include "gtest/gtest.h"
#include "../AbstractSyntaxTree.h"

TEST(AST, Sanity) {
    EXPECT_EQ(1, 1);
}

TEST(AST, SingleConstruction) {
    SyntaxTreeNode *root = new SyntaxTreeNode;
    SyntaxTreeNode *child = nullptr;
    child = root->createChildNode();
    EXPECT_EQ(root->childNodes.size(), 1);
    EXPECT_NE(child, nullptr);

    root->cleanSyntaxTree();
    delete root;
}

TEST(AST, propagateSymbol) {
    SyntaxTreeNode *root = new SyntaxTreeNode;
    root->createChildNode();
    root->childNodes[0]->createChildNode();
    SyntaxTreeNode::Symbol sym;
    sym.type = SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR;
    sym.value = 123.0;
    root->propagateSymbol({"abc", sym});

    SyntaxTreeNode* child = root->childNodes[0];
    SyntaxTreeNode* grandchild = root->childNodes[0]->childNodes[0];
    EXPECT_EQ(root->symbolTable.size(), 0);
    EXPECT_EQ(child->symbolTable.size(), 1);
    EXPECT_EQ(grandchild->symbolTable.size(), 1);

    root->cleanSyntaxTree();
    delete root;
}

TEST(AST, propagateSymbolTable) {
    SyntaxTreeNode *root = new SyntaxTreeNode;
    root->createChildNode();
    root->childNodes[0]->createChildNode();
    SyntaxTreeNode::Symbol sym;
    sym.type = SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR;
    sym.value = 123.0;
    root->symbolTable.insert({"abc", sym});

    SyntaxTreeNode* child = root->childNodes[0];
    SyntaxTreeNode* grandchild = root->childNodes[0]->childNodes[0];

    root->propagateSymbolTable(root->symbolTable);

    EXPECT_EQ(root->symbolTable.size(), 1);
    EXPECT_EQ(child->symbolTable.size(), 1);
    EXPECT_EQ(grandchild->symbolTable.size(), 1);
    EXPECT_FLOAT_EQ(grandchild->symbolTable["abc"].type, SyntaxTreeNode::Symbol::SYMBOL_TYPE_VAR);
    EXPECT_FLOAT_EQ(grandchild->symbolTable["abc"].value, 123.0);

    root->cleanSyntaxTree();
    delete root;
}

TEST(AST, copyFrom) {
    SyntaxTreeNode *root = new SyntaxTreeNode;
    root->createChildNode();
    root->childNodes[0]->createChildNode();
    root->childNodes[0]->childNodes[0]->token = "<";

    SyntaxTreeNode *newRoot = new SyntaxTreeNode;
    newRoot->copyFrom(root, true);

    SyntaxTreeNode* child = newRoot->childNodes[0];
    SyntaxTreeNode* grandchild = newRoot->childNodes[0]->childNodes[0];
    EXPECT_EQ(grandchild->token, "<");

    root->cleanSyntaxTree();
    delete root;

    newRoot->cleanSyntaxTree();
    delete newRoot;
}
