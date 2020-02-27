#include <algorithm> // std::equals

#include "gtest/gtest.h"

#include "tree/tree_serialization.hpp"

/****
## Purpose
Verify correctness of the `tree::read` and `tree::write` function

## Input
    * `input`    Name of file from which to read in the tree
    * `output`   The name of the file to which to write tree
    * `tree`     The tree

## Expected result
    * `input` file is equal to `output` file
****/
TEST(tree_serialization, serialization) {
    std::string input  = "test/input.txt";
    std::string output = "test/output.txt";

    std::shared_ptr<tree::Node> tree;

    tree::read(input, tree);
    tree::write(output, tree);

    std::ifstream in(input);
    std::ifstream out(output);

    EXPECT_TRUE(in.is_open());
    EXPECT_TRUE(out.is_open());

    EXPECT_TRUE(std::equal(std::istreambuf_iterator<char>(in.rdbuf()),
                           std::istreambuf_iterator<char>(),
                           std::istreambuf_iterator<char>(out.rdbuf())));
}
