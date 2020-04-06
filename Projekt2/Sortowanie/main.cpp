#include "Sortowanie.h"

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctime>


extern const int N;

using namespace std;


    /*
    ==================
	       MAIN
    ==================
    */


int main()
{
   srand(time(NULL));
   double timemerge=0, timemerge1=0;
   clock_t start, stop;

    int ilosc = 1;

    for (int i = 0; i < ilosc; i++) {


        Stworz();
        //cout << "\n\nPrzed: \n";  Wyswietl();

        start = clock();
        //MergeSort(0, N-1);
        //QuickSortv1(0, N);

       // HybridSort(0,N-1);
        //QuickSortv3(0, N);
 
        HeapSortv2(0,N);
        //Insertion(0,N);

        stop = clock();
        Sprawdz();
        timemerge += (double_t)(stop - start) / CLOCKS_PER_SEC;

       // cout << "\nPo: \n"; Wyswietl();
       // cout << "\nPo: \n"; Wyswietl();

    /*
        Stworz();
       cout << "Przed: \n";  Wyswietl();
        start = clock();
        //MergeSort(0, N-1);
        QuickSortv1(0, N);
        stop = clock();
        Sprawdz();
        timemerge1 += (double_t)(stop - start) / CLOCKS_PER_SEC;
        @@@@@*/

    }


    //cout << "\n\nSuma: " << timemerge << endl;
    cout << "\nCzas to: " << timemerge/ilosc << endl;
    //cout << "\nCzas to: " << timemerge1 / ilosc << endl;

}
