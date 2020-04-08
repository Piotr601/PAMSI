#include "Sortowanie.h"

#include <iostream>
#include <algorithm>
#include <cmath>

/*
	Plik Sortowanie.cpp

	Plik w którym znajd¹ sie wszystkie funkcji wraz z kodem
	które bêd¹ potrzebne do sortowañ

*/


// ZMIENNE GLOBALNE
extern const int ilosc = 50;
extern const int obrot = 0;
extern const int N = 100;
extern const int percent = 1000;

// TABLICE
int tab[N];		// glowna tablica
int pom[N];		// tablica pomocnicza

/*
-----------------------------------
	@@@|==================|@@@
			MERGE SORT
	@@@|==================|@@@
-----------------------------------
*/


// Algorytm 
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

// Sortowanie przez scalanie
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

/*

 //	Quick v1
 int QuickSortv1(int leftIndex, int rightIndex){
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

*/

// Quick v2 
int Quickv2(int leftIndex, int rightIndex) 
{
	// Dzielenie
	int pivot = tab[rightIndex];					// za pivot przyjmujemy ostatni element
	int i = leftIndex - 1;

	for (int j = leftIndex; j <= rightIndex; j++)	// dopoki jest tablica
	{
		if (tab[j] < pivot)							// jezeli ostatni element jest wiekszy od elementu tablicy
		{											// nastepuje inkrementacja i zamiana wartosci
			i++;
			std::swap(tab[i], tab[j]);				// zamiana
		}

	}									
													// po wyjsciu z petli, czyli jezeli tablica sie skonczyla
	std::swap(tab[i + 1], tab[rightIndex]);			// nastepuje zamiana nastepnego elementu z ostatnim
	return (i + 1);									// zwracana jest kolejna wartoœæ
}

int QuickSortv2(int leftIndex, int rightIndex)
{
	// Wywo³anie
	if (leftIndex < rightIndex) {			// jezeli tablica istnieje, to znaczy sa elementy
		int iq = Quickv2(leftIndex, rightIndex); // dzieli tablice 
		QuickSortv2(leftIndex, iq - 1);		// wywolanie dla lewych podtablic
		QuickSortv2(iq + 1, rightIndex);	// wywolanie dla prawych podtablic
	}
	return 0;
}

// Quick v3
void QuickSortv3(int leftIndex, int rightIndex) {

	if (rightIndex <= leftIndex)				// jezeli koniec tablicy
		return;
											// wskazniki
	int i = leftIndex - 1;						// i - zmienna oznaczajaca poczatek - 1 
	int j = rightIndex + 1;						// j - zmienna oznaczajaca koniec +1

	int pivot = tab[(leftIndex + rightIndex) / 2];	// pivot - tutaj jako srodkowa wartosc

	while (true) {							// nieskonczona petla (do break)
		while (pivot < tab[--j]);			// gdy ostatni elementn i schodzaca w dol sa wieksze, to zostaja
		while (pivot > tab[++i]);			// gdy pierwszy i kolejne elmenty sa mniejsze od pivota to zostaja

		if (i <= j) {						// jezeli nie jest to ten sam element, albo wskazniki sie nie mina
			std::swap(tab[i], tab[j]);		// to zamien liczby
		}
		else								// Jezeli sie minely, to wychodzi z petli
			break;
	}

	if ( j > leftIndex )					// jezeli wskaznik jest wiekszy od pierwszego lewego elementu
		QuickSortv3(leftIndex, j);			// sortowanie lewej podtablicy

	if( i < rightIndex )					// jezeli wskaznik jest mniejszy od ostatniego elementu (prawego)
		QuickSortv3(i, rightIndex);			// sortowanie prawej podtablicy

}

/*
-----------------------------------
	@@@|==================|@@@
//			HEAP SORT
	@@@|==================|@@@
-----------------------------------
*/

// >>>> V1 <<<<

/*
 // void Heap(int begin, int end, int mov)	// tablica, poczatek, koniec, przesuniecie
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
*/

// >>>> V2 <<<<
// Tworzenie kopca

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

	if (index_max != parentindex) {			// jesli indeks maksymalny jest rozny od indeksu rodzica 
		std::swap(tab[parentindex], tab[index_max]); // zamiana 

		Heapv2(tab ,size , index_max);		// czy rodzic jest w odpowiedniej pozycji po zamianie?
	}										// sprawdzenie czy nie zostal zaburzony kopiec
										
}


