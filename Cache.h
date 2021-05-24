#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class Node {
public:
	Node* left;
	Node* right;
	int height;
	Elem* elem = new Elem(0, 0, false);
	~Node() {
		left = NULL;
		right = NULL;
		delete elem;
	}
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

Node* newNode(int key, Data* cont, bool s) {
	Node* node = new Node();
	node->elem->addr = key;
	node->elem->data = cont;
	node->elem->sync = s;
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

Node* insert(Node* node, int key, Data* cont, bool s) {
	if (node == NULL) {
		return newNode(key, cont, s);
	}
	if (key < node->elem->addr) {
		node->left = insert(node->left, key, cont, s);	// Insert to the left
	}
	else if (key > node->elem->addr) {
		node->right = insert(node->right, key, cont, s);	// Insert to the right
	}
	else return node;

	node->height = 1 + max(height(node->left), height(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->elem->addr) { // Left left case
		return rightRotate(node);
	}
	if (balance < -1 && key > node->right->elem->addr) { // Right right case
		return leftRotate(node);
	}
	if (balance > 1 && key > node->left->elem->addr) {	// Left right case
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && key < node->right->elem->addr) { // Right left case
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void deleteTree(Node* node)
{
	if (node == NULL) return;

	/* first delete both subtrees */
	deleteTree(node->left);
	deleteTree(node->right);

	/* then delete the node */
	delete node;
}

bool search(Node* node, int addr) {
	if (node != NULL) {
		if (node->elem->addr == addr) {
			return true;
		}
		else if (addr < node->elem->addr) {
			return search(node->left, addr);
		}
		else {
			return search(node->right, addr);
		}
	}
	return false;
}

Data* getData(Node* node, int addr) {
	if (node != NULL) {
		if (node->elem->addr == addr) {
			return node->elem->data;
		}
		else if (addr < node->elem->addr) {
			return getData(node->left, addr);
		}
		else {
			return getData(node->right, addr);
		}
	}
	return NULL;
}

void replace(Node* node, int addr, Data* data) {
	if (node != NULL) {
		if (node->elem->addr == addr) {
			free(node->elem->data);
			node->elem->data = data;
			node->elem->sync = false;
		}
		else if (addr < node->elem->addr) {
			replace(node->left, addr, data);
		}
		else {
			replace(node->right, addr, data);
		}
	}
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
	if (key < root->elem->addr) {
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->elem->addr) {
		root->right = deleteNode(root->right, key);
	}
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Node* temp = (root->left) ? root->left : root->right;

			if (temp == NULL) { // No child
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

			root->elem->addr = temp->elem->addr;

			root->right = deleteNode(root->right, temp->elem->addr);
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

void inOrder(Node* root) {
	if (root != NULL) {
		inOrder(root->left);
		cout << root->elem->data << " ";
		inOrder(root->right);
	}
}

class Queue {
public:
	int front, rear, size;
	Elem** array;
	~Queue() {
		for (int i = front; i <= rear; i++) {
			array[i] = NULL;
		}
		delete[] array;
	}
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
Queue* createQueue()
{
	Queue* queue = new Queue();
	queue->front = queue->size = 0;

	// This is important, see the enqueue
	queue->rear = -1;
	queue->array = new Elem * [65536];
	return queue;
}

// Queue is full when size
// becomes equal to the capacity
int isFull(Queue* queue)
{
	return (queue->size == 15);
}

// Queue is empty when size is 0
int isEmpty(Queue* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, Elem* item)
{
	if (isFull(queue))
		return;
	queue->rear = queue->rear + 1;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

// Function to remove an item from queue.
// It changes front and size
Elem* dequeue(Queue* queue)
{
	if (isEmpty(queue))
		return NULL;
	Elem* item = queue->array[queue->front];
	queue->front = (queue->front + 1);
	queue->size = queue->size - 1;
	return item;
}

// Function to get front of queue
Elem* front(Queue* queue)
{
	if (isEmpty(queue))
		return NULL;
	return queue->array[queue->front];
}

// Function to get rear of queue
Elem* rear(Queue* queue)
{
	if (isEmpty(queue))
		return NULL;
	return queue->array[queue->rear];
}

class Cache {
		Queue* q;
		int p;
		Node* root;
	public:
		Cache(int s) {
			q = createQueue(); 
			p = 0;
			root = NULL;
		}
		~Cache() {
			delete q;
			deleteTree(root);
		}
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();	
		void printP(Node* root);
		void printI(Node* root);
};

#endif