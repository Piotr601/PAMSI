// Projekt0.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//



#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


#define DL_TAB 10						// Maksymalna ilosc trojkatow
#define MAX_DL_SC 450					// Maksymalna dlugosc sciezki

using namespace std;

	//--------------------------------------------------------------//
	//	                     Klasa Trojkaty                       //
	//	                                                            //
	//	    Parametry:                                              //
	//	            a - pierwszy bok                                //
	//              b - drugi bok                                   //
	//              c - trzeci bok                                  //
	//              nazwa[DL_TAB] - nazwa trojkata                  //
	//              obw[DL_TAB] - obwod trojkata                    //
	//--------------------------------------------------------------//

class Trojkaty
{
public:
	int a;
	int b;
	int c;
	string nazwa[DL_TAB];

	int obw[DL_TAB];
};


	/////////////////////////////////////////////////
	//               Glowny program               //
	////////////////////////////////////////////////

int main()
{
	int i;
	int j = 0;

	string linia;											// Obsluga wczytywania pliku 
	fstream plik;
	Trojkaty Troj;											// Tworzenie nowego obiektu


	// Wczytywanie pliku w katalogu po nazwie V1
		
		// string nazwa;		
		// cout << " Podaj nazwe pliku: ";
		// cin >> nazwa;	
		// cout << "\n";

	// Wczytywanie po sciezce V2

	char sciezka[MAX_DL_SC];
	cout << " Podaj sciezke do pliku: ";
	cin.getline(sciezka, MAX_DL_SC);
	

	/////////////////////////////////////////////////
	//         Wczytywanie pliku tekstowego       //
	////////////////////////////////////////////////

	  // V1 

		// plik.open(nazwa, ios::in);																			// * otwarcie pliku	
	
	  // V2

	plik.open(sciezka, ios::in);																				// * otwarcie pliku
	if (plik.good() == false)																					// Sprawdzanie - Plik NIE ISTNIEJE
	{
		cout << "\n Plik nie istnieje!!!" << endl;
		exit(1);	
	}

	if (plik.good() == true)																					// Sprawdzanie - Plik ISTNIEJE 
	{
		cout << " Dane z pliku: \n\n";
		while (!plik.eof())																						// dopoki nie zakonczy sie plik
		{
			plik >> Troj.nazwa[j] >> Troj.a >> Troj.b >> Troj.c;												// Wczytywanie danych z pliku
			cout << ' ' << Troj.nazwa[j] << " " << Troj.a << " " << Troj.b << " " << Troj.c << endl;			// Wypisywanie danych z pliku


			Troj.obw[j] = Troj.a + Troj.b + Troj.c;																// Obliczanie obwodu trojkata
			j = j + 1;																							// j - zmianna pomocnicza
			
		}
		plik.close();																							// * zamknięcie pliku
	}


	/////////////////////////////////////////////////
	//      Wypisywanie posortowanej tablicy       //
	////////////////////////////////////////////////

	cout << endl << " Dane zliczone: \n" << endl;

	for (i = 0; i <= (j-1); i++)
	{
		cout << " " << Troj.nazwa[i] << " obwod:  " << Troj.obw[i] << endl;
	}
	
	return(0);
}

