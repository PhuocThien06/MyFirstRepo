#include <iostream>
using namespace std;
struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};
NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = NULL;
    newNode->p_right = NULL;
    newNode->height = 1; 
    return newNode;
}
int Height(NODE* node) {
    return node ? node->height : 0;
}
int Balance(NODE* node) {
    if (node == nullptr) return 0;
    return Height(node->p_left) - Height(node->p_right);
}
void updateHeight(NODE* node) {
    node->height = 1 + max(Height(node->p_left), Height(node->p_right));
}
NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* z = y->p_left;
    y->p_left = x;
    x->p_right = z;
    updateHeight(x);
    updateHeight(y);
    return y;
}
NODE* rotateRight(NODE* x) {
    NODE* y = x->p_left;
    NODE* z = y->p_right;
    y->p_right = x;
    x->p_left = z;
    updateHeight(x);
    updateHeight(y);
    return y;
}
void Insert(NODE*& pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    }
    else if (x > pRoot->key) {
        Insert(pRoot->p_right, x);
    }
    else {
        return;
    }
    updateHeight(pRoot);
    int balance = Balance(pRoot);
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rotateRight(pRoot);
    else if (balance > -1 && x > pRoot->p_right->key) {
        pRoot = rotateLeft(pRoot);
    }
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balance > -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
NODE* findMin(NODE* pRoot) {
    while (pRoot && pRoot->p_left != NULL)
        pRoot = pRoot->p_left;
    return pRoot;
}
void Remove(NODE*& pRoot, int x) {
    if (pRoot == nullptr) return;
    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        if (pRoot->p_left == NULL || pRoot->p_right == NULL) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            if (temp == NULL) {
                temp = pRoot;
                pRoot = NULL;
            }
            else
                *pRoot = *temp;
            delete temp;
        }
        else {
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
    if (pRoot == nullptr) return;
    updateHeight(pRoot);
    int balance = Balance(pRoot);
    if (balance > 1 && Balance(pRoot->p_left) >= 0)
        pRoot = rotateRight(pRoot);

    else if (balance > 1 && Balance(pRoot->p_left) < 0) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }

    else if (balance < -1 && Balance(pRoot->p_right) <= 0)
        pRoot = rotateLeft(pRoot);

    else if (balance < -1 && Balance(pRoot->p_right) > 0) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}
bool isAVL(NODE* pRoot) {
    if (pRoot == nullptr) {
        return false;
    }
    int balance = Balance(pRoot);
    if (abs(balance) > 1) {
        return false;
    }
    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}


