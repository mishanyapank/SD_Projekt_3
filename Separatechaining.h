#ifndef SEPARATECHAINING_H
#define SEPARATECHAINING_H

#include <iostream>
#include <cstdlib> // dla std::rand() i std::srand()
#include <ctime> // dla std::time()
#include <set>
#include <random>
#include <vector>
#include <fstream>
#include <chrono>




using namespace std;
struct BSTNode {
    int key;
    int value;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int k, int v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class Separatechaining {
private:
    int capacity, elements;
    BSTNode** table;

    BSTNode* insertBST(BSTNode* root, int key, int value);
    BSTNode* searchBST(BSTNode* root, int key) const;
    BSTNode* removeBST(BSTNode* root, int key);
    BSTNode* findMin(BSTNode* root) const;
    void inorderTraversal(BSTNode* root, vector<pair<int, int>>& elem) const;
    void clearBST(BSTNode* root);
    void displayBST(BSTNode* root) const;
    void resizetable();
public:
    int r = 0, s = 0;
    Separatechaining(int capacity);
    ~Separatechaining();
    void addrand(int number);
    bool insert(int key, int value);
    bool search(int key, int& value) const;
    bool remove(int key);
    bool exists(int key);
    void display() const;

    void clear();



};

#endif