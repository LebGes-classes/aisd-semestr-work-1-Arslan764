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

		Node(T& value)
		{//можно инициализированным списком?
			this->value = value;
			level = 1;
			left = nullptr;
			right = nullptr;
		}
	};

	Node* root;

private:
	

	Node* insert(Node* node, T& value);
	Node* skew(Node* node);
	Node* split(Node* node);
	Node* remove(Node* node, T& value);
	void inOrder(Node* node);
	bool contains(Node* node, T& value);
	void clear(Node* node);

public:
	aaTree();
	~aaTree();

	void insert(T& value);
	void inOrder();
	bool contains(T& value);
	void remove(T& value);
	void clear();
};


