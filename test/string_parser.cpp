#include "gtest/gtest.h"

#include "tree/tree_serialization.hpp"


TEST(string_parser, parseString) {
    try {
        using namespace tree;

        std::variant<int, double, std::string> result;

        std::string str = "12345";
        auto type = tree::parseString(str, result);
        EXPECT_EQ(type, tree::StorageType::Integer);
        EXPECT_EQ(std::get<int>(result), 12345);

        str = "1.12345";
        type = tree::parseString(str, result);
        EXPECT_EQ(type, tree::StorageType::Double);
        EXPECT_EQ(std::get<double>(result), 1.12345);

        str = "\"12345\"";
        type = tree::parseString(str, result);
        EXPECT_EQ(type, tree::StorageType::String);
        EXPECT_EQ(std::get<std::string>(result), "12345");

    } catch (const std::bad_variant_access&) {
        FAIL() << "Catch std::bad_variant_access";
    }
}
