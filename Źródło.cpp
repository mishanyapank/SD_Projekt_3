#include "Separatechaining.h"
#include "Openchaining.h"
#include "cuckoohash.h"

#include <conio.h>

// Funkcja czyszcząca ekran, specyficzna dla systemu Windows
void wyczysc() {
#ifdef _WIN32
    system("cls");    // Dla Windows.
#endif
}

// Funkcja zapisująca czasy operacji do pliku
void add_to_file(const string& nazwaPliku, const vector<float>& czasy) {
    ofstream plik(nazwaPliku);

    // Sprawdzenie czy plik został poprawnie otwarty
    if (!plik.is_open()) {
        cerr << "Nie udało się otworzyć pliku do zapisu." << endl;
        return;
    }

    // Zapisanie czasów do pliku
    for (int i = 0; i < czasy.size(); i++) {
        plik << czasy[i] << endl;
    }

    plik.close();

    cout << "Dane zostały zapisane do pliku " << nazwaPliku << endl;
}

// Funkcja wyświetlająca pierwsze menu wyboru typu tablicy mieszającej
void firstmenu() {
    cout << "-----------------------------------" << endl;
    cout << "WITAJ! WYBIERZ RODZAJ TABLICY MIESZAJĄCEJ" << endl;
    cout << "-----------------------------------" << endl;
    cout << "1. ADRESOWANIE OTWARTE" << endl;
    cout << "2. ADRESOWANIE ZAMKNIĘTE Z DRZEWEM ZBALANSOWANYM BST" << endl;
    cout << "3. CUCKOO HASHING" << endl;
    cout << "4. ZAKOŃCZ" << endl;
    cout << "WYBÓR: ";
}

// Funkcja wyświetlająca drugie menu wyboru rozmiaru tablicy
void secondmenu() {
    cout << "PO PROSTU WYBIERZ ROZMIAR SWOJEJ TABLICY!!!" << endl;
    cout << "1. 5000" << endl;
    cout << "2. 8000" << endl;
    cout << "3. 10000" << endl;
    cout << "4. 20000" << endl;
    cout << "5. 40000" << endl;
    cout << "6. 60000" << endl;
    cout << "7. 80000" << endl;
    cout << "8. 100000 (OSTROŻNIE!!!)" << endl;
    cout << "9. DEMONSTRATOR" << endl;
    cout << "WYBÓR: ";
}

// Funkcja wyświetlająca trzecie menu wyboru operacji
void thirdmenu() {
    cout << "WYBIERZ RODZAJ OPERACJI" << endl;
    cout << "1. DODAJ ELEMENT" << endl;
    cout << "2. USUŃ ELEMENT" << endl;
    cout << "3. WYJDŹ" << endl;
    cout << "WYBÓR: ";
}