// Sortowanie przez kopcowanie
void HeapSortv2(int leftIndex, int rightIndex){
	++rightIndex;											// zwiekszanie kolejnego miejsca

	int* temp = new int[(rightIndex - leftIndex)];			// tablica dynamiczna -> size/l. elementow

	for (int i = 0; i < (rightIndex - leftIndex); i++) {	// wpisanie do tablicy dynamicznej
		temp[i] = tab[i + leftIndex];						
	}

	for (int i = (rightIndex - leftIndex) / 2 - 1; i >= 0; --i) { // przejscie calej tablicy
		Heapv2(temp, (rightIndex - leftIndex), i);			// wywolanie rekurencji, przywrocenie kopca
	}

	for (int i = (rightIndex - leftIndex) - 1; i >= 0; --i) {	// przejscie 
		std::swap(temp[0],temp[i]);						// Zamiana korzenia z ostatnim elementem (maksymalny)
		Heapv2(temp, i, 0);								// przywrocenie wlasnosci kopca
	}
	for (int i = 0; i < (rightIndex - leftIndex); i++) {	// przepisanie z tablicy dynamicznej
		tab[i + leftIndex] = temp[i];
	}

	delete[] temp;										// usuniecie tablicy dynamicznej
}

/*
-----------------------------------
	@@@|==================|@@@
			INTRO SORT
	@@@|==================|@@@
-----------------------------------
*/

//  Wstawianie
void Insertion(int leftIndex, int rightIndex)
{
	rightIndex++;							// zwiekszenie indeksu

	int i = leftIndex;						// zmienna pomocnicza / poczatek tablicy
	while(i < rightIndex){					// dopoki nie dojdzie do konca tablicy
		int j = i;
		while (j > 0 && tab[j - 1] > tab[j]) {	// dopoki indeks jest wiekszy od 0 i element poprzedni jest wiekszy od nastepnego
			std::swap(tab[j], tab[j - 1]);		// wystepuje zamiana elementow tablic
			--j;
		}
		++i;
	}
}

// Partycjonowanie / dzielenie
int InsertPart(int leftIndex, int rightIndex)
{
	int pivot = tab[(leftIndex + rightIndex) / 2];		// wartosc srodkowa tablicy / pivot
										// wskazniki
	int i = leftIndex-1;					// i - zmienna oznaczajaca poczatek - 1 
	int j = rightIndex + 1;					// // j - zmienna oznaczajaca koniec +1

	while(1) {						// nieskonczona petla
		do ++i;							// zwiekszanie indeksu
		while (tab[i] < pivot);			// dopoki wartosc srednia jest wieksza od lewej wartosci

		do --j;							// zmniejszanie indeksu
		while (tab[j] > pivot);			// dopoki wartosc srednia jest mniejsza od prawej wartosci 

		if (i >= j) return j;		// jezeli ineks lewy jest >= od prawego, to zwracany jest koniec (prawy)

		std::swap(tab[i], tab[j]);		// zamiana elementow tablic
	}
}


/*
-----------------------------------
	@@@|==================|@@@
			HYBRID SORT
	@@@|==================|@@@
-----------------------------------
*/

// Sortowanie Intro
void IntroSort(int leftIndex,int rightIndex, int max)
{
	int size = rightIndex - leftIndex + 1;			// wielkosc tablicy / podtablicy (size)

	if ( size <= 20) {								// jezel wartosc ta bedzie mniejsza niz 20
		Insertion(leftIndex,rightIndex);			// wywolana jest sortowanie inser ( szybka dla malych liczb )
	}

	else if (max == 0) {							// jezeli glebokosc tego sortowania jest rowna 0
		HeapSortv2(leftIndex,rightIndex);			// nastepuje wywolanie sortowanie przez kopcowanie
	}
	else if (leftIndex < rightIndex) {				// jezeli prawy indeks jest wiekszy niz lewo

		int ip = InsertPart(leftIndex, rightIndex);
		IntroSort(leftIndex, ip, --max);			// wywolanie sortowania dla lewej podtablicy
		IntroSort(ip + 1, rightIndex, --max);		// wywolanie sortowanie dla prawej podtablicy
	}

}

// Wywo³anie funkcji
void HybridSort(int leftIndex, int rightIndex)
{
	int max = (int) log(rightIndex - leftIndex + 1)*2;	// 2 log  ... ustalona wartosc, glebokosc
	IntroSort(leftIndex, rightIndex, max);
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

// Oblicza ile procent tablicy jest sortowanych 
int Procentowe() {
	int lperc = (N * percent) / 1000;

	return lperc;
}

// Sprawdza czy tablica zostala posortowana prawidlowo
int Sprawdz()
{
	int lperc = (N * percent) / 1000;

	for ( int i = 0; i < lperc; i++ ) {
		if ( i != 0 && tab[i] < tab[i - 1] ) {
			std::cout << "\n\n >>>> BLAD W SORTOWANIU <<<< \n";
			return 1;
		}
	}
	return 0;
}

// Odwraca tablice
void Odwroc() {

	std::reverse(std::begin(tab), std::end(tab));
}

// Sprawdza czy sortowanie po obrocie przebieglo prawidlowo
int SprawdzOdwrot()
{
	int lperc = (N * percent) / 1000;

	for (int i = 0; i < lperc; i++) {
		if (i != 0 && tab[i] > tab[i - 1]) {
			std::cout << "\n\n >>>> BLAD W ODWRACANIU <<<< \n";
			return 1;
		}
	}
	return 0;
}