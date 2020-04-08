#include "Sortowanie.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

#include <time.h>
#include <ctime>

using namespace std;

// zmienne globalne
extern const int N;             // wielkosc tablicy
extern const int percent;       // procent posortowania tablicy
extern const int ilosc;         /// zmienna okreslajaca ile razy ma wykonac petla [FOR]

/*
 ==================
        MAIN
 ==================
 */

int main()
{
   std::fstream plik;

   // losowosc tablicy
   srand(time(NULL));

   // mierzenie czasu
   double tm=0, tq=0, tq2=0, ti = 0;
   time_t start, stop;

   // Procentowa wartosc tablicy
    int K = Procentowe() - 1;

    for (int i = 0; i < ilosc; i++) {
    
      // MergeSort
        Stworz();
            //MergeSort(0, K);
            //Odwroc();
            //SprawdzOdwrot();

        start = clock();
        MergeSort(0, K);
        stop = clock();
        Sprawdz();
        //Wyswietl();
        tm += (double_t)(stop - start) / CLOCKS_PER_SEC;
      

       
      // QuickSort
        Stworz();
           //MergeSort(0, K);
           //Odwroc();
           //SprawdzOdwrot();

        start = clock();    
        QuickSortv2(0, K);
        stop = clock();
        Sprawdz();
        //Wyswietl();
        tq += (double_t)(stop - start) / CLOCKS_PER_SEC;
        

        
      // QuickSortv2
        Stworz();
            //MergeSort(0, K);
            //Odwroc();
            //SprawdzOdwrot();

        start = clock();
        QuickSortv3(0, K);
        stop = clock();
        Sprawdz();
        //Wyswietl();
        tq2 += (double_t)(stop - start) / CLOCKS_PER_SEC;

      // Introsort
        Stworz(); 
            //MergeSort(0, K);
            //Odwroc();
            //SprawdzOdwrot();

        start = clock();
        HybridSort(0,K);
        stop = clock();
        Sprawdz();
        // Wyswietl();
        ti += (double_t)(stop - start) / CLOCKS_PER_SEC;
        
    }

    // wyswietlanie parametrow i czasow
        cout << "Wielkosc tablicy: " << N << "\n";
        cout << "Procent sortowania: " << (float)percent / 10 << "\n\n";
        cout << "Mergesort: " << tm / ilosc << "\n";
        cout << "Quicksort: " << tq / ilosc << "\n";
        cout << "Quicksortv2: " << tq2 / ilosc << "\n";
        cout << "Introsort: " << ti / ilosc << "\n";
  

    // zapis parametrow i czasow do pliku
    // by latwiej mozna bylo skopiowac dane
     plik.open("Sortowanie.txt", std::ios::out);
        if (plik.good() == true) {
            plik << "Wielkosc tablicy: " << N << "\n";
            plik << "Procent sortowania: " << (float)percent / 10 << "\n\n";
            plik << "Mergesort: " << "\n" << tm/ilosc << "\n";
            plik << "Quicksort: " << "\n" << tq/ilosc << "\n";
            plik << "Quicksortv2: "<< "\n" << tq2/ilosc << "\n";
            plik << "Introsort: "<< "\n" << ti/ilosc << "\n";

            plik.close();
        }

}
