#pragma once


template <typename T>
class aaTree
{
	struct Node
	{
		T value;
		int level;
		Node* left;
		Node* right;

		Node(const T& value)
		{
			this->value = value;
			level = 1;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;

private:
	

	Node* insert(Node* node, const T& value);
	Node* skew(Node* node);
	Node* split(Node* node);
	Node* remove(Node* node, const T& value);
	void inOrder(Node* node);
	bool contains(Node* node, const T& value);
	void deleteSubtree(Node* node);

public:
	aaTree();
	~aaTree();

	void insert(const T& value);
	void inOrder();
	bool contains(const T& value);
	void remove(const T& value);
	void clear();
};


