#include "Sortowanie.h"

#include <iostream>
#include <algorithm>
#include <cmath>

extern const int N = 1000000;
/*
	Plik Sortowanie.cpp

	Plik w którym znajd¹ sie wszystkie funkcji wraz z kodem
	które bêd¹ potrzebne do sortowañ

*/

int tab[N];		// glowna tablica
int pom[N];		// tablica pomocnicza

/*
-----------------------------------
	@@@|==================|@@@
			MERGE SORT
	@@@|==================|@@@
-----------------------------------
*/


void Merge(int leftIndex, int middleIndex, int rightIndex)	// laczenie tablic
{
	int p1 = leftIndex;		  // pointer1 - wskazuje na poczatek pierwszej tablicy
	int p2 = middleIndex + 1; // pointer2 - wskazuje na poczatek drugiej tablicy
	int curr = leftIndex;	  // current - indeks, gdzie wpisujemy najmniejszy element


	for (int i = leftIndex; i <= rightIndex; i++) {		// kopiowanie tablicy
		pom[i] = tab[i];
	}

	while (p1 <= middleIndex && p2 <= rightIndex) {	// dopoki nie dojdziemy do konca 1 tab i 2 tab
		if (pom[p1] <= pom[p2]) {			// element 1 podtablicy jest mniejszy
			tab[curr] = pom[p1];			// PDTG* - przepisz do tablicy glownej
			p1++; curr++;					// ZW* - zwiekszanie indeksu
		}
		else {								// element 2 podtablicy jest mniejszy
			tab[curr] = pom[p2];			// PDTG*
			p2++; curr++;					// ZW*
		}
	}

	while (p1 <= middleIndex) {				// dopoki elementy w 1 tablicy sa
		tab[curr] = pom[p1];				// PDTG*
		curr++; p1++;						// ZW*
	}
}

int MergeSort(int leftIndex, int rightIndex)
{
	
	if (leftIndex < rightIndex) {					// dzielimy dopoki nie bedzie jednego elementu
		int middle = (leftIndex + rightIndex) / 2;	// srodek

		MergeSort(leftIndex, middle);				// sortujemy lewa podtablice
		MergeSort(middle + 1, rightIndex);			// sortujemy prawa podtablice

		Merge(leftIndex, middle, rightIndex);		// polaczenie podtablic
	}
	return 0;

	if (rightIndex >= leftIndex) return 1;			// je¿eli jest tylko jeden element, badz mniej
}

/*
-----------------------------------
	@@@|==================|@@@
			QUICK SORT
	@@@|==================|@@@
-----------------------------------
*/


// Quick v2 do sprawdzenia

int Quickv2(int leftIndex, int rightIndex) 
{
	// Dzielenie
	int pivot = tab[rightIndex];
	int i = leftIndex - 1;

	for (int j = leftIndex; j <= rightIndex; j++)
	{
		if (tab[j] < pivot)
		{
			i++;
			std::swap(tab[i], tab[j]);
		}
	}
	std::swap(tab[i + 1], tab[rightIndex]);
	return (i+1);
}
	
int QuickSortv2(int leftIndex, int rightIndex)
{
	// Wywo³anie
	if (leftIndex < rightIndex) {
		int q = Quickv2(leftIndex, rightIndex);
		QuickSortv2(leftIndex, q - 1);
		QuickSortv2(q + 1, rightIndex);
	}
	return 0;

}

//	Quick v1
int QuickSortv1(int leftIndex, int rightIndex)
{
	// Dzielenie

	int pivot = tab[rightIndex];	// element wybrany, ktory bedzie porownywany

	int border = leftIndex-1;		// granica, ktora stoi przed indeksem w danym problemie, bedzie dzielila na inne podroblemy
	int counter = leftIndex;		// umozliwia przemieszczanie sie po tablicy w lewo -- i prawo ++

	while (counter < rightIndex) { 	// dopoki nie bedzie konca tablicy
		if (tab[counter] < pivot) {		// jezeli element pod danym indeksem jest wiekszy od pivota
			border++;						// przesuwamy granice
			if (border != counter) {			// jezeli granica jest rozna od obecnego elementu
				std::swap(tab[border],tab[counter]);	// zamieniamy wartosci
			}
		}
		counter++;					// zwiekszanie licznika
	}
	border++;						// zwiekszanie granicy

	if (border != rightIndex) {		// jezeli granica jest rozna /rowna/ od indeksu prawego

		std::swap(tab[border],tab[rightIndex]);	// zamieniamy elementy
	}


	// Wywo³anie
	if (leftIndex <= rightIndex) {				// dopoki nie ma konca
		QuickSortv1(leftIndex, border - 1);	    // wywolujemy quicksorty dla podzielonych danych jednoczesnie
		QuickSortv1(border + 1, rightIndex);		// nie uwzglêdniaj¹c pivota ( bo jest juz posortowany )
	}
	return 0;

}


