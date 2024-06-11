#include "cuckoohash.h"

CuckooHash::CuckooHash(size_t size) : size(size), currentSize(0) {
    table1 = new pair<int, int>[size];
    table2 = new pair<int, int>[size];
    for (size_t i = 0; i < size; ++i) {
        table1[i] = {-1, -1};
        table2[i] = {-1, -1};
    }
}

CuckooHash::~CuckooHash() {
    delete[] table1;
    delete[] table2;
}

int CuckooHash::hashFunction1(int key) {
    return key % size;
}

int CuckooHash::hashFunction2(int key) {
    return (key / size) % size;
}

void CuckooHash::resizeTable() {
    int oldSize = size;
    size *= 2;
    pair<int, int>* oldTable1 = table1;
    pair<int, int>* oldTable2 = table2;
    table1 = new pair<int, int>[size];
    table2 = new pair<int, int>[size];

    for (size_t i = 0; i < size; ++i) {
        table1[i] = {-1, -1};
        table2[i] = {-1, -1};
    }

    currentSize = 0;

    for (size_t i = 0; i < oldSize; ++i) {
        if (oldTable1[i].first != -1) {
            insert(oldTable1[i].first, oldTable1[i].second);
        }
        if (oldTable2[i].first != -1) {
            insert(oldTable2[i].first, oldTable2[i].second);
        }
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

bool CuckooHash::insert(int key, int value) {
    if (currentSize >= (size * 0.7)) {
        resizeTable();
    }

    int hash1 = hashFunction1(key);
    int hash2 = hashFunction2(key);

    for (int i = 0; i < size; ++i) {
        if (table1[hash1].first == -1) {
            table1[hash1] = {key, value};
            ++currentSize;
            return true;
        } else if (table2[hash2].first == -1) {
            table2[hash2] = {key, value};
            ++currentSize;
            return true;
        } else {
            swap(key, table1[hash1].first);
            swap(value, table1[hash1].second);
            hash1 = hashFunction2(key);
            if (table2[hash1].first == -1) {
                table2[hash1] = {key, value};
                ++currentSize;
                return true;
            }
            swap(key, table2[hash1].first);
            swap(value, table2[hash1].second);
            hash1 = hashFunction1(key);
        }
    }

    return false;
}

bool CuckooHash::search(int key, int& value) {
    int hash1 = hashFunction1(key);
    int hash2 = hashFunction2(key);

    if (table1[hash1].first == key) {
        value = table1[hash1].second;
        return true;
    }

    if (table2[hash2].first == key) {
        value = table2[hash2].second;
        return true;
    }

    return false;
}

bool CuckooHash::remove(int key) {
    int hash1 = hashFunction1(key);
    int hash2 = hashFunction2(key);

    if (table1[hash1].first == key) {
        table1[hash1] = {-1, -1};
        --currentSize;
        return true;
    }

    if (table2[hash2].first == key) {
        table2[hash2] = {-1, -1};
        --currentSize;
        return true;
    }

    return false;
}

void CuckooHash::display() {
    cout << "Table 1:\n";
    for (size_t i = 0; i < size; ++i) {
        if (table1[i].first != -1) {
            cout << i << ": (" << table1[i].first << ", " << table1[i].second << ")\n";
        }
    }
    cout << "Table 2:\n";
    for (size_t i = 0; i < size; ++i) {
        if (table2[i].first != -1) {
            cout << i << ": (" << table2[i].first << ", " << table2[i].second << ")\n";
        }
    }
}

void CuckooHash::addToTable(int liczba) {
    set<int> uniqueKeys;
    int randkey;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disKey(100000, 1000000);
    uniform_int_distribution<> disValue(0, liczba * 2);

    int toremove = rand() % liczba;
    int tosearch = rand() % liczba;

    for (int i = 0; i < liczba; ++i) {
        do {
            randkey = disKey(gen);
        } while (uniqueKeys.find(randkey) != uniqueKeys.end());
        uniqueKeys.insert(randkey);
        int randvalue = disValue(gen);
        if (toremove == i) {
            r = randkey;
        } else if (tosearch == i) {
            s = randkey;
        }
        insert(randkey, randvalue);
    }
}

void CuckooHash::clear() {
    for (size_t i = 0; i < size; ++i) {
        table1[i] = {-1, -1};
        table2[i] = {-1, -1};
    }
    currentSize = 0;
}

