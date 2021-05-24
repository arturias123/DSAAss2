#include "main.h"
#include "Cache.h"

Data* Cache::read(int addr) {
    if (search(root, addr)) {
        return getData(root, addr);
    }
    return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
    Elem* temp = new Elem(addr, cont, true);
    if (q->size < 15) {
        enqueue(q, temp);
        root = insert(root, addr, cont, true);
    }
    else {
        Elem* res = dequeue(q);
        root = deleteNode(root, res->addr);
        enqueue(q, temp);
        root = insert(root, addr, cont, true);
        return res;
    }
    return NULL;
}
Elem* Cache::write(int addr, Data* cont) {
    bool found = false;
	/*for (int i = 0; i < p; i++)
        if (arr[i]->addr == addr) {
            //delete arr[i]->data;
            arr[i]->data = cont;
            arr[i]->sync = false;
            found = true;
            break;
        }*/

    if (search(root, addr)) {
        replace(root, addr, cont);
        for (int i = q->front; i <= q->rear; i++) {
            if (q->array[i]->addr == addr) {
                //free(q->array[i]->data);
                q->array[i]->data = cont;
                q->array[i]->sync = false;
            }
        }
        found = true;
    }
    if (!found) {
      //  arr[p++] = new Elem(addr,cont,false);
        Elem* temp = new Elem(addr, cont, false);
        if (q->size < 15) {
            enqueue(q, temp);
            root = insert(root, addr, cont, false);
        }
        else {
            Elem* res = dequeue(q);
            root = deleteNode(root, res->addr);
            enqueue(q, temp);
            root = insert(root, addr, cont, false);
            return res;
        }
    }
    return NULL;
}
void Cache::print() {
	for (int i = q->front; i <= q->rear; i++)
        q->array[i]->print();
}
void Cache::preOrder() {
    printP(root);
}
void Cache::inOrder() {
    printI(root);
}
void Cache::printI(Node* root) {
    if (root != NULL) {
        printI(root->left);
        root->elem->print();
        printI(root->right);
    }
}
void Cache::printP(Node* root) {
    if (root != NULL) {        
        root->elem->print();
        printP(root->left);
        printP(root->right);
    }
}