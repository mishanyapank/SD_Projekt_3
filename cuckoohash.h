#ifndef CUCKOOHASH_H
#define CUCKOOHASH_H

#include <iostream>
#include <vector>
#include <functional>
#include <set>
#include <random>

using namespace std;

class CuckooHash {
private:
    size_t size;
    vector<int> table1;
    vector<int> table2;
    int hashFunction1(int key);
    int hashFunction2(int key);

public:
    int currentSize, r, s;
    CuckooHash(size_t size);
    bool insert(int key, int value);
    bool search(int key, int& value);
    bool remove(int key);
    void display();
    void addToTable(int liczba);
    void clear();
};

#endif