// najszybszy quicksort
void QuickSortv3(int leftIndex, int rightIndex) {

	if (rightIndex <= leftIndex)
		return;

	int i = leftIndex - 1;
	int j = rightIndex + 1;

	int pivot = tab[(leftIndex + rightIndex) / 2];

	while (true) {
		while (pivot < tab[--j]);
		while (pivot > tab[++i]);

		if (i <= j) {
			std::swap(tab[i], tab[j]);
		}
		else
			break;
	}

	if ( j > leftIndex )
		QuickSortv3(leftIndex, j);

	if( i < rightIndex )
		QuickSortv3(i, rightIndex);

}

/*
======================
		 HEAP
======================
*/

/* ====================
		   V1
   ===================*/
void Heap(int begin, int end, int mov)		// tablica, poczatek, koniec, przesuniecie
{
	int j = begin;					// przechowuje korzen
	int left = 2 * j + 1 - mov;		// index lewego dziecka, mov cofa polozenie 
	int right = 2 * j + 2 - mov;	// index prawego dziecka


	if (left <= end) {				// czy lewe dziecko miesci sie w kopcu / ma poprawny index 
		if (tab[left] > tab[j]){	// jezeli wartosc tablicy dziecka jest wieksza od obecnej wartosci maksymalnej
			j = left;				// zamiana
		}
	}


	if (right <= end) {				// czy prawe dziecko miesci sie w kopcu / ma poprawny index 
		if (tab[right] > tab[j]) {	// jezeli wartosc tablicy dziecka jest wieksza od obecnej wartosci maksymalnej
			j = right;				// zamiana
		}
	}

	if (j != begin) {				   // gdy wezel to nie korzen / jesli indeks maksymalny jest rozny od indeksu rodzica 
		std::swap(tab[begin], tab[j]); // zamiana indeksow

		Heap(j, end, j);			// czy rodzic jest w odpowiedniej pozycji po zamianie?
	}


}

void HeapSort(int begin, int end)
{
	// budowanie kopca
	int elements = (end - begin);	// liczba elementow
	
	for (int i = (elements / 2) + begin; i >= begin; i--) { // przejscie calej tablicy
		Heap(i, end, begin);	// wywolanie rekurencji, przywrocenie kopca
	}

	// sortowanie
	for (int i = end; i > begin; i--) {  // Od ostatniego elementu do poczatku
		std::swap(tab[begin], tab[i]);   // Zamiana korzenia z ostatnim elementem (maksymalny)
		--end;							 // zmniejszanie rozmiaru kopca
		Heap(begin, end, begin);
	}
}

/* ====================
	       V2
   ===================*/

void Heapv2(int* tab,int size, int parentindex)
{
	int index_max = parentindex;		// index maksymalnego elementu
	int left = 2 * parentindex + 1;		// index lewego dziecka
	int right = 2 * parentindex + 2;	// index prawego dziecka


	if ((left < size) && (tab[left] > tab[index_max])) {	// czy lewe dziecko miesci sie w kopcu / ma poprawny index 
															// jezeli wartosc tablicy dziecka jest wieksza od obecnej wartosci maksymalnej
			index_max = left;								// zamiana
	}
	 
	if ((right < size) && (tab[right] > tab[index_max])) {	 // czy prawe dziecko miesci sie w kopcu / ma poprawny index
															 // jezeli wartosc tablicy dziecka jest wieksza od obecnej wartosci maksymalnej
			index_max = right;								 // zamiana
	}	

	if (index_max != parentindex) {		  // jesli indeks maksymalny jest rozny od indeksu rodzica 
		std::swap(tab[parentindex], tab[index_max]); // zamiana indeksow

		Heapv2(tab ,size , index_max);		// czy rodzic jest w odpowiedniej pozycji po zamianie?
	}
										// sprawdzenie czy nie zostal zaburzony kopiec
}

