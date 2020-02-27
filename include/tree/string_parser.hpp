#ifndef TREE_STRING_PARSER
#define TREE_STRING_PARSER

#include <variant>  // std::variant since C++17

#include "tree_node.hpp"


namespace tree {
//! @brief Getting value from string
//!
//! @param[in]  str            String for parsing
//! @param[out] result         Parsed value
//! @return                    Type of parsed value
StorageType parseString(const std::string& str, std::variant<int, double, std::string>& result);
} // namespace tree

#endif // TREE_STRING_PARSER
