#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class BinaryNode { //이진 노드 그자체 의미
	friend class BinarySearchTree;
private:
	int value;
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(int value = 0, BinaryNode* left = nullptr, BinaryNode* right = nullptr)
	{
		this->value = value;
		this->left = left;
		this->right = right;
	}
	BinaryNode* getLeft()
	{
		return this->left;
	}
	BinaryNode* getRight()
	{
		return this->right;
	}
	int getData()
	{
		return this->value;
	}
	bool isleaf() {
		return this->left == nullptr && this->right == nullptr;
	}
	bool hasTwoChildren() {
		return this->left != nullptr && this->right != nullptr;
	}
	bool hasOneChild()
	{
		bool hasonlyleft = this->left != nullptr && this->right == nullptr;
		bool hasonlyright = this->left == nullptr && this->right != nullptr;
		return hasonlyleft || hasonlyright;
	}
};

class Binarytree {
protected:
	BinaryNode* root = nullptr;
	int treesize = 0;
public:
	Binarytree()
	{
		root = nullptr;
	}
	bool empty()
	{
		return this->root == nullptr;
	}
};

class BinarySearchTree :public Binarytree {
private:
	int getheight(BinaryNode* node)
	{
		int hLeft=0;
		int hRight=0;
		if (node->isleaf())
		{
			return 0;
		}
		if (node->hasOneChild())
		{
			if (node->left == nullptr && node->right != nullptr)
			{
				hRight++;
			}
			else if (node->right == nullptr && node->left != nullptr)
			{
				hLeft++;
			}
			return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
		}
		hLeft = getheight(node->getLeft());
		hRight = getheight(node->getRight());

		return (hLeft > hRight) ? hLeft + 1 : hRight + 1;

	}
	BinaryNode* leftmost(BinaryNode* node)
	{
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	void insert(BinaryNode* node, int value) {
		if (value == node->value) {
			node->value = value;
		}
		else if (value < node->value) {
			if (node->left == nullptr) {
				node->left = new BinaryNode(value);
			}
			else {
				insert(node->left, value);
			}
		}
		else {
			if (node->right == nullptr) {
				node->right = new BinaryNode(value);
			}
			else {
				insert(node->right, value);
			}
		}
	}
	BinaryNode* remove(BinaryNode* node, BinaryNode* parent, int value) {
		if (node == nullptr)
		{
			return nullptr;
		}
		if (value < node->value)
		{
			return remove(node->left, node, value);
		}
		else if (value > node->value)
		{
			return remove(node->right, node, value);
		}
		else { // key == node->key
			if (node->hasTwoChildren()) {
				BinaryNode* succ = leftmost(node->right);
				node->value = succ->value;

				succ = this->remove(node->right, node, succ->value);
				return succ;// do something for case 3
			}
			else if (node->hasOneChild()) {
				BinaryNode* child = (node->left != nullptr) ? node->left : node->right;
				if (node == this->root)
				{
					this->root = child;
				}
				else {
					if (parent->left == node)
						parent->left = child;
					else
						parent->right = child;
				}
				return node;// do something for case 2
			}
			else if (node->isleaf()) {
				if (node == this->root)
					this->root = nullptr;
				else {
					if (parent->left == node)
					{
						parent->left = nullptr;
					}
					else
					{
						parent->right = nullptr;
					}
				}
				return node;// do something for case 1
			}
		}
	}
	int IsBalanced(BinaryNode* node)
	{
		int hLeft = getheight(node->getLeft());
		int hRight = getheight(node->getRight());
		return hLeft - hRight;
	}
public:
	void insert(int value)
	{
		if (empty() == true)
		{
			this->root = new BinaryNode(value);
		}
		else {
			insert(this->root, value);
		}
	}
	void remove(int value)
	{
		BinaryNode* node = remove(this->root, nullptr, value);
		if (node == nullptr) {
			cout << "out-of-key" << endl;
		}
		delete node;
	}
	int getheight()
	{
		return (empty()) ? 0 : getheight(root);
	}
	bool isbalanced()
	{
		if (abs(IsBalanced(root)) <= 1)
		{
			return true;
		}
		else {
			return false;
		}
	}
};

int main()
{
	int n;
	cin >> n;
	cin.ignore();

	string line, token;
	vector<string> expr;
	Binarytree tree;
	BinarySearchTree BST;

	for (int i = 0; i < n; i++)
	{
		getline(cin, line);
		stringstream ss(line);

		while (getline(ss, token, ' '))
		{
			expr.push_back(token);
		}
		if (expr[0] == "insert")
		{
			BST.insert(stoi(expr[1]));
		}
		else if (expr[0] == "remove")
		{
			BST.remove(stoi(expr[1]));
		}
		expr.clear();
	}

	if (BST.isbalanced() == true)
	{
		cout << "Balanced" << endl;
	}
	else {
		cout << "Unbalanced" << endl;
	}


	return 0;
}