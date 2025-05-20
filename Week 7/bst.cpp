#include <iostream>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* Search(NODE* pRoot, int x) {
	if (!pRoot) return nullptr;
	if (x < pRoot->key) {
		return Search(pRoot->p_left, x);
	}
	else return Search(pRoot->p_right, x);
}
void Insert(NODE*& pRoot, int x) {
	if (!pRoot) {
		NODE* p = new NODE;
		p->key = x;
		p->p_left = nullptr;
		p->p_right = nullptr;
		return;
	}
	if (x < pRoot->key) {
		Insert(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Insert(pRoot->p_right, x);
	}
}
NODE* findMin(NODE* pRoot) {
	while (pRoot && pRoot->p_left != nullptr) {
		pRoot = pRoot->p_left;
	}
	return pRoot;
}
void Remove(NODE*& pRoot, int x) {
	if (!pRoot)
		return;
	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (pRoot->p_left == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_right;
			delete temp;
		}
		else if (pRoot->p_right == nullptr) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_left;
			delete temp;
		}
		else {
			NODE* minRight = findMin(pRoot);
			pRoot->key = minRight->key;
			Remove(pRoot->p_right, minRight->key);
		}
	}
}
NODE* createTree(int a[], int n) {
	NODE* pRoot = NULL;
	for (int i = 0; i < n; ++i)
		Insert(pRoot, a[i]);
	return pRoot;
}
void removeTree(NODE*& pRoot) {
	if (pRoot == NULL) return;
	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = NULL;
}
int Height(NODE* pRoot) {
	if (!pRoot) return -1;
	int leftHeight = Height(pRoot->p_left);
	int rightHeight = Height(pRoot->p_right);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
int countLess(NODE* pRoot, int x) {
	if (pRoot == NULL) return 0;
	if (pRoot->key < x)
		return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
	else
		return countLess(pRoot->p_left, x);
}
int countGreater(NODE* pRoot, int x) {
	if (pRoot == nullptr) return 0;
	if (pRoot->key > x)
		return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
	else
		return countGreater(pRoot->p_right, x);
}
bool kiemtra(NODE* node,NODE* minNode,NODE* maxNode) {
	if (node == nullptr) return true;
	if (minNode != nullptr && node->key <= minNode->key) return false;
	if (maxNode != nullptr && node->key >= maxNode->key) return false;
	return kiemtra(node->p_left, minNode, node) && kiemtra(node->p_right, node, maxNode);
}
bool isBST(NODE* pRoot) {
	if (!pRoot) return false;
	return kiemtra(pRoot, nullptr, nullptr);
}
bool isFullBST(NODE* pRoot) {
	if (pRoot == nullptr) return false;
	if ((pRoot->p_left == nullptr && pRoot->p_right != nullptr) || (pRoot->p_left != nullptr && pRoot->p_right == nullptr))
		return false;
	return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}