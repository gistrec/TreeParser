#ifndef TREE_EXCEPTIONS
#define TREE_EXCEPTIONS

#include <exception>
#include <string>


namespace tree {
//! @brief Error indicating that specified file does not exist
class TreeBadFile : public std::runtime_error {
public:
    TreeBadFile(const std::string& message) : std::runtime_error(message) {};
};

//! @brief Error indicating incorrect value
class TreeBadData : public std::runtime_error {
public:
    TreeBadData(const std::string& message) : std::runtime_error(message) {};
};
} // namespace tree

#endif // TREE_EXCEPTIONS