void HeapSortv2(int leftIndex, int rightIndex){
	++rightIndex;

	int* temp = new int[(rightIndex - leftIndex)];

	for (int i = 0; i < (rightIndex - leftIndex); i++) {
		temp[i] = tab[i + leftIndex];
	}

	for (int i = (rightIndex - leftIndex) / 2 - 1; i >= 0; --i) {
		Heapv2(temp, (rightIndex - leftIndex), i);
	}

	for (int i = (rightIndex - leftIndex) - 1; i >= 0; --i) {
		std::swap(temp[0],temp[i]);
		Heapv2(temp, i, 0);
	}
	for (int i = 0; i < (rightIndex - leftIndex); i++) {
		tab[i + leftIndex] = temp[i];
	}

	delete[] temp;
}

/*=========================
	    INSERTION
==========================*/

/* ====================
		   V1
   ===================*/

void Insertion(int leftIndex, int rightIndex)
{
	rightIndex++;

	int i = leftIndex;
	while(i < rightIndex){
		int j = i;
		while (j > 0 && tab[j - 1] > tab[j]) {
			std::swap(tab[j], tab[j - 1]);
			--j;
		}
		++i;
	}
}

int InsertPart(int leftIndex, int rightIndex)
{
	int pivot = tab[(leftIndex + rightIndex) / 2];

	int i = leftIndex-1;
	int j = rightIndex + 1;

	while(1) {
		do ++i;
		while (tab[i] < pivot);

		do --j;
		while (tab[j] > pivot);

		if (i >= j) return j;

		std::swap(tab[i], tab[j]);
	}
}

void IntroSort(int leftIndex,int rightIndex, int max)
{
	int size = rightIndex - leftIndex + 1;

	if ( size <= 16) {
		Insertion(leftIndex,rightIndex);
	}

	else if (max == 0) {	
		HeapSort(leftIndex,rightIndex);
	}
	else if (leftIndex < rightIndex) {

		int ip = InsertPart(leftIndex, rightIndex);
		IntroSort(leftIndex, ip, --max);
		IntroSort(ip + 1, rightIndex, --max);
	}

}


void HybridSort(int leftIndex, int rightIndex)
{
	int max = (int) log(rightIndex - leftIndex + 1)*2;
	IntroSort(leftIndex, rightIndex, max);

}

/*=========================
            V2
==========================*/

int InsertMedian(int leftIndex, int rightIndex) 
{
	int middleIndex = (leftIndex + rightIndex) / 2;

	if ((tab[leftIndex] < tab[rightIndex] && tab[rightIndex] < tab[middleIndex]) ||
		(tab[middleIndex] <= tab[rightIndex] && tab[rightIndex] <= tab[leftIndex]))
		return(rightIndex);

	if ((tab[leftIndex] < tab[middleIndex] && tab[middleIndex] <= tab[rightIndex]) ||
		(tab[rightIndex] < tab[middleIndex] && tab[middleIndex] <= tab[leftIndex]))
		return(middleIndex);


	if ((tab[middleIndex] <= tab[leftIndex] && tab[leftIndex] < tab[rightIndex]) ||
		(tab[rightIndex] <= tab[leftIndex] && tab[leftIndex] < tab[middleIndex]))
		return(leftIndex);
	
	return 0;
}
void IntroSortv2(int leftIndex, int rightIndex, int max)
{
	if (leftIndex > rightIndex)
		return;

	if (max == 0)
	{
		HeapSort(leftIndex, rightIndex);
		return;
	}

	// Partition
	int b = leftIndex;			// begin - pierwszy element tablicy
	int e = rightIndex;			// end - ostatni element tablicy

	int pivot = InsertMedian(leftIndex, rightIndex);	// pivot - srodkowy element


	if (tab[b] < tab[pivot]) b++;
	if (tab[e] < tab[pivot]) e--;

	std::swap(tab[b++], tab[e++]);

	//std::swap(tab[b++], tab[e++]);

	//Quick(leftIndex,rightIndex);
	IntroSortv2(leftIndex, e - 1, max - 1);
	IntroSortv2(b + 1, rightIndex, max - 1);

}



/*
==================
  Funkcje OGOLNE
==================
*/

// Tworzy losowa tablice
void Stworz()
{
	for ( int i = 0; i < N; i++ ) {
		tab[i] = rand() % N + 1;
	}
}

// Wyswietla tablice po/przed sortowaniem
void Wyswietl()
{
	for ( int i = 0; i < N; i++ ) {
		if ( i % 25 == 0 ) std::cout << '\n';
		std::cout << tab[i] << ' ';
	}
}

// Warunek czy sortowanie dziala dobrze
int Sprawdz()
{
	for ( int i = 0; i < N; i++ ) {
		if ( i != 0 && tab[i] < tab[i - 1] ) {
			std::cout << "\n\n >>>> BLAD W SORTOWANIU <<<< \n";
			return 1;
		}
	}
	return 0;
}

