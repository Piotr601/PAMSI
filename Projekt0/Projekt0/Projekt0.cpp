// Projekt0.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//


#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class Trojkaty
{
public:
	int a;
	int b;
	int c;
	string nazwa;
};

int main()
{

	string sciezka;

	cout << "Podaj sciezke do pliku: ";
	cin >> sciezka;

	Trojkaty Trojkat1;

	cout << "Hello World!" << endl;

	cin >> Trojkat1.a;
}

