#include "tree/string_parser.hpp"

#include <sstream> // std::istringstream


namespace tree {
//! @brief Getting value from string
//!
//! @param[in]  str            String for parsing
//! @param[out] result         Parsed value
//! @return                    Type of parsed value
StorageType parseString(const std::string& str, std::variant<int, double, std::string>& result) {
    const auto start = str.find_first_not_of(/* TAB */ 0x09);

    // Different locales have different comma for floating point values
    // This program can't risk any impact on other parts of the system and changing global locale for sure can affect other processes
    // So we need to convert string to istringstream and set locale only for
    std::istringstream istr(str);
    istr.imbue(std::locale("C"));
    istr.exceptions(std::ios::failbit);

    try {
        // Integer
        if (str.find_first_not_of("-+0123456789", start) == std::string::npos) {
            int value;
            istr >> value;
            result = value;
            return StorageType::Integer;
        }

        // Double
        if (str.find_first_not_of(".-+0123456789", start) == std::string::npos) {
            double value;
            istr >> value;
            result = value;
            return StorageType::Double;
        }

        // String
        if (str[start] == '"' && str[str.size() - 1U] == '"') {
            result = str.substr(start + 1U, str.size() - 2U - start);

            return StorageType::String;
        }
    } catch (/* ios::exceptions */...) {}

    return StorageType::None;
}
} // namespace tree
