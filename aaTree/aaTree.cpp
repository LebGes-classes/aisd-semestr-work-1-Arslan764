#include "aaTree.h"

template <typename T>
aaTree<T>::aaTree()
{
	this->root = nullptr;

}

template <typename T>
aaTree<T>::~aaTree()
{
	clear();//TODO доделать
	// нужно удалить каждый Node из за отсутвия сборщика?
}

template <typename T>
void aaTree<T>::insert(T& value)// пользовательский метод, вызыввает внутренниий, рекурсивный
{
	root = insert(root, value);
}

template <typename T>
typename aaTree<T>::Node* aaTree<T>::insert(Node* node, T& value)
{
	if (node == nullptr)// если узел null, то создаем новый
	{
		return new Node(value);
	}
	else if (value < node->value)// классика бинарного дерева - если элемент меньше - идем в левое поддерево
	{
		node->left = insert(node->left, value);
	}
	else if (value > node->value)// если элемент больше - идем в правое поддерево
	{
		node->right = insert(node->right, value);
	}
	else
	{
		//дубликаты не допускаются?
		return node
	}
	// балансируем элементы
	node = skew(node);
	node = split(node);
	return node;
}

template <typename T>
typename aaTree<T>::Node* aaTree<T>::skew(Node* node)// метод балансировки, чтобы не допустить левого потомка того же уровня(правый поворот)
{
	/* из этого          получаем это
	* 
	*         |           |
	*         v           v
	*    L <- T    ==>    L -> T
	*   / \              /    / \
	*  A   B            A    B   R
	*/

	if (node == nullptr)
	{
		return nullptr;
	}

	if (node->left != nullptr && node->left->level == node->level)// если у левого потомка уровень как у родителя
	{
		Node *leftChild = node->left;//запоминаем L, левого потомка node T
		node->left = leftChild->right;// теперь левый потомок node T -  это бывший правый потомок L - B
		leftChild->right = node; // для самого L теперь правый потомок это T
		node = leftChild;// node теперь L
	}
	return node;
}

template <typename T>
typename aaTree<T>::Node* aaTree<T>::split(Node* node)// метод балансировки, чтобы не допустить двух правых потомков одного уровня(левый поворот)
{
	/* из этого              получаем это
	*
	*    |                     |
	*    v                     v
	*    T -> R -> X    ==>    R
	*   /    /                / \
	*  A    B                T   X
	*                       / \
	*                      A   B
	*/

	if (node == nullptr)
	{
		return nullptr;
	}
	if (node->right != nullptr && node->right->right != nullptr && node->level == node->right->right->level)// если уровень правого внука равен уровню родителя
	{
		Node* rightChild = node->right;// запоминаем R, правого потомка node T
		node->right = rightChild->left;// теперь правый потомок T - это бывший левый потомок R
		rightChild->left = node;// сам T теперь левый потомок R
		rightChild->level += 1;// R поднимается на уровень выше
		node = rightChild;// node теперь R
	}
	return node;
}

template <typename T>
void aaTree<T>::remove(T& value)
{
	root = remove(root, value);
}

template <typename T>
typename aaTree<T>::Node* aaTree<T>::remove(Node* node, T& value)
{

}

template <typename T>
bool aaTree<T>::contains(T& value)
{
	bool isFound = contains(root, value);
	return isFound;
}

template <typename T>
bool aaTree<T>::contains(Node* node, T& value)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->value == value)//не уверен как это в плюсах, нужен ли аналог equals?
	{
		return true;
	}
	else if (value < node->value) {
		return contains(node->left, value);
	}
	else if (value > node->value) {
		return contains(node->right, value);
	}
}