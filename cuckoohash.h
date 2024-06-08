#ifndef CUCKOOHASH_H
#define CUCKOOHASH_H

#include <iostream>
#include <set>
#include <random>

using namespace std;

class CuckooHash {
private:
    size_t size;
    int* table1;
    int* table2;
    int hashFunction1(int key);
    int hashFunction2(int key);

public:
    int currentSize, r, s;
    CuckooHash(size_t size);
    ~CuckooHash();
    bool insert(int key, int value);
    bool search(int key, int& value);
    bool remove(int key);
    void display();
    void addToTable(int liczba);
    void clear();
};

#endif