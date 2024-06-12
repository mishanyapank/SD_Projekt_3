#include "cuckoohash.h"

// Konstruktor inicjalizujący tablice mieszające
CuckooHash::CuckooHash(size_t size) : size(size), currentSize(0) {
    table1 = new pair<int, int>[size];
    table2 = new pair<int, int>[size];
    // Inicjalizacja tablic wartościami domyślnymi
    for (size_t i = 0; i < size; ++i) {
        table1[i] = { -1, -1 };
        table2[i] = { -1, -1 };
    }
}

// Destruktor zwalniający pamięć
CuckooHash::~CuckooHash() {
    delete[] table1;
    delete[] table2;
}

// Pierwsza funkcja mieszająca
int CuckooHash::hashFunction1(int key) {
    return key % size;
}

// Druga funkcja mieszająca
int CuckooHash::hashFunction2(int key) {
    return (key / size) % size;
}

// Funkcja do zmiany rozmiaru tablic mieszających
void CuckooHash::resizeTable() {
    int oldSize = size;
    size = static_cast<int>(size * 1.5); // Zwiększenie rozmiaru tablicy o 1.5x
    pair<int, int>* oldTable1 = table1;
    pair<int, int>* oldTable2 = table2;
    table1 = new pair<int, int>[size];
    table2 = new pair<int, int>[size];

    // Inicjalizacja nowych tablic wartościami domyślnymi
    for (size_t i = 0; i < size; ++i) {
        table1[i] = { -1, -1 };
        table2[i] = { -1, -1 };
    }

    currentSize = 0;

    // Przeniesienie istniejących elementów do nowych tablic
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

// Wstawianie pary klucz-wartość do tablicy
bool CuckooHash::insert(int key, int value) {
    if (currentSize >= (size * 0.5)) { // Zwiększenie rozmiaru tablicy jeśli jest pełna
        resizeTable();
    }

    int hash1 = hashFunction1(key); // Obliczenie pierwszego hasha
    int hash2 = hashFunction2(key); // Obliczenie drugiego hasha

    // Przenoszenie elementów w celu wstawienia nowego elementu
    for (int i = 0; i < size; ++i) {
        if (table1[hash1].first == -1) {
            table1[hash1] = { key, value };
            ++currentSize;
            return true;
        } else if (table2[hash2].first == -1) {
            table2[hash2] = { key, value };
            ++currentSize;
            return true;
        } else {
            swap(key, table1[hash1].first);
            swap(value, table1[hash1].second);
            hash1 = hashFunction2(key);
            if (table2[hash1].first == -1) {
                table2[hash1] = { key, value };
                ++currentSize;
                return true;
            }
            swap(key, table2[hash1].first);
            swap(value, table2[hash1].second);
            hash1 = hashFunction1(key);
        }
    }

    resizeTable(); // Zmienianie rozmiaru tablicy w przypadku kolizji
    return insert(key, value);
}

// Szukanie wartości na podstawie klucza
bool CuckooHash::search(int key, int& value) {
    int hash1 = hashFunction1(key); // Obliczenie pierwszego hasha
    int hash2 = hashFunction2(key); // Obliczenie drugiego hasha

    if (table1[hash1].first == key) { // Sprawdzenie w pierwszej tablicy
        value = table1[hash1].second;
        return true;
    }

    if (table2[hash2].first == key) { // Sprawdzenie w drugiej tablicy
        value = table2[hash2].second;
        return true;
    }

    return false; // Element nie został znaleziony
}

// Usuwanie elementu na podstawie klucza
bool CuckooHash::remove(int key) {
    int hash1 = hashFunction1(key); // Obliczenie pierwszego hasha
    int hash2 = hashFunction2(key); // Obliczenie drugiego hasha

    if (table1[hash1].first == key) { // Sprawdzenie w pierwszej tablicy
        table1[hash1] = { -1, -1 };
        --currentSize;
        return true;
    }

    if (table2[hash2].first == key) { // Sprawdzenie w drugiej tablicy
        table2[hash2] = { -1, -1 };
        --currentSize;
        return true;
    }

    return false; // Element nie został znaleziony
}

// Wyświetlanie zawartości tablic mieszających
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

// Dodawanie losowych par klucz-wartość do tablicy
void CuckooHash::addToTable(int liczba) {
    set<int> uniqueKeys; // Zbiór unikalnych kluczy
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

// Czyszczenie tablic mieszających
void CuckooHash::clear() {
    for (size_t i = 0; i < size; ++i) {
        table1[i] = { -1, -1 };
        table2[i] = { -1, -1 };
    }
    currentSize = 0;
}
