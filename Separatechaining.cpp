#include "Separatechaining.h"

// Konstruktor inicjalizujący tablicę mieszającą
Separatechaining::Separatechaining(int capacity) : capacity(capacity), elements(0) {
    table = new BSTNode * [capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

// Destruktor zwalniający pamięć
Separatechaining::~Separatechaining() {
    for (int i = 0; i < capacity; ++i) {
        clearBST(table[i]);
    }
    delete[] table;
}

// Funkcja pomocnicza do wstawiania do drzewa BST
BSTNode* Separatechaining::insertBST(BSTNode* root, int key, int value) {
    if (root == nullptr) {
        return new BSTNode(key, value);
    }
    if (key < root->key) {
        root->left = insertBST(root->left, key, value);
    }
    else if (key > root->key) {
        root->right = insertBST(root->right, key, value);
    }
    else {
        root->value = value; // Aktualizacja wartości jeśli klucz już istnieje
    }
    return root;
}

// Funkcja pomocnicza do przeglądania drzewa BST w kolejności inorder
void Separatechaining::inorderTraversal(BSTNode* root, vector<pair<int, int>>& elements) const {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->left, elements);
    elements.push_back(make_pair(root->key, root->value));
    inorderTraversal(root->right, elements);
}

// Funkcja do zmiany rozmiaru tablicy
void Separatechaining::resizetable() {
    int oldCapacity = capacity;
    capacity *= 2; // Zwiększenie rozmiaru tablicy
    BSTNode** oldTable = table;

    table = new BSTNode * [capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }

    vector<pair<int, int>> elements;
    for (int i = 0; i < oldCapacity; ++i) {
        inorderTraversal(oldTable[i], elements);
    }

    for (const auto& elem : elements) {
        insert(elem.first, elem.second);
    }

    for (int i = 0; i < oldCapacity; ++i) {
        clearBST(oldTable[i]);
    }
    delete[] oldTable;
}

// Funkcja pomocnicza do wyszukiwania w drzewie BST
BSTNode* Separatechaining::searchBST(BSTNode* root, int key) const {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchBST(root->left, key);
    }
    else {
        return searchBST(root->right, key);
    }
}

// Funkcja pomocnicza do usuwania z drzewa BST
BSTNode* Separatechaining::removeBST(BSTNode* root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->key) {
        root->left = removeBST(root->left, key);
    }
    else if (key > root->key) {
        root->right = removeBST(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }
        BSTNode* temp = findMin(root->right);
        root->key = temp->key;
        root->value = temp->value;
        root->right = removeBST(root->right, temp->key);
    }
    return root;
}

// Funkcja pomocnicza do znajdowania minimalnego elementu w drzewie BST
BSTNode* Separatechaining::findMin(BSTNode* root) const {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Funkcja pomocnicza do czyszczenia drzewa BST
void Separatechaining::clearBST(BSTNode* root) {
    if (root == nullptr) {
        return;
    }
    clearBST(root->left);
    clearBST(root->right);
    delete root;
}

// Funkcja dodająca losowe pary klucz-wartość do tablicy
void Separatechaining::addrand(int number) {
    set<int> uniqueKeys;
    int randkey;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> disKey(100000, 1000000);
    uniform_int_distribution<> disValue(0, number * 2);
    int toremove = (rand() % number);
    int tosearch = (rand() % number);

    for (int i = 0; i < number; i++) {
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

// Funkcja wstawiająca parę klucz-wartość do tablicy
bool Separatechaining::insert(int key, int value) {
    if (elements >= (capacity * 2.5)) { // Zwiększenie rozmiaru tablicy jeśli jest pełna
        resizetable();
    }
    int hash = key % capacity;
    table[hash] = insertBST(table[hash], key, value);
    elements++;
    return true;
}

// Funkcja wyszukująca wartość na podstawie klucza
bool Separatechaining::search(int key, int& value) const {
    int hash = key % capacity;
    BSTNode* node = searchBST(table[hash], key);
    if (node != nullptr) {
        value = node->value;
        return true;
    }
    return false;
}

// Funkcja usuwająca element na podstawie klucza
bool Separatechaining::remove(int key) {
    int hash = key % capacity;
    table[hash] = removeBST(table[hash], key);
    return true;
}

// Funkcja wyświetlająca zawartość tablicy mieszającej
void Separatechaining::display() const {
    for (int i = 0; i < capacity; ++i) {
        cout << "Bucket " << i << ": ";
        displayBST(table[i]);
        cout << endl;
    }
}

// Funkcja sprawdzająca czy element istnieje w tablicy
bool Separatechaining::exists(int key) {
    int hash = key % capacity;
    BSTNode* node = searchBST(table[hash], key);
    if (node != nullptr) {
        return true;
    }
    return false;
}

// Funkcja pomocnicza do wyświetlania drzewa BST
void Separatechaining::displayBST(BSTNode* root) const {
    if (root != nullptr) {
        displayBST(root->left);
        cout << "(" << root->key << ", " << root->value << ") ";
        displayBST(root->right);
    }
}

// Funkcja czyszcząca tablicę
void Separatechaining::clear() {
    for (int i = 0; i < capacity; ++i) {
        clearBST(table[i]);
    }
    delete[] table;
    capacity = 20;
    elements = 0;
    table = new BSTNode * [capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}
