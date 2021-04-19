#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class Cache {
		Elem** arr;
		int p;
	public:
		Cache(int s) {
			arr = new Elem*[s]; 
			p = 0;
		}
		~Cache() {
			delete[] arr;
		}
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();	
};

class Node {
public: 
	int key;
	Node* left;
	Node* right;
	int height;
};

int max(int a, int b) {
	return (a > b) ? a : b;
}

int height(Node* N) {
	if (N == NULL) {
		return 0;
	}
	return N->height;
}

Node* newNode(int key) {
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return node;
}

Node* rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	// Rotate
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	return x;
}

Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	// Rotate
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

int getBalance(Node* N) {
	if (N == NULL) {
		return 0;
	}
	return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key) {
	if (node == NULL) {
		return newNode(key);
	}
	if (key < node->key) {
		node->left = insert(node->left, key);	// Insert to the left
	}
	else if (key > node->key) {
		node->right = insert(node->right, key);	// Insert to the right
	}
	else return node;

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key) { // Left left case
		return rightRotate(node);
	}
	if (balance < -1 && key > node->right->key) { // Right right case
		return leftRotate(node);
	}
	if (balance > 1 && key > node->left->key) {	// Left right case
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && key < node->right->key) { // Right left case
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

Node* minValueNode(Node* node) {
	Node* current = node;

	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

Node* deleteNode(Node* root, int key) {
	if (root == NULL) {
		return root;
	}
	if (key < root->key) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->key) {
		root->right = deleteNode(root->right, key);
	}
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = (root->left) ? root->left : root->right;

			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else {
				*root = *temp;
			}
			free(temp);
		}
		else {
			Node* temp = minValueNode(root->right);

			root->key = temp->key;

			root->right = deleteNode(root->right, temp->key);
		}
	}
	if (root == NULL) {
		return root;
	}

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0) { // Left left case
		return rightRotate(root);
	}
	if (balance < -1 && getBalance(root->right) <= 0) { // Right right case
		return leftRotate(root);
	}
	if (balance > 1 && getBalance(root->left) < 0) {	// Left right case
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (balance < -1 && getBalance(root->right) > 0) { // Right left case
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void preOrder(Node* root) {
	if (root != NULL) {
		cout << root->key << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}

void inOrder(Node* root) {
	if (root != NULL) {
		inOrder(root->left);
		cout << root->key << " ";
		inOrder(root->right);
	}
}

#endif