int main() {
    Openchaining openchaining;
    Separatechaining separatechaining(20);
    CuckooHash cuckooHash(10); // Zmień rozmiar w razie potrzeby
    srand(time(NULL)); // Inicjalizacja generatora liczb losowych
    int wybor, wybor2, wybor3, size = 0;
    do {
        firstmenu(); // Wyświetlenie pierwszego menu
        cin >> wybor; // Wybór opcji przez użytkownika
        if (wybor != 4) { // Jeśli wybrano opcję inną niż zakończenie programu
            wyczysc(); // Wyczyść ekran
            secondmenu(); // Wyświetl drugie menu
            cin >> wybor2; // Wybór rozmiaru tablicy
            wyczysc(); // Wyczyść ekran

            // Przypisanie rozmiaru tablicy w zależności od wyboru użytkownika
            switch (wybor2) {
            case 1: size = 5000; break;
            case 2: size = 8000; break;
            case 3: size = 10000; break;
            case 4: size = 20000; break;
            case 5: size = 40000; break;
            case 6: size = 60000; break;
            case 7: size = 80000; break;
            case 8: size = 100000; break;
            default: size = 0; break; // Obsłuż nieoczekiwane wejście
            }

            random_device rd; // Urządzenie generujące liczby losowe
            mt19937 gen(rd()); // Generator liczb losowych
            uniform_int_distribution<> disKey(100000, 1000000); // Rozkład losowy dla kluczy
            uniform_int_distribution<> disValue(0, size * 2); // Rozkład losowy dla wartości

            // Wybór rodzaju tablicy mieszającej
            switch (wybor) {
            case 1:
                if (wybor2 == 9) { // Tryb demonstracyjny
                    int demo, demoremove, demokey, demovalue;
                    cout << "PODAJ ILOŚĆ DANYCH: ";
                    cin >> demo;
                    openchaining.addToTable(demo); // Dodaj dane do tablicy
                    openchaining.display(); // Wyświetl tablicę
                    cout << "PODAJ KLUCZ DO USUNIĘCIA: ";
                    cin >> demoremove;
                    cout << "PODAJ KLUCZ I WARTOŚĆ DO DODANIA: ";
                    cin >> demokey >> demovalue;
                    openchaining.remove(demoremove); // Usuń element
                    openchaining.insert(demokey, demovalue); // Dodaj element
                    openchaining.display(); // Wyświetl tablicę
                    openchaining.deleteTable(); // Usuń tablicę
                    _getch(); // Czekaj na naciśnięcie klawisza
                    wyczysc(); // Wyczyść ekran
                }
                else {
                    do {
                        thirdmenu(); // Wyświetl trzecie menu
                        cin >> wybor3; // Wybór operacji
                        wyczysc(); // Wyczyść ekran
                        if (wybor3 == 1) { // Dodaj element
                            vector<float> czasy;
                            for (int i = 0; i < 50; i++) {
                                openchaining.addToTable(size); // Dodaj dane do tablicy
                                auto start = chrono::high_resolution_clock::now(); // Rozpocznij pomiar czasu
                                openchaining.insert(disKey(gen), disValue(gen)); // Wstaw element
                                auto end = chrono::high_resolution_clock::now(); // Zakończ pomiar czasu
                                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start); // Oblicz czas
                                czasy.push_back(duration.count()); // Zapisz czas
                                openchaining.deleteTable(); // Usuń tablicę
                            }
                            add_to_file("openinsert.csv", czasy); // Zapisz czasy do pliku
                            _getch(); // Czekaj na naciśnięcie klawisza
                            wyczysc(); // Wyczyść ekran
                        }
                        else if (wybor3 == 2) { // Usuń element
                            vector<float> czasy;
                            for (int i = 0; i < 50; i++) {
                                openchaining.addToTable(size); // Dodaj dane do tablicy
                                auto start = chrono::high_resolution_clock::now(); // Rozpocznij pomiar czasu
                                openchaining.remove(openchaining.r); // Usuń element
                                auto end = chrono::high_resolution_clock::now(); // Zakończ pomiar czasu
                                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start); // Oblicz czas
                                czasy.push_back(duration.count()); // Zapisz czas
                                openchaining.deleteTable(); // Usuń tablicę
                            }
                            add_to_file("openremove.csv", czasy); // Zapisz czasy do pliku
                            _getch(); // Czekaj na naciśnięcie klawisza
                            wyczysc(); // Wyczyść ekran
                        }
                    } while (wybor3 != 3); // Powtarzaj aż użytkownik wybierze wyjście
                }
                break;

            case 2:
                if (wybor2 == 9) { // Tryb demonstracyjny
                    int demo, demoremove, demokey, demovalue;
                    cout << "PODAJ ILOŚĆ DANYCH: ";
                    cin >> demo;
                    separatechaining.addrand(demo); // Dodaj dane do tablicy
                    separatechaining.display(); // Wyświetl tablicę
                    cout << "PODAJ KLUCZ DO USUNIĘCIA: ";
                    cin >> demoremove;
                    cout << "PODAJ KLUCZ I WARTOŚĆ DO DODANIA: ";
                    cin >> demokey >> demovalue;
                    separatechaining.remove(demoremove); // Usuń element
                    separatechaining.insert(demokey, demovalue); // Dodaj element
                    separatechaining.display(); // Wyświetl tablicę
                    separatechaining.clear(); // Wyczyść tablicę
                    _getch(); // Czekaj na naciśnięcie klawisza
                    wyczysc(); // Wyczyść ekran
                }
                else {
                    do {
                        thirdmenu(); // Wyświetl trzecie menu
                        cin >> wybor3; // Wybór operacji
                        wyczysc(); // Wyczyść ekran
                        if (wybor3 == 1) { // Dodaj element
                            vector<float> czasy;
                            for (int i = 0; i < 50; i++) {
                                separatechaining.addrand(size); // Dodaj dane do tablicy
                                auto start = chrono::high_resolution_clock::now(); // Rozpocznij pomiar czasu
                                separatechaining.insert(disKey(gen), disValue(gen)); // Wstaw element
                                auto end = chrono::high_resolution_clock::now(); // Zakończ pomiar czasu
                                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start); // Oblicz czas
                                czasy.push_back(duration.count()); // Zapisz czas
                                separatechaining.clear(); // Wyczyść tablicę
                            }
                            add_to_file("separateinsert.csv", czasy); // Zapisz czasy do pliku
                            _getch(); // Czekaj na naciśnięcie klawisza
                            wyczysc(); // Wyczyść ekran
                        }
                        else if (wybor3 == 2) { // Usuń element
                            vector<float> czasy;
                            for (int i = 0; i < 50; i++) {
                                separatechaining.addrand(size); // Dodaj dane do tablicy
                                auto start = chrono::high_resolution_clock::now(); // Rozpocznij pomiar czasu
                                separatechaining.remove(separatechaining.r); // Usuń element
                                auto end = chrono::high_resolution_clock::now(); // Zakończ pomiar czasu
                                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start); // Oblicz czas
                                czasy.push_back(duration.count()); // Zapisz czas
                                separatechaining.clear(); // Wyczyść tablicę
                            }
                            add_to_file("separateremove.csv", czasy); // Zapisz czasy do pliku
                            _getch(); // Czekaj na naciśnięcie klawisza
                            wyczysc(); // Wyczyść ekran
                        }
                    } while (wybor3 != 3); // Powtarzaj aż użytkownik wybierze wyjście
                }
                break;

            case 3:
                if (wybor2 == 9) { // Tryb demonstracyjny
                    int demo, demoremove, demokey, demovalue;
                    cout << "PODAJ ILOŚĆ DANYCH: ";
                    cin >> demo;
                    cuckooHash.addToTable(demo); // Dodaj dane do tablicy
                    cuckooHash.display(); // Wyświetl tablicę
                    cout << "PODAJ KLUCZ DO USUNIĘCIA: ";
                    cin >> demoremove;
                    cout << "PODAJ KLUCZ I WARTOŚĆ DO DODANIA: ";
                    cin >> demokey >> demovalue;
                    cuckooHash.remove(demoremove); // Usuń element
                    cuckooHash.insert(demokey, demovalue); // Dodaj element
                    cuckooHash.display(); // Wyświetl tablicę
                    cuckooHash.clear(); // Wyczyść tablicę
                    _getch(); // Czekaj na naciśnięcie klawisza
                    wyczysc(); // Wyczyść ekran
                }
                else {
                    do {
                        thirdmenu(); // Wyświetl trzecie menu
                        cin >> wybor3; // Wybór operacji
                        wyczysc(); // Wyczyść ekran
                        if (wybor3 == 1) { // Dodaj element
                            vector<float> czasy;
                            for (int i = 0; i < 50; i++) {
                                cuckooHash.addToTable(size); // Dodaj dane do tablicy
                                auto start = chrono::high_resolution_clock::now(); // Rozpocznij pomiar czasu
                                cuckooHash.insert(disKey(gen), disValue(gen)); // Wstaw element
                                auto end = chrono::high_resolution_clock::now(); // Zakończ pomiar czasu
                                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start); // Oblicz czas
                                czasy.push_back(duration.count()); // Zapisz czas
                                cuckooHash.clear(); // Wyczyść tablicę
                            }
                            add_to_file("cuckooinsert.csv", czasy); // Zapisz czasy do pliku
                            _getch(); // Czekaj na naciśnięcie klawisza
                            wyczysc(); // Wyczyść ekran
                        }
                        else if (wybor3 == 2) { // Usuń element
                            vector<float> czasy;
                            for (int i = 0; i < 50; i++) {
                                cuckooHash.addToTable(size); // Dodaj dane do tablicy
                                auto start = chrono::high_resolution_clock::now(); // Rozpocznij pomiar czasu
                                cuckooHash.remove(cuckooHash.r); // Usuń element
                                auto end = chrono::high_resolution_clock::now(); // Zakończ pomiar czasu
                                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start); // Oblicz czas
                                czasy.push_back(duration.count()); // Zapisz czas
                                cuckooHash.clear(); // Wyczyść tablicę
                            }
                            add_to_file("cuckooremove.csv", czasy); // Zapisz czasy do pliku
                            _getch(); // Czekaj na naciśnięcie klawisza
                            wyczysc(); // Wyczyść ekran
                        }
                    } while (wybor3 != 3); // Powtarzaj aż użytkownik wybierze wyjście
                }
                break;
            }
        }
    } while (wybor != 4); // Powtarzaj aż użytkownik wybierze zakończenie programu

    return 0;
}
