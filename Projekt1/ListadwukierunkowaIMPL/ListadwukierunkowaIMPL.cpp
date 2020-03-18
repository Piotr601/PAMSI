#include "ListadwukierunkowaIMPL.h"

#include <iostream>

using namespace std;

// Klasa - lista dwukierunkowa
class DoublyLinkedList {
public:
	int element;
	DoublyLinkedList* next_adress;
	DoublyLinkedList* previous_adress;
};

DoublyLinkedList* front = NULL;
DoublyLinkedList* back = NULL;

// =============================================== //
//					   METODY					   //
// =============================================== //

bool empty() {
	if (front == NULL && back == NULL)
		return 1;
	else
		return 0;
};

// dodawanie na poczatku listy elementu
void frontadd(int value) {

	DoublyLinkedList* ptr = new DoublyLinkedList;		// stworzenie wskaznika na liste
	ptr->element = value;								// element
	ptr->next_adress = front;							// adres nastepny =front
	ptr->previous_adress = NULL;						// adres poprzedni = NULL (poczatek)

	if (front == NULL)			// Jezeli poczatku nie ma to wskazniko sa NULLEm
	{
		front = ptr;
		back = ptr;

	}
	else						// Jezeli juz istnieje, to poczatek zostaje, a koniec jest wskaznikiem na element koncowy
	{
		front = ptr;
	}
};
 // dodawanie na koncu listy
void backadd(int value)
{
	DoublyLinkedList* ptr = new DoublyLinkedList;	// skaznik
	ptr->element = value;							// element
	ptr->previous_adress = back;					// adres poprzedni = back
	ptr->next_adress = NULL;						// adres nastepny = NULL (ostatni element listy)

	if (front == NULL)
	{
		front = ptr;
		back = ptr;
	}
	else
	{
		back->next_adress = ptr;		// tworzony jest nowy adres
		back = ptr;
	}

};

// usuwanie na poczatku listy
void frontdel()
{
	if (empty())				// sprawdzanie czy lista jest pusta
		cout << "Lista pusta" << endl;	
	else
	{
		if (front->next_adress == NULL) {	// jezeli poczatek wskazuje na NULL, <=> lista bez elementu
				front = NULL;
			}
		else
		{
			DoublyLinkedList* ptr = front;	// wskaznik pokazuje na poczatek
			front=front->next_adress;		// przypisywanie wskaznika do nastepnego adresu
			free(ptr);						// zwalnianie pamieci
		}
	}
};

// usuwanie na koncu listy
void backdel()
{
	DoublyLinkedList* ptr = front;

	if (empty())								// sprawdzanie czy lista jest pusta
		cout << "Lista pusta" << endl;
	else
	{
		if ((front->next_adress == NULL))	// jezeli poczatek wskazuje na null <=> lista bez elementow
			front = NULL;
		else
		{
			while (ptr->next_adress->next_adress != NULL) {		// szukanie ostatniego elementu
				ptr = ptr->next_adress;							// i zachowanie go jako wskaznik
			}
			free(ptr->next_adress);			// zwalnianie pamieci
			ptr->next_adress = NULL;		// przypisanie do adresu poprzedniego elementu NULLA w polu next adress
			back = ptr;						// skaznik pokazuje na ostatni element
		}
	}
};

// wyswietlanie listy 
void display()
{
	if (empty())						// sprawdzanie czy lista jest pusta
		cout << "Lista jest pusta\n";
	else
	{
		DoublyLinkedList* ptr = front;
		if (ptr != NULL)				// czy wskaznik pokazuje na NULLa -> czy skonczyly sie elementy
		{
			for (; ptr; ptr = ptr->next_adress) {	// znajdowanie kolejnych adresow elementow

			cout << ptr->element << " ";			// wypisywanie ich
			}
			cout << "\n";
		}
	}
};

// wyswietlenie pierwszego elementu
void frontdisplay()
{
	if (empty())						// sprawdzanie czy lista jest pusta
		cout << "Lista pusta\n";
	else
	{
		cout << " Pierwszy element: ";
		DoublyLinkedList* ptr = front;				// wskaznik - poczatek
		cout << ptr->element << endl;				// wypisanie elementu na ktory wskazuje wskaznik (poczatek)

	}

};


// wyswietlenie ostatniego elementu
void backdisplay()
{
	if (empty())						// sprawdzanie czy lista jest pusta
		cout << "Lista pusta\n";
	else
	{
		cout << " Ostatni element: ";
		DoublyLinkedList* ptr = back;				// wskaznik - koniec
		cout << ptr->element << endl;				// wypisanie elementu na ktory wskazuje wskaznik (koniec)
	}

};

/*
/	KLUCZE
*/

