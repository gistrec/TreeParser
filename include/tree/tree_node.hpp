#ifndef TREE_NODE
#define TREE_NODE

#include <string>
#include <vector>
#include <memory>


namespace tree {

enum class StorageType {
	String,
	Double,
	Integer,
    None
};

class Node {
public:
	using NodePtr      = std::shared_ptr<Node>;
	using ChildrenType = std::vector<NodePtr>;

	StorageType virtual getStorageType() const = 0;

	inline const ChildrenType& getChildren() const {
		return _children;
	}

    inline void addChild(const NodePtr& child) {
        _children.push_back(child);
    }

private:
	ChildrenType _children;
};

class StringNode : public Node {
public:
	using Node::getChildren;

	inline explicit StringNode(const std::string& value) : _value(value) {};

	inline StorageType getStorageType() const override {
		return StorageType::String;
	}

	inline std::string& getStoredValue() {
		return _value;
	}

	inline ~StringNode() {}

private:
	std::string _value;
};

class DoubleNode : public Node {
public:
	using Node::getChildren;

    inline explicit DoubleNode(double value) : _value(value) {};

	inline StorageType getStorageType() const override {
		return StorageType::Double;
	}

	inline double& getStoredValue() {
		return _value;
	}

	inline ~DoubleNode() {}

private:
	double _value;
};

class IntegerNode : public Node {
public:
	using Node::getChildren;

    inline explicit IntegerNode(int value) : _value(value) {};

	inline StorageType getStorageType() const override {
		return StorageType::Integer;
	}

	inline int& getStoredValue() {
		return _value;
	}

	inline ~IntegerNode() {}

private:
	int _value;
};
} // namespace tree

#endif // TREE_NODE
