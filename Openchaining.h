#ifndef OPENCHAINING_H
#define OPENCHAINING_H

#include <iostream>
#include <cstdlib>
#include <set>
#include <ctime>
#include <random>
#include <vector>

using namespace std;
const int TABLE_SIZE = 10;

class Openchaining {
private:
    struct HashNode {
        int key;
        int value;
        bool occupied;
        HashNode() : key(0), value(0), occupied(false) {}
    };

    HashNode* table;
    int tableSize;
    int hashFunction(int key);
    void resizeTable();

public:
    int currentSize, r, s;
    Openchaining();
    ~Openchaining();
    void addToTable(int rand);
    bool insert(int key, int value);
    bool find(int key, int& value);
    bool remove(int key);
    void display();
    void deleteTable();
};

#endif