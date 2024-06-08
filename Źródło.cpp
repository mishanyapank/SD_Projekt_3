#include "Separatechaining.h"
#include "Openchaining.h"

void wyczysc() {
#ifdef _WIN32
    system("cls");    // Dla Windows.
#endif
}
void add_to_file(const string& nazwaPliku, const vector<float>& czasy) {
    ofstream plik(nazwaPliku);

    if (!plik.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku do zapisu." << endl;
        return;
    }
    for (int i = 0; i < czasy.size(); i++) {
        plik << czasy[i] << endl;
    }

    plik.close();

    cout << "Dane zostaly zapisane do pliku czasy.csv" << endl;
}
void firstmenu() {
    cout << "-----------------------------------" << endl;
    cout << "WITAJ! WYBIERZ RODZAJ TABLICY MIESZAJAJACEJ" << endl;
    cout << "-----------------------------------" << endl;
        cout << "1. ADRESOWANIE OTWARTE" << endl;
        cout << "2. ADRESOWANIE ZAMKNIETE Z DRZEWEM ZBALANSOWANYM BST" << endl;
        cout << "3. CUCKOO HASHING" << endl;
        cout << "4. ZAKONCZ" << endl;
        cout << "WYBOR: ";
}
void secondmenu() {
    cout << "PO PROSTU WYBIERZ ROZMIAR SWOJEJ TABLICY!!!" << endl;
    cout << "1. 5000" << endl;
    cout << "2. 8000" << endl;
    cout << "3. 10000" << endl;
    cout << "4. 20000" << endl;
    cout << "5. 40000" << endl;
    cout << "6. 60000" << endl;
    cout << "7. 80000" << endl;
    cout << "8. 100000 (OSTROZNIE!!!)" << endl;
    cout << "WYBOR: ";
}
void thirdmenu() {
    cout << "WYBIERZ RODZAJ OPERACJI" << endl;
    cout << "1. DODAJ ELEMENT" << endl;
    cout << "2. USUN ELEMENT" << endl;
    cout << "3. EXIT" << endl;
    cout << "WYBOR: ";
}


int main() {
    Openchaining openchaining;
    Separatechaining separatechaining(20);
    srand(time(NULL));
    int wybor, wybor2, wybor3, size;
    do {
        firstmenu();
        cin>> wybor;
        if (wybor != 4) {
            wyczysc();
            secondmenu();
            cin >> wybor2;
            switch (wybor2) {
            case 1: size = 5000; break;
            case 2: size = 8000; break;
            case 3: size = 10000; break;
            case 4: size = 20000; break;
            case 5: size = 40000; break;
            case 6: size = 60000; break;
            case 7: size = 80000; break;
            case 8: size = 10000; break;
            }
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> disKey(100000, 1000000);
            uniform_int_distribution<> disValue(0, size * 2);
            switch (wybor) {
            case 1:
                do {
                    thirdmenu();
                    cin >> wybor3;
                    if (wybor3 == 1) {
                        vector <float> czasy;
                        for (int i = 0; i < 50; i++) {
                            openchaining.addToTable(size);
                            auto start = chrono::high_resolution_clock::now();
                            openchaining.insert(disKey(gen), disValue(gen));
                            auto end = chrono::high_resolution_clock::now();
                            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
                            czasy.push_back(duration.count());
                            openchaining.deleteTable();
                        }
                        add_to_file("openinsert.csv", czasy);
                        vector<float>().swap(czasy);
                    }
                    else if (wybor3 == 2) {
                        vector <float> czasy;
                        for (int i = 0; i < 50; i++) {
                            openchaining.addToTable(size);
                            auto start = chrono::high_resolution_clock::now();
                            openchaining.remove(openchaining.r);
                            auto end = chrono::high_resolution_clock::now();
                            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
                            czasy.push_back(duration.count());
                            openchaining.deleteTable();
                        }
                        add_to_file("openremove.csv", czasy);
                        vector<float>().swap(czasy);
                    }
                } while (wybor3 != 3); break;
            case 2:
                do {
                    thirdmenu();
                    cin >> wybor3;
                    if (wybor3 == 1) {
                        vector <float> czasy;
                        for (int i = 0; i < 50; i++) {
                            separatechaining.addrand(size);
                            auto start = chrono::high_resolution_clock::now();
                            separatechaining.insert(disKey(gen), disValue(gen));
                            auto end = chrono::high_resolution_clock::now();
                            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
                            czasy.push_back(duration.count());
                            separatechaining.clear();
                        }
                        add_to_file("separateinsert.csv", czasy);
                        vector<float>().swap(czasy);
                    }
                    if (wybor3 == 2) {
                        vector <float> czasy;
                        for (int i = 0; i < 50; i++) {
                            separatechaining.addrand(size);
                            auto start = chrono::high_resolution_clock::now();
                            separatechaining.remove(separatechaining.r);
                            auto end = chrono::high_resolution_clock::now();
                            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
                            czasy.push_back(duration.count());
                            separatechaining.clear();
                        }
                        add_to_file("separateremove.csv", czasy);
                        vector<float>().swap(czasy);
                    }
                } while (wybor3 != 3);
                break;
            case 3: break;
            }
        }
    } while (wybor != 4);
   

    return 0;
}