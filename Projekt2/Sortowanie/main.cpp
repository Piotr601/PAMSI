#include "Sortowanie.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctime>

#define N 500000
using namespace std;


    /*
    ==================
	       MAIN
    ==================
    */


int main()
{
    srand(time(NULL));
    double timemerge=0;
    clock_t start, stop;

    int ilosc = 100;

    for (int i = 0; i < ilosc; i++) {

        Stworz();
      //  cout << "Przed: \n";  Wyswietl();

        start = clock();
       // MergeSort(0, N-1);
        QuickSort(0, N);
        stop = clock();
        Sprawdz();
        timemerge += (double_t)(stop - start) / CLOCKS_PER_SEC;
    }

     //cout << "\nPo: \n"; Wyswietl();

    cout << "\n\nSuma: " << timemerge << endl;
    cout << "\nCzas to: " << timemerge/ilosc << endl;

}
