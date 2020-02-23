#ifndef TREE_STRING_PARSER
#define TREE_STRING_PARSER

#include <charconv> // std::from_chars since C++17
#include <variant>  // std::variant since C++17

#include "tree_node.hpp"


namespace tree {
//! @brief Getting value from string
//!
//! @param[in]  str            String for parsing
//! @param[out] result         Parsed value
//! @return                    Type of parsed value
static StorageType parseString(const std::string& str, std::variant<int, double, std::string>& result) {
	const auto start = str.find_first_not_of(/* TAB */ 0x09);

	// Integer
	if (str.find_first_not_of("-0123456789", start) == std::string::npos) {
        int value;

		auto [p, ec] = std::from_chars(str.data() + start, str.data() + str.size(), value);
        if (ec != std::errc()) return StorageType::None;

        result = value;
        return StorageType::Integer;
	}

	// Double
	if (str.find_first_not_of(".,-0123456789", start) == std::string::npos) {
        double value;

		auto [p, ec] = std::from_chars(str.data() + start, str.data() + str.size(), value);
        if (ec != std::errc()) return StorageType::None;

        result = value;
        return StorageType::Double;
	}

	// String
	if (str[start] == '"' && str[str.size() - 1U] == '"') {
		result = str.substr(start + 1U, str.size() - 2U - start);

        return StorageType::String;
	}

	// Nothing
	return StorageType::None;
}
} // namespace tree

#endif // TREE_STRING_PARSER
