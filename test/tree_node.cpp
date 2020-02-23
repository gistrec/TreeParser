#include "gtest/gtest.h"

#include "tree/tree_serialization.hpp"


TEST(tree_node, IntegerNode) {
    tree::IntegerNode node(2);

    EXPECT_EQ(node.getStoredValue(), 2);
    EXPECT_EQ(node.getChildren().size(), 0U);
    EXPECT_EQ(node.getStorageType(), tree::StorageType::Integer);
}

TEST(tree_node, DoubleNode) {
    tree::DoubleNode node(2.3);

    EXPECT_EQ(node.getStoredValue(), 2.3);
    EXPECT_EQ(node.getChildren().size(), 0U);
    EXPECT_EQ(node.getStorageType(), tree::StorageType::Double);
}

TEST(tree_node, StringNode) {
    tree::StringNode node("string");

    EXPECT_EQ(node.getStoredValue(), "string");
    EXPECT_EQ(node.getChildren().size(), 0U);
    EXPECT_EQ(node.getStorageType(), tree::StorageType::String);
}

TEST(tree_node, Children) {
    tree::IntegerNode node(1);

    EXPECT_EQ(node.getChildren().size(), 0U);

    std::shared_ptr<tree::Node> child = std::make_shared<tree::StringNode>("child");
    node.addChild(child);

    EXPECT_EQ(node.getChildren().size(), 1U);
    EXPECT_EQ(node.getChildren()[0]->getStorageType(), tree::StorageType::String);
}