// licznik liczacy ile elementow jest na liscie
int counter()
{
	int a = 1;					// sumator zliczajacy
	DoublyLinkedList* ptr = front;
	while (ptr != NULL)
	{
		a++;
		ptr = ptr->next_adress;			// przeskakiwanie po kolejnych tablicach

	}
	return a;
};

// dodawanie elementu do listy z wybranym indeksem
void indexadd(int index, int value)
{
	if (index == 0)					// gdy wartosc jest zerem
		frontadd(value);			// dodajemy na poczatek
	else
	if (index >= counter())			// gdy wartosc jest ostatnia
		backadd(value);				// dodajemy na koniec
	else
	{
		DoublyLinkedList* ptr = front;
		DoublyLinkedList* temp;

		int i = 0;
		while (ptr->next_adress != NULL && i < index - 1) {
			ptr = ptr->next_adress;					// wskaznik pokazuje nam adres
			i++;
		}

		temp = ptr->next_adress;					// tymczasowa zapamietujaca element
		ptr->next_adress = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList)); //zarezerwoanie pamieci na nowy element
		ptr->next_adress->element = value;			// zapisujemy elementy dla danego adresu
		ptr->next_adress->previous_adress = ptr;	// przypisanie adresow do wskaznika
		temp->previous_adress = ptr->next_adress;	// zapamietanie adresow w tablicy pomocniczej
		ptr->next_adress->next_adress = temp;		// Przepisanie adresu do nowej powiekszonej tablicy
	}
};

// usuwanie elementu z listy po wybranym indeksie
void indexdel(int index)
{
	if (index == 0)						// podobnie jak wyzej
		frontdel();
	else
		if (index == counter())
			backdel();
		else
		{
			DoublyLinkedList* ptr = front;
			DoublyLinkedList* temp;					// pomocnicza klasa

			int i = 0;
			while (ptr->next_adress != NULL && i < index - 1) {
				ptr = ptr->next_adress;					// wskaznik pokazuje nam adres
				i++;
			}

			temp = ptr->next_adress;						// pomocnicze zapamietanie
			ptr->next_adress = temp->next_adress;			// przypisanie adresow do wskaznika
			ptr->next_adress->previous_adress = ptr;		// zapamietanie adresow w tablicy pomocniczej
			free(temp);										//zwalnianie pamieci

		}

};


// =============================================== //
//					 PROGRAM					   //
// =============================================== //

int main() 
{


	cout << "				MENU					\n";		// menu
	cout << "(a) sprawdzenie czy lista jest pusta\n" 
		<< "(b) dodanie elementu do listy na poczatek\n"
		<< "(c) dodanie elementu do listy na koniec\n"
		<< "[d] wstawienie elementu do listy po elemencie z zadanym kluczem\n"
		// nalezy pamietac ze indexujemy od 0!
		<< "(e) usuniecie poczatkowego elementu z listy\n"
		<< "(f) usuniecie ostatniego elementu z listy\n"
		<< "[g] usuniecie wybranego elementu(zawierajacego zadany klucz) z listy\n"
		// nalezy pamietac ze indexujemy od 0!
		<< "(h) wyswietlenie zawartosci listy\n"
		<< "(i) wyswietlenie pierwszego elementu\n"
		<< "(j) wyswietlenie ostatniego elementu\n\n"
		<< "<k> wyjscie z programu \n"
		<< " Punkty |d|,|g| Nalezy pamietac ze indeksujemy od 0!\n\n";

	char x = 0;
	int z;
	int index, value;


	while (x != 107)	// warunek na wyjscie z programu ASCII  102 ='f'
	{
		switch (x = getchar())		// instrukcja warunkowa wyboru z menu
		{
		case 'a':
			if (empty() == 0)
				cout << "Lista nie jest pusta\n";
			else
				cout << "Lista jest pusta\n";
			break;

		case 'b':
			cout << "Podaj wartosc: ";
			cin >> z;
			frontadd(z);
			break;

		case 'c':
			cout << "Podaj wartosc: "; 
			cin >> z;
			backadd(z);
			break;

		case 'd':		// nalezy pamietac ze indexujemy od 0!
			cout << "Podaj index: ";
			cin >> index;

			cout << "\nPodaj wartosc: ";
			cin >> value;
			indexadd(index, value);
			break;

		case 'e':
			frontdel();
			break;

		case 'f':	
			backdel();
			break;

		case 'g':		// nalezy pamietac ze indexujemy od 0!
			cout << "Podaj index: ";
			cin >> index;
			indexdel(index);
			break;

		case 'h':	
			display();
			break;

		case 'i':	
			frontdisplay();
			break;

		case 'j':	
			backdisplay();
			break;

		}
	}
}