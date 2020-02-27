#include "tree/tree_serialization.hpp"

#include <stack>     // std::stack
#include <algorithm> // std::count


namespace tree {
//! @brief Creating a node for value in line
//!
//! @param[in] line            String with value
//! @return                    One of nodes: IntegerNode, DoubleNode, StringNode
//!
//! @throw parse_error         In case of line contains an invalid value
std::shared_ptr<Node> createNode(const std::string& line) {
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
void print(const std::shared_ptr<Node>& tree, std::ostream& stream) {
    using NodePtr   = std::shared_ptr<Node>;
    using NodeLevel = std::size_t;
    using NodeData  = std::pair<NodePtr, NodeLevel>; // Save level of node

    // Save stream locale to print floating point values with comma
    auto locale = stream.getloc();
    stream.imbue(std::locale("C"));

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
                stream << '"' << static_cast<StringNode*>(node.get())->getStoredValue() << '"' << std::endl;
                break;
        }

        const auto& children = node->getChildren();

        for (auto it = children.rbegin(); it < children.rend(); ++it) {
            parents.push({*it, level + 1U});
        }
    }

    // Restore stream locale
    stream.imbue(locale);
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

    std::stack<std::shared_ptr<Node>> parents;
    size_t level = 0U;

    // Process the root of the tree
    // The tree should have only one root
    std::string line;
    std::getline(file, line);

    // The number of tabs is equal to the node level
    auto tabCount = std::count(std::begin(line), std::end(line), /* TAB*/ 0x09);
    if (tabCount != 0U) {
        throw std::runtime_error("parse_error");
    }

    tree = createNode(line);
    parents.push(tree);


    while (std::getline(file, line)) {
        size_t new_level = std::count(std::begin(line), std::end(line), /* TAB*/ 0x09);

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
        throw std::runtime_error("file_error");
    }

    print(tree, file);
}
} // namespace tree
