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

	const ChildrenType& getChildren() const {
		return _children;
	}

    void addChild(const NodePtr& child) {
        _children.push_back(child);
    }

private:
	ChildrenType _children;
};

class StringNode : public Node {
public:
	using Node::getChildren;

	explicit StringNode(const std::string& value) : _value(value) {};

	StorageType getStorageType() const override {
		return StorageType::String;
	}

	std::string& getStoredValue() {
		return _value;
	}

	~StringNode() {}

private:
	std::string _value;
};

class DoubleNode : public Node {
public:
	using Node::getChildren;

    explicit DoubleNode(double value) : _value(value) {};

	StorageType getStorageType() const override {
		return StorageType::Double;
	}

	double& getStoredValue() {
		return _value;
	}

	~DoubleNode() {}

private:
	double _value;
};

class IntegerNode : public Node {
public:
	using Node::getChildren;

    explicit IntegerNode(int value) : _value(value) {};

	StorageType getStorageType() const override {
		return StorageType::Integer;
	}

	int& getStoredValue() {
		return _value;
	}

	~IntegerNode() {}

private:
	int _value;
};
} // namespace tree

#endif // TREE_NODE
