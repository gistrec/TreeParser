#ifndef TREE_READER
#define TREE_READER

#include <queue>    // std::queue
#include <stack>    // std::stack
#include <fstream>  // std::ofstream

#include "string_parser.hpp"


namespace tree {
//! @brief Getting the number of tabs in a string
//!
//! @param str                 The string to tabs counting
//! @return                    Number of tabs
static size_t getTabCount(const std::string& str) {
	size_t index = 0U;

    for (; index < str.size() && str[index] == /* TAB */ 0x09; ++index) {}

	return index;
}

//! @brief Creating a node for value in line
//!
//! @param[in] line            String with value
//! @return                    One of nodes: IntegerNode, DoubleNode, StringNode
//!
//! @throw parse_error         In case of line contains an invalid value
static std::shared_ptr<Node> createNode(const std::string& line) {
    std::variant<int, double, std::string> value;

    auto type = tree::parseString(line, value);

    switch (type) {
        case StorageType::Integer:
            return std::make_shared<IntegerNode>(std::get<int>(value));

        case StorageType::Double:
            return std::make_shared<DoubleNode>(std::get<double>(value));

        case StorageType::String:
            return std::make_shared<StringNode>(std::get<std::string>(value));

        default:
            throw std::runtime_error("parse_error");
    }
}

//! @brief Print tree to given stream
//!
//! @param[out] tree           The tree to populate
//! @param[in]  stream         Stream to write in the tree
void print(const std::shared_ptr<Node>& tree, std::ostream& stream = std::cout) {
    using NodePtr   = std::shared_ptr<Node>;
    using NodeLevel = std::size_t;
    using NodeData  = std::pair<NodePtr, NodeLevel>; // Save level of node

    std::stack<NodeData> parents;
    parents.push({ tree, 0U });

    while (!parents.empty()) {
        const auto [node, level] = parents.top();
        parents.pop();

        for (size_t tabs = 0U; tabs < level; tabs++) {
            stream << '\t';
        }
        switch (node->getStorageType()) {
        case StorageType::Integer:
            stream << static_cast<IntegerNode*>(node.get())->getStoredValue() << std::endl;
            break;

        case StorageType::Double:
            stream << static_cast<DoubleNode*>(node.get())->getStoredValue() << std::endl;
            break;

        case StorageType::String:
            stream << static_cast<StringNode*>(node.get())->getStoredValue() << std::endl;
            break;
        }

        const auto& children = node->getChildren();

        for (auto it = children.rbegin(); it < children.rend(); ++it) {
            parents.push({*it, level + 1U});
        }
    }
}

//! @brief Read tree from the given file
//!
//! @param[in]  filename       Name of file from which to read in the tree
//! @param[out] tree           The tree to populate
//!
//! @throw file_error          In case of error reading from the file
//! @throw parse_error         In case of error deserializing the tree
void read(const std::string& filename, std::shared_ptr<Node>& tree) {
	std::ifstream file(filename, std::ifstream::in);

	if (!file.is_open()) {
		throw std::runtime_error("file_error: Cant't open input file " + filename);
	}

	// Количество табов перед строкой - уровень дерева
	std::stack<std::shared_ptr<Node>> parents;
	size_t level = 0U;

	// Обрабатываем корень дерева
	// Т.к. в неё может быть только один элемент
	std::string line;
	std::getline(file, line);

	if (getTabCount(line) != 0U) {
		throw std::runtime_error("parse_error");
	}

    tree = createNode(line);
    parents.push(tree);


	while (std::getline(file, line)) {
        size_t new_level = getTabCount(line);

        if (new_level == 0U || new_level > parents.size()) {
            throw std::runtime_error("parse_error");
        }

        auto node = createNode(line);

        while (level >= new_level) {
            parents.pop();
            level--;
        }

        parents.top()->addChild(node);
        parents.push(node);
        level = new_level;
	}
}

//! @brief Write tree to the given file
//!
//! @param[in] filename      The name of the file to which to write tree
//! @param[in] tree          The tree to output
//!
//! @throw file_error        In case of error writing to the file
void write(const std::string& filename, const std::shared_ptr<Node>& tree) {
    std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);

    if (!file.is_open()) {
        std::cout << "Lol";
        throw std::runtime_error("file_error");
    }

    print(tree, file);
}
} // namespace tree

#endif // TREE_READER
