#include "gtest/gtest.h"

#include "tree/tree_serialization.hpp"


/****
## Purpose
Verify correctness of the `tree::read` and `tree::write` functions in the event that nonexistent file was passed

## Input
    * `nonexistent`    Path to a nonexistent file
    * `tree`           The tree

## Expected result
    * `tree::read`  throws `tree::TreeBadFile` exception
    * `tree::write` throws `tree::TreeBadFile` exception
****/
TEST(exceptions, TreeBadFile) {
    std::string nonexistent = "/asd/asd/asd/asd.txt";
    try {
        std::shared_ptr<tree::Node> tree;

        tree::read(nonexistent, tree);

        FAIL() << "We shouldn't get here.";
    } catch (const tree::TreeBadFile &error) {};

    try {
        std::shared_ptr<tree::Node> tree = std::make_shared<tree::StringNode>("index");

        tree::write(nonexistent, tree);

        FAIL() << "We shouldn't get here.";
    } catch (const tree::TreeBadFile &error) {};
}

/****
## Purpose
Verify correctness of the `tree::parseString` function in the event that string contains double value

## Input
    * `str`      String for parsing
    * `result`   Parsed value

## Expected result
    * String  `+1.2` parsed to  `+1.2` double value
    * String `-1.23` parsed to `-1.23` double value
    * String `1.234` parsed to `1.234` double value
****/
TEST(exceptions, TreeBadData) {
}
