#include "gtest/gtest.h"

#include "tree/tree_serialization.hpp"

/****
## Purpose
Verify correctness of the `tree::parseString` function in the event that string contains integer value

## Input
    * `str`      String for parsing
    * `result`   Parsed value

## Expected result
    * String  `+12` parsed to  `+12` integer value
    * String `-123` parsed to `-123` integer value
    * String `1234` parsed to `1234` integer value
****/
TEST(string_parser, integer) {
    std::variant<int, double, std::string> result;

    std::string str = "+12";
    auto type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::Integer);
    EXPECT_EQ(std::get<int>(result), 12);

    str = "-123";
    type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::Integer);
    EXPECT_EQ(std::get<int>(result), -123);

    str = "1234";
    type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::Integer);
    EXPECT_EQ(std::get<int>(result), 1234);
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
TEST(string_parser, double) {
    std::variant<int, double, std::string> result;

    std::string str = "+1.2";
    auto type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::Double);
    EXPECT_EQ(std::get<double>(result), 1.2);

    str = "-1.23";
    type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::Double);
    EXPECT_EQ(std::get<double>(result), -1.23);

    str = "1.234";
    type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::Double);
    EXPECT_EQ(std::get<double>(result), 1.234);
}

/****
## Purpose
Verify correctness of the `tree::parseString` function in the event that string contains string value

## Input
    * `str`      String for parsing
    * `result`   Parsed value

## Expected result
    * String `""` parsed to empty string
    * String `"12345"` parsed to `12345` string
****/
TEST(string_parser, string) {
    std::variant<int, double, std::string> result;

    std::string str = "\"\"";
    auto type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::String);
    EXPECT_EQ(std::get<std::string>(result), "");

    str = "\"12345\"";
    type = tree::parseString(str, result);
    EXPECT_EQ(type, tree::StorageType::String);
    EXPECT_EQ(std::get<std::string>(result), "12345");
}

/****
## Purpose
Verify correctness of the `tree::parseString` function in the event that input string is incorrect

## Input
    * `str`      String for parsing
    * `result`   Parsed value

## Expected result
    * String `"` didn't parse due to missing closing quotes
    * String `9223372036854775808` didn't parse due to the number is too big
****/
TEST(string_parser, error) {
    std::variant<int, double, std::string> result;

    std::string str = "\"string";
    EXPECT_EQ(tree::parseString(str, result), tree::StorageType::None);

    str = "9223372036854775808";
    EXPECT_EQ(tree::parseString(str, result), tree::StorageType::None);
}