#include "aaTree.cpp"
#include <iostream>

int main() {
	aaTree<int>* testTree = new aaTree<int>();
	testTree->insert(10);
	testTree->insert(5);
	testTree->insert(2);
	testTree->insert(20);
	testTree->insert(30);
	testTree->insert(140);
	testTree->insert(47);
	testTree->insert(81);
	testTree->insert(3);

	//вывод в отсротированном порядке
	testTree->inOrder();

	//проверка работы contains
	std::cout << "\n" << testTree->contains(10) << "   " << testTree->contains(9999);
	
	//проверка работы удаления элемента
	testTree->remove(140);
	testTree->remove(5);
	testTree->remove(100000);

	std::cout << "\n" << testTree->contains(140) << "   " << testTree->contains(5)<<"\n";

	testTree->inOrder();

	testTree->clear();
	testTree->inOrder();


}