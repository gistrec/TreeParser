#include "tree/tree_serialization.hpp"

namespace tree {

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
} // namespace tree
