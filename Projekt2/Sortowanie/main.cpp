#include "Sortowanie.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

#define N 100
using namespace std;

/*
    Plik main.cpp
    
    Główny program, tutaj pojawią funkcje z pliku Sortowanie.cpp
    i inne funkcje np. liczące czas

*/


int main()
{
    srand(time(NULL));

    Stworz();
    cout << "Przed: \n";
    Wyswietl();

    MergeSort(0, N-1);

    cout << "\n\nPo: \n";
    Wyswietl();
    
}
