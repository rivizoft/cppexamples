#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node
{
	int data;
	node* right;
	node* left;
};

node* createTree(int data, node* tree)
{
	// продолжение пустое - создаем новый уровень
	if (tree == nullptr)
	{
		tree = new node;
		tree->data = data;
		tree->right = nullptr;
		tree->left = nullptr;
	}
	else
	{
		if (data < tree->data)
			tree->left = createTree(data, tree->left);
		else
			tree->right = createTree(data, tree->right);
	}

	return tree;
}

// вывод, используя инфиксную форму обхода
void sort(node* tree, vector<int>* newArr)
{
	if (tree != nullptr)
	{
		sort(tree->left, newArr);
		newArr->push_back(tree->data);
		sort(tree->right, newArr);
	}
}

int main()
{
	node *tree = 0;
	vector<int> arr = { 5, 1, 5, 35, -90, 150 };

	cout << "INPUT: ";
	for (int i = 0; i < 6; i++)
	{
		cout << arr[i] << " ";
		tree = createTree(arr[i], tree);
	}

	vector<int> sortedArr;
	sort(tree, &sortedArr);

	cout << "\nRESULT: ";
	for (int i = 0; i < 6; i++)
	{
		cout << sortedArr[i] << " ";
	}

	system("pause");
	return 0;
}