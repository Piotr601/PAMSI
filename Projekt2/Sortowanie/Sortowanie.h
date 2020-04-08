#pragma once

/*
	Plik Sortowanie.h

	Plik w którym znajduj¹ siê definicje wszystkie funkcje sortowañ
	wraz z argumentami.

	1) Sortowanie przez scalanie (Merge)
	3) Sortowanie szybkie (Quick)
	2) Sortowanie introspektywne (Introsort)
*/

// -------------------------------
/*
//	---===|| OGOLNE ||===---
*/
// -------------------------------

// Wyswietla tablice
void Wyswietl();

// Tworzy tablice
void Stworz();

// Odwraca tablice
void Odwroc();

// Sprawdza czy sortowanie po obrocie przebieglo prawidlowo
int SprawdzOdwrot();

// Sprawdza czy sortowanie przebieglo prawidlowo
int Sprawdz();

// Oblicza ile % tablicy jest sortowanych
int Procentowe();

// -------------------------------
/*
   ---===||	MERGE SORT ||===---
*/
// -------------------------------

// Algorytm
void Merge(int leftIndex, int middleIndex, int rightIndex);

// Sortowanie przez scalanie
int MergeSort(int leftIndex, int rightIndex);

// -------------------------------
/*
   ---===||	QUICK SORT ||===---
*/
// -------------------------------

//	>>>> V1 <<<<
// Sortowanie szybkie
//int QuickSortv1(int leftIndex, int rightIndex);


//	>>>> V2 <<<<
// Partycjonowanie
int Quickv2(int leftIndex, int rightIndex);
// Sortowanie szybkie
int QuickSortv2(int leftIndex, int rightIndex);


//	>>>> V3 <<<<
// Sortowanie szybkie
void QuickSortv3(int leftIndex, int rightIndex);


// -------------------------------
/*
    ---===|| INTRO SORT ||===---
*/
// -------------------------------


// ||| HEAP ||

//	>>>> V1 <<<<
// void Heap(int begin, int end, int mov);
// void HeapSort(int begin, int end);

//	>>>> V2 <<<<
// Tworzenie kopca
void Heapv2(int*tab, int size, int parentindex);
// Sortowanie przez kopcowanie
void HeapSortv2(int leftIndex, int rightIndex);


//	||| INTRO |||

//  Wstawianie
void Insertion(int leftIndex, int rightIndex);
// Partycjonowanie / dzielenie
int InsertPart(int leftIndex, int rightIndex);

//	||| HYBRID |||

// Sortowanie Intro
void IntroSort(int leftIndex, int rightIndex, int max);
// Wywo³anie funkcji
void HybridSort( int leftIndex, int rightIndex);