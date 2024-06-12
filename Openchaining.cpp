#include "Openchaining.h"

// Konstruktor inicjalizujący tablicę mieszającą
Openchaining::Openchaining() : tableSize(TABLE_SIZE), currentSize(0) {
    table = new HashNode[tableSize];
}

// Destruktor zwalniający pamięć
Openchaining::~Openchaining() {
    delete[] table;
}

// Funkcja mieszająca
int Openchaining::hashFunction(int key) {
    return key % tableSize;
}

// Zmienianie rozmiaru tablicy
void Openchaining::resizeTable() {
    int oldSize = tableSize;
    tableSize *= 2;
    HashNode* oldTable = table;
    table = new HashNode[tableSize];
    currentSize = 0;

    // Przeniesienie istniejących elementów do nowej tablicy
    for (int i = 0; i < oldSize; ++i) {
        if (oldTable[i].occupied) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }

    delete[] oldTable;
}

// Wstawianie pary klucz-wartość do tablicy
bool Openchaining::insert(int key, int value) {
    if (currentSize >= (tableSize * 0.7)) { // Zwiększenie rozmiaru tablicy jeśli jest pełna
        resizeTable();
    }

    int hash = hashFunction(key);
    int originalHash = hash;

    // Wstawianie elementu do tablicy przy użyciu liniowego próbkowania
    while (table[hash].occupied) {
        if (table[hash].key == key) {
            // Aktualizacja istniejącej wartości
            table[hash].value = value;
            return true;
        }
        hash = (hash + 1) % tableSize; // Linear probing
        if (hash == originalHash) {
            // Tablica jest pełna
            return false;
        }
    }

    table[hash].key = key;
    table[hash].value = value;
    table[hash].occupied = true;
    currentSize++;
    return true;
}

// Dodawanie losowych par klucz-wartość do tablicy
void Openchaining::addToTable(int liczba) {
    set<int> uniqueKeys;
    int randkey;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disKey(100000, 1000000);
    uniform_int_distribution<> disValue(0, liczba * 2);
    int toremove = (rand() % liczba);
    int tosearch = (rand() % liczba);

    for (int i = 0; i < liczba; i++) {
        do {
            randkey = disKey(gen);
        } while (uniqueKeys.find(randkey) != uniqueKeys.end());
        uniqueKeys.insert(randkey);
        int randvalue = disValue(gen);
        if (toremove == i) {
            r = randkey;
        }
        else if (tosearch == i) {
            s = randkey;
        }
        insert(randkey, randvalue);
    }
}

// Szukanie wartości na podstawie klucza
bool Openchaining::find(int key, int& value) {
    int hash = hashFunction(key);
    int originalHash = hash;

    // Szukanie elementu przy użyciu liniowego próbkowania
    while (table[hash].occupied) {
        if (table[hash].key == key) {
            value = table[hash].value;
            cout << "znaleziono " << hash << ": (" << table[hash].key << ", " << table[hash].value << ")" << endl;
            return true;
        }
        hash = (hash + 1) % tableSize; // Linear probing
        if (hash == originalHash) {
            // Przeszliśmy przez całą tablicę
            return false;
        }
    }
    return false;
}

// Usuwanie elementu na podstawie klucza
bool Openchaining::remove(int key) {
    int hash = hashFunction(key);
    int originalHash = hash;

    // Usuwanie elementu przy użyciu liniowego próbkowania
    while (table[hash].occupied) {
        if (table[hash].key == key) {
            table[hash].occupied = false;
            currentSize--;
            cout << "usunieto " << hash << ": (" << table[hash].key << ", " << table[hash].value << ")" << endl;
            return true;
        }
        hash = (hash + 1) % tableSize; // Linear probing
        if (hash == originalHash) {
            // Przeszliśmy przez całą tablicę
            return false;
        }
    }
    return false;
}

// Wyświetlanie zawartości tablicy mieszającej
void Openchaining::display() {
    for (int i = 0; i < tableSize; ++i) {
        if (table[i].occupied) {
            cout << i << ": (" << table[i].key << ", " << table[i].value << ")\n";
        }
    }
}

// Usuwanie tablicy i resetowanie jej rozmiaru
void Openchaining::deleteTable() {
    delete[] table;
    table = new HashNode[TABLE_SIZE];
    tableSize = TABLE_SIZE;
    currentSize = 0;
}
