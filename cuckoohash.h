#ifndef CUCKOOHASH_H
#define CUCKOOHASH_H

#include <iostream>
#include <set>
#include <random>

using namespace std;

class CuckooHash {
private:
    size_t size; // Rozmiar tablic mieszających
    pair<int, int>* table1; // Pierwsza tablica mieszająca
    pair<int, int>* table2; // Druga tablica mieszająca
    int hashFunction1(int key); // Pierwsza funkcja mieszająca
    int hashFunction2(int key); // Druga funkcja mieszająca
    void resizeTable(); // Funkcja do zmiany rozmiaru tablicy

public:
    int currentSize, r, s; // Aktualny rozmiar tablicy, zmienne pomocnicze do usuwania i szukania
    CuckooHash(size_t size); // Konstruktor
    ~CuckooHash(); // Destruktor
    bool insert(int key, int value); // Funkcja wstawiająca element do tablicy
    bool search(int key, int& value); // Funkcja szukająca elementu w tablicy
    bool remove(int key); // Funkcja usuwająca element z tablicy
    void display(); // Funkcja wyświetlająca zawartość tablicy
    void addToTable(int liczba); // Funkcja dodająca losowe elementy do tablicy
    void clear(); // Funkcja czyszcząca tablicę
};

#endif
