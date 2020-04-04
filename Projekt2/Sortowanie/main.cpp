#include "Sortowanie.h"

#include <iostream>
#define N 100
using namespace std;

/*
    Plik main.cpp
    
    Główny program, tutaj pojawią funkcje z pliku Sortowanie.cpp
    i inne funkcje np. liczące czas

*/


int main()
{
    Stworz();
    cout << "Przed: \n";
    Wyswietl();

    MergeSort(0, N-1);

    cout << "\n\n Po: \n";
    Wyswietl();
    

}
