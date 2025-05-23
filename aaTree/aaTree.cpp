#include "aaTree.h"
#include <iostream>


//конструктор
template <typename T>
aaTree<T>::aaTree()
{
	this->root = nullptr;

}


//деструктор
template <typename T>
aaTree<T>::~aaTree()
{
	clear();//вызываем метод, очищающий дерево
}

template <typename T>
void aaTree<T>::insert(const T& value)// пользовательский метод добавления, вызыввает внутренниий, рекурсивный
{
	root = insert(root, value);
}

template <typename T>
typename aaTree<T>::Node* aaTree<T>::insert(Node* node, const T& value)
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
		return node;
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
void aaTree<T>::remove(const T& value)//пользовательский метод удаления
{
	root = remove(root, value);
}

template <typename T>
typename aaTree<T>::Node* aaTree<T>::remove(Node* node, const T& value)
{
	if (node == nullptr)
	{
		return nullptr;//дошли до листа, значения нет, удалять нечего
	}
	if (value < node->value)
	{
		node->left = remove(node->left, value);// удаляем в левом поддереве
	}
	else if (value > node->value)
	{
		node->right = remove(node->right, value);// удаляем в правом поддереве
	}
	else
	{
		Node* temp = nullptr;
		if (node->left == nullptr && node->right == nullptr)// у узла нет потомков - спокойно удаляем
		{
			delete node;
			return nullptr;
		}
		else if (node->right == nullptr)// только левый потомок не null
		{
			temp = node->left;
			delete node;
			return temp;//левый потомок занимает место удаленного узла
		}
		else if (node->left == nullptr)// только правый потомок не null
		{
			temp = node->right;
			delete node;
			return temp;//правй потомок занимает место удаленного узла
		}
		else //оба потомка не null -> заменяем на минимальный узел правого поддерева
		{
			temp = node->right;
			while (temp->left != nullptr)//находим мин узел правого поддерева
			{
				temp = temp->left;
			}
			node->value = temp->value;//присваеиваем значение мин узла удаляемому
			node->right = remove(node->right, temp->value);//удаляем узел, которым заменили удаляемый
			//TODO доделать
		}
	}

	if (node == nullptr) {
		return nullptr;
	}
	// балансируем дерево после удаления элемента
	node = skew(node);
	node->right = skew(node->right);
	if (node->right != nullptr)
	{
		node->right->right = skew(node->right->right);
	}
	node = split(node);
	node->right = split(node->right);
	
	return node;
	
}

template <typename T>
bool aaTree<T>::contains(const T& value)// пользовательский метод, вызыввает внутренниий, рекурсивный
{
	bool isFound = contains(root, value);
	return isFound;
}

template <typename T>
bool aaTree<T>::contains(Node* node, const T& value)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->value == value)// нашли искомое значение
	{
		return true;
	}
	else if (value < node->value) {// ищем в леовм поддереве
		return contains(node->left, value);
	}
	else if (value > node->value) {// ищем в правом поддереве
		return contains(node->right, value);
	}
}

template <typename T>
void aaTree<T>::inOrder()// пользовательский метод, вызыввает внутренниий, рекурсивный
{
	inOrder(root);
}

template <typename T>
void aaTree<T>::inOrder(Node* node)// метод для обхода в дереве в порядке левое поддерево - корень - правое поддерево
{
	if (node == nullptr)// null - лист -Ю выходим из рекурсии
	{
		return;
	}

	inOrder(node->left);// идем в левое поддерево, пока не дойдем до базового случая

	std::cout << node->value << " ";// выводим элемент

	inOrder(node->right);// идем вправое поддерево
}

template <typename T>
void aaTree<T>::clear()
{
	//Вызов рекурсивной функции, удаляющей поддеревья
	deleteSubtree(root);
}

template <typename T>
void aaTree<T>::deleteSubtree(Node* node)
{
	if (node != nullptr)
	{
		//Удаление поддерева слева
		deleteSubtree(node->left);
		//Удаление поддерева справа
		deleteSubtree(node->right);

		//Удаление узла
		delete node;

		node = nullptr;
	}
	return;
}
