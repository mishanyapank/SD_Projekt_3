#include "cuckoohash.h"

CuckooHash::CuckooHash(size_t size) : size(size), currentSize(0) {
    table1 = vector<int>(size, -1);
    table2 = vector<int>(size, -1);
}

int CuckooHash::hashFunction1(int key) {
    return key % size;
}

int CuckooHash::hashFunction2(int key) {
    return (key / size) % size;
}

bool CuckooHash::insert(int key, int value) {
    int hash1 = hashFunction1(key);
    int hash2 = hashFunction2(key);

    if (table1[hash1] == -1) {
        table1[hash1] = key;
        return true;
    }

    if (table2[hash2] == -1) {
        table2[hash2] = key;
        return true;
    }

    for (int i = 0; i < size; i++) {
        swap(key, table1[hash1]);
        hash1 = hashFunction2(key);
        if (table2[hash1] == -1) {
            table2[hash1] = key;
            return true;
        }
        swap(key, table2[hash1]);
        hash1 = hashFunction1(key);
    }
    return false;
}

bool CuckooHash::search(int key, int& value) {
    int hash1 = hashFunction1(key);
    int hash2 = hashFunction2(key);

    if (table1[hash1] == key || table2[hash2] == key) {
        value = (table1[hash1] == key) ? table1[hash1] : table2[hash2];
        return true;
    }
    return false;
}

bool CuckooHash::remove(int key) {
    int hash1 = hashFunction1(key);
    int hash2 = hashFunction2(key);

    if (table1[hash1] == key) {
        table1[hash1] = -1;
        return true;
    }

    if (table2[hash2] == key) {
        table2[hash2] = -1;
        return true;
    }
    return false;
}

void CuckooHash::display() {
    cout << "Table 1: \n";
    for (size_t i = 0; i < size; ++i) {
        if (table1[i] != -1) {
            cout << i << ": " << table1[i] << "\n";
        }
    }
    cout << "Table 2: \n";
    for (size_t i = 0; i < size; ++i) {
        if (table2[i] != -1) {
            cout << i << ": " << table2[i] << "\n";
        }
    }
}

void CuckooHash::addToTable(int liczba) {
    set<int> uniqueKeys;
    int randkey;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disKey(100000, 1000000);
    int toremove = (rand() % liczba);
    int tosearch = (rand() % liczba);

    for (int i = 0; i < liczba; i++) {
        do {
            randkey = disKey(gen);
        } while (uniqueKeys.find(randkey) != uniqueKeys.end());
        uniqueKeys.insert(randkey);
        if (toremove == i) {
            r = randkey;
        }
        else if (tosearch == i) {
            s = randkey;
        }
        insert(randkey, randkey);
    }
}

void CuckooHash::clear() {
    table1 = vector<int>(size, -1);
    table2 = vector<int>(size, -1);
    currentSize = 0;
}
