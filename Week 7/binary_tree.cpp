#include <iostream>
#include <vector>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* createNode(int data) {
	NODE* p = new NODE;
	p->key = data;
	p->p_left = nullptr;
	p->p_right = nullptr;
	return p;
}
vector<int> NLR(NODE* pRoot) {
	vector<int> result;
	if (pRoot) {
		result.push_back(pRoot->key);
		vector<int> left = NLR(pRoot->p_left);
		vector<int> right = NLR(pRoot->p_right);
		result.insert(result.end(), left.begin(), left.end());
		result.insert(result.end(), right.begin(), right.end());
	}
	return result;
}
vector<int> LNR(NODE* pRoot) {
	vector<int> result;
	if (pRoot) {
		vector<int> left = LNR(pRoot->p_left);
		result.insert(result.end(), left.begin(), left.end());
		result.push_back(pRoot->key);
		vector<int> right = LNR(pRoot->p_right);
		result.insert(result.end(), right.begin(), right.end());
	}
	return result;
}
vector<int> LRN(NODE* pRoot) {
	vector<int> result;
	if (pRoot) {
		vector<int> left = LRN(pRoot->p_left);
		vector<int> right = LRN(pRoot->p_right);
		result.insert(result.end(), left.begin(), left.end());
		result.insert(result.end(), right.begin(), right.end());
		result.push_back(pRoot->key);
	}
	return result;
}
vector <vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> result;
	if (!pRoot) return result;
	const int MAX = 1000;
	NODE* queue[MAX];
	int rear = 0, front = 0;
	queue[rear++] = pRoot;
	while (front < rear) {
		int levelSize = rear - front;
		vector<int> level;
		for (int i = 0;i < levelSize;i++) {
			NODE* node = queue[front++];
			level.push_back(node->key);
			if (node->p_left) queue[rear++] = node->p_left;
			if (node->p_right) queue[rear++] = node->p_right;
		}
		result.push_back(level);
	}
	return result;
}
int countNode(NODE* pRoot) {
	if (!pRoot) return 0;
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
int sumNode(NODE* pRoot) {
	if (!pRoot) return 0;
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}
NODE* findNode(NODE* pRoot, int value) {
	if (!pRoot) return nullptr;
	if (pRoot->key == value) return pRoot;
	NODE* leftResult = findNode(pRoot->p_left, value);
	if (leftResult) return leftResult;
	return findNode(pRoot->p_right, value);
}
int findHeight(NODE* pRoot) {
	if (!pRoot) return -1;
	int leftHeight = findHeight(pRoot->p_left);
	int rightHeight = findHeight(pRoot->p_right);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
int heightNode(NODE* pRoot, int value) {
	NODE* target = findNode(pRoot, value);
	if (!target) return -1;
	return findHeight(target);
}
int findLevel(NODE* pRoot, NODE* p, int& level, int currentLevel) {
	if (!pRoot) return 0;
	if (pRoot->key == p->key) {
		level = currentLevel;
		return 1;
	}
	return findLevel(pRoot->p_left, p, level, currentLevel + 1) | findLevel(pRoot->p_right, p, level, currentLevel + 1);
}
int Level(NODE* pRoot, NODE* p) {
	int level = -1;
	if (!findLevel(pRoot, p, level, 0)) return -1;
}
int countLeaf(NODE* pRoot) {
	if (!pRoot) return 0;
	if (!pRoot->p_left && !pRoot->p_right) return 1;
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
