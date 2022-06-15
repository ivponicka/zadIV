#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

fstream plikLog;
char plik1;
char plik2;
long long liczbaBitow1 = 0;
long long liczbaBitow2 = 0;
long long liczbaBitow3 = 0;


void tworzeniePliku(const string name, const int count, const char wartosc, const char wartosc1)   // tworzenie pliku
{
    fstream f;
    f.open(name.c_str(), ios::binary | ios::out);
    for (int i = 0; i < count; i++)
    {
        f.write((char*)&wartosc,1);
    }
    f.close();
}

void zapiszLog(string msg)      // zapisywanie logów
{
    string ss;
    time_t czas = time(NULL);
    string czasLogu = (string)asctime(localtime(&czas));
    czasLogu = czasLogu.substr(0, czasLogu.length() - 1);
    ss = (string)"T: " + czasLogu + " M: " + msg + "\n";
    plikLog << ss.c_str();
    plikLog.flush();
    cout << ss.c_str();
    cout.flush();
}

void otworzLog(string nazwaPliku)    // otwieranie loga
{
    plikLog.open(nazwaPliku.c_str(), ios_base::app);
    if (!plikLog.good() == true)
    {
        cout << "Nie mozna otworzyc pliku" << "log.txt" << endl;
    }
    zapiszLog("Otwarto plik log.txt.");
}

void zamknijLog(void)              // zamykanie loga
{
    zapiszLog("Zamknieto plik log.txt.");
    plikLog.close();
}

uint8_t odlegloscHamminga(uint8_t n1, uint8_t n2)    // porownywanie  bitów
{
    uint8_t x = n1 ^ n2;
    uint8_t bity = 0;
    while (x > 0)
    {
        bity += x & 1;
        x >>= 1;
    }
    return bity;
}

main(int argc, char * argv[])                            // glowny program
{
    otworzLog("log.log");
    zapiszLog("Uruchamianie programu...");

    // TEST 1

    tworzeniePliku("plik1.bin", 01010101, 0x50, 0x55);       // tworzenie plikow (test 1)
    tworzeniePliku("plik2.bin", 01010101, 0x50, 0x55);

    long long BER = 0;
    ifstream plik1("plik1.bin", ios::binary | ios::in);   // wczytywanie plikow (test 1)
    ifstream plik2("plik2.bin", ios::binary | ios::in);
    vector<unsigned char> buffer(istreambuf_iterator<char>(plik1), {});
    vector<unsigned char> buffer2(istreambuf_iterator<char>(plik2), {});

    auto start1 = chrono::high_resolution_clock::now();    // włączenie timera (test 1)

    for (int i = 0; i < 01010101; i++)
    {
      liczbaBitow2 += 8;
      BER += (int)odlegloscHamminga(buffer2[i], buffer[i]);
    }

    plik1.close();
    plik2.close();

    auto koniec1 = chrono::high_resolution_clock::now(); // wyłączenie timera (test 1)
    auto czas = chrono::duration_cast<chrono::milliseconds>(koniec1 - start1); //porównanie czasów (test 1)

    zapiszLog("Liczba sprawdzonych bitow (1 test): " + to_string(liczbaBitow2));
    zapiszLog( "Liczba roznych bitorw (BER) = " + to_string(BER));
    zapiszLog("Czas obliczen: " + to_string(czas.count()) + " ms");
    zapiszLog("-----------------------------");

   // TEST 2

    tworzeniePliku("plik3.bin", 1010101, 0x50, 0x55);    // tworzenie plikow (test 2) 
    tworzeniePliku("plik3.bin", 1010101, 0x0, 0x65);

    long long BER2 = 0;

    ifstream plik3("plik3.bin", ios::binary | ios::in);   // wczytywanie plikow (test 2)
    ifstream plik4("plik3.bin", ios::binary | ios::in);
    vector<unsigned char> buffer3(istreambuf_iterator<char>(plik3), {});
    vector<unsigned char> buffer4(istreambuf_iterator<char>(plik4), {});

    auto start2 = chrono::high_resolution_clock::now();    // włączenie timera (test 2)

    for (int i = 0; i < 1010101; i++)
    {
      liczbaBitow2 += 8;
      BER2 += (int)odlegloscHamminga(buffer4[i], buffer3[i]);
    }

    plik3.close();
    plik4.close();

    auto koniec2 = chrono::high_resolution_clock::now(); // wyłączenie timera (test 2)
    auto czas2 = chrono::duration_cast<chrono::milliseconds>(koniec2 - start2); //porównanie czasów (test 2)

    zapiszLog("Liczba sprawdzonych bitow (2 test): " + to_string(liczbaBitow2));
    zapiszLog( "Liczba roznych bitorw (BER) = " + to_string(BER2));
    zapiszLog("Czas obliczen: " + to_string(czas2.count()) + " ms");
    zapiszLog("-----------------------------");

    // TEST 3

    tworzeniePliku("plik5.bin", 340143400, 0x50, 0x55);    // tworzenie plikow (test 3)
    tworzeniePliku("plik6.bin", 340143400, 0x50, 0x65);
    long long BER3 = 0;

    ifstream plik5("plik5.bin", ios::binary | ios::in);
    ifstream plik6("plik6.bin", ios::binary | ios::in);
    vector<unsigned char> buffer5(istreambuf_iterator<char>(plik5), {});
    vector<unsigned char> buffer6(istreambuf_iterator<char>(plik6), {});

    auto start3 = chrono::high_resolution_clock::now();    // włączenie timera (test 3)

    for (int i = 0; i < 340143400; i++)
    {
      liczbaBitow3 += 8;
      BER3 += (int)odlegloscHamminga(buffer6[i], buffer5[i]);
    }

    plik5.close();
    plik6.close();

    auto koniec3 = chrono::high_resolution_clock::now(); // wyłączenie timera (test 3)
    auto czas3 = chrono::duration_cast<chrono::milliseconds>(koniec3 - start3); //porównanie czasów (test 3)

    zapiszLog("Liczba sprawdzonych bitow (3 test): " + to_string(liczbaBitow3));
    zapiszLog( "Liczba roznych bitorw (BER) = " + to_string(BER3));
    zapiszLog("Czas obliczen: " + to_string(czas3.count()) + " ms");
    zapiszLog("-----------------------------");

    zamknijLog(); // zamkniecie loga
}
