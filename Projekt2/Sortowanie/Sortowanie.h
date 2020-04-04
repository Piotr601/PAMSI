#pragma once

/*
	Plik Sortowanie.h

	Plik w którym znajduj¹ siê definicje wszystkie funkcje sortowañ
	wraz z argumentami.

	1) Sortowanie przez scalanie (Merge)
	3) Sortowanie szybkie (Quick)
	2) Sortowanie introspektywne (Introsort)
*/

// Funckje ogolne
void Wyswietl();
void Stworz();

int Sprawdz();

// Sortowanie przez scalanie ( Merge )

void Merge(int leftIndex, int middleIndex, int rightIndex);
int MergeSort(int leftIndex, int rightIndex);

