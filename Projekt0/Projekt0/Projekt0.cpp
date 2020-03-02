// Projekt0.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//



#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


#define DL_TAB 10

using namespace std;

	//
	//	Klasa Trojkaty
	//	
	//	Parametry:
	//	a - pierwszy bok , b - drugi bok , c - trzeci bok, nazwa[DL_TAB] - nazwa trojkata, obw[DL_TAB] - obwod trojkata
	//

class Trojkaty
{
public:
	int a;
	int b;
	int c;
	string nazwa[DL_TAB];

	int obw[DL_TAB];
};


	//
	// Glowny program
	//

int main()
{
	int i;
	int j = 0;

	string linia;											// Obsluga wczytywania pliku 
	fstream plik;

	string sciezka;											// Wczytywanie pliku V1

	Trojkaty Troj;											// Tworzenie nowego obiektu

	cout << " Podaj nazwe pliku: ";
	cin >> sciezka;
	cout << "\n";


	cout << " Dane z pliku: \n\n";

	//
	// Wczytywanie pliku tekstowego
	//

	plik.open(sciezka, ios::in);																				// * otwarcie pliku
	if (plik.good() == true)																					// Sprawdzanie czy plik nie jest pusty
	{
		while (!plik.eof())																						// dopoki nie zakonczy sie plik
		{
			plik >> Troj.nazwa[j] >> Troj.a >> Troj.b >> Troj.c;												// Wczytywanie danych z pliku
			cout << ' ' << Troj.nazwa[j] << " " << Troj.a << " " << Troj.b << " " << Troj.c << endl;			// Wypisywanie danych z pliku


			Troj.obw[j] = Troj.a + Troj.b + Troj.c;																// Obliczanie obwodu trojkata
			j = j + 1;																							// j - zmianna pomocnicza
			
		}
		plik.close();																							// * zamknięcie pliku
	}


	//
	// Wypisywanie posortowanej tablicy
	//

	cout << endl << " Dane zliczone: \n" << endl;

	for (i = 0; i <= (j-1); i++)
	{
		cout << " " << Troj.nazwa[i] << " obwod:  " << Troj.obw[i] << endl;
	}
	
	return(0);
}

