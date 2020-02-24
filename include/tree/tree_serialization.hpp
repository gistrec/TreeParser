#ifndef TREE_READER
#define TREE_READER

#include <fstream>  // std::ofstream
#include <iostream> // std::cout

#include "string_parser.hpp"


namespace tree {
//! @brief Creating a node for value in line
//!
//! @param[in] line            String with value
//! @return                    One of nodes: IntegerNode, DoubleNode, StringNode
//!
//! @throw parse_error         In case of line contains an invalid value
std::shared_ptr<Node> createNode(const std::string& line);

//! @brief Print tree to given stream
//!
//! @param[out] tree           The tree to populate
//! @param[in]  stream         Stream to write in the tree
void print(const std::shared_ptr<Node>& tree, std::ostream& stream = std::cout);

//! @brief Read tree from the given file
//!
//! @param[in]  filename       Name of file from which to read in the tree
//! @param[out] tree           The tree to populate
//!
//! @throw file_error          In case of error reading from the file
//! @throw parse_error         In case of error deserializing the tree
void read(const std::string& filename, std::shared_ptr<Node>& tree);

//! @brief Write tree to the given file
//!
//! @param[in] filename      The name of the file to which to write tree
//! @param[in] tree          The tree to output
//!
//! @throw file_error        In case of error writing to the file
void write(const std::string& filename, const std::shared_ptr<Node>& tree);
} // namespace tree

#endif // TREE_READER
