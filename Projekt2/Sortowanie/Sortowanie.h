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
	---===|| OGOLNE ||===---
*/
// -------------------------------

void Wyswietl();
void Stworz();
int Sprawdz();
int Procentowe();

// -------------------------------
/*
   ---===||	MERGE SORT ||===---
*/
// -------------------------------

void Merge(int leftIndex, int middleIndex, int rightIndex);
int MergeSort(int leftIndex, int rightIndex);

// -------------------------------
/*
   ---===||	QUICK SORT ||===---
*/
// -------------------------------

//	>>>> V1 <<<<
int QuickSortv1(int leftIndex, int rightIndex);


//	>>>> V2 <<<<
int Quickv2(int leftIndex, int rightIndex);
int QuickSortv2(int leftIndex, int rightIndex);

void QuickSortv3(int leftIndex, int rightIndex);

// -------------------------------
/*
    ---===|| INTRO SORT ||===---
*/
// -------------------------------

/*
	||| HEAP ||
*/

//	>>>> V1 <<<<
void Heap(int begin, int end, int mov);
void HeapSort(int begin, int end);


//	>>>> V2 <<<<
void Heapv2(int*tab, int size, int parentindex);
void HeapSortv2(int leftIndex, int rightIndex);

/*
	||| INTRO |||
*/

//	>>>> V1 <<<<
int InsertPart(int leftIndex, int rightIndex);
void Insertion(int leftIndex, int rightIndex);

int InsertMedian(int leftIndex, int rightIndex);
void IntroSort(int leftIndex, int rightIndex,int max);

void HybridSort( int leftIndex, int rightIndex);

//	>>>> V2 <<<<
void IntroSortv2(int begin, int end, int max);