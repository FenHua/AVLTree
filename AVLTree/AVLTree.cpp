// AVLTree.cpp : 定义控制台应用程序的入口点。
#include"AVLTree.h"
#include"iostream"
using namespace std;
void testAVLTree()
{
	int array1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	size_t size = sizeof(array1) / sizeof(array1[0]);
	AVLTree<int, int>tree;
	for (size_t i = 0; i < size; i++)
	{
		tree.Insert(array1[i], i);
	}
	tree.InOrder();
	cout << "tree IsBalance ? " << tree.IsBalance() << endl;


	int array2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	size_t len = sizeof(array2) / sizeof(array2[0]);
	AVLTree<int, int> tree2;
	for (size_t i = 0; i<len; ++i)
	{
		tree2.Insert(array2[i], i);
	}
	tree2.InOrder();
	cout << "tree2 IsBalance ? " << tree2.IsBalance() << endl;
}

int main()
{
	testAVLTree();
	system("pause");
	return 0;
}