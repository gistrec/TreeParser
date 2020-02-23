#include "tree/string_parser.hpp"

// GCC has partial support charconv - only integral types supported from GCC 8.1
#if __cpp_lib_to_chars >= 201611
#include <charconv>
#else
#include <cstdlib>  // std::strtod
#endif


namespace tree {
//! @brief Getting value from string
//!
//! @param[in]  str            String for parsing
//! @param[out] result         Parsed value
//! @return                    Type of parsed value
StorageType parseString(const std::string& str, std::variant<int, double, std::string>& result) {
	const auto start = str.find_first_not_of(/* TAB */ 0x09);

    #if __cpp_lib_to_chars >= 201611
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
    #else
        try {
            // Integer
            if (str.find_first_not_of("-0123456789", start) == std::string::npos) {
                result = std::stoi(str.data() + start);
                return StorageType::Integer;
            }

            // Double
            if (str.find_first_not_of(".,-0123456789", start) == std::string::npos) {
                result = std::stod(str.data() + start);
                return StorageType::Double;
            }

            // String
            if (str[start] == '"' && str[str.size() - 1U] == '"') {
                result = str.substr(start + 1U, str.size() - 2U - start);

                return StorageType::String;
            }
        } catch (/* std::out_of_range or std::invalid_argument */...) {}

        return StorageType::None;
    #endif
}
} // namespace tree
