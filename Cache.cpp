#include "main.h"
#include "Cache.h"

Data* Cache::read(int addr) {
	for (int i = 0; i < p; i++)
        if (arr[i]->addr == addr)
            return arr[i]->data;
    return NULL;
}
Elem* Cache::put(int addr, Data* cont) {
	arr[p++] = new Elem(addr,cont,true);
    return NULL;
}
Elem* Cache::write(int addr, Data* cont) {
    bool found = false;
	for (int i = 0; i < p; i++)
        if (arr[i]->addr == addr) {
            //delete arr[i]->data;
            arr[i]->data = cont;
            arr[i]->sync = false;
            found = true;
            break;
        }
    if (!found) {
        arr[p++] = new Elem(addr,cont,false);
    }
    return NULL;
}
void Cache::print() {
	for (int i =0; i < p; i++)
        arr[i]->print();
}
void Cache::preOrder() {
	for (int i =0; i < p; i++)
        arr[i]->print();
}
void Cache::inOrder() {
    for (int i =0; i < p; i++)
        arr[i]->print();
}
