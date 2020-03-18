#include "ListaIMPL.h"

#include <iostream>

using namespace std;

// Klasa - lista jednokierunkowa
class SinglyLinkedList {
public:
	int element;
	SinglyLinkedList* adress;
};

// wskazniki - poczatku i konca listy
SinglyLinkedList* front = NULL;
SinglyLinkedList* back = NULL;


// =============================================== //
//					   METODY					   //
// =============================================== //


// dodawanie na koncu listy elementu
void backadd(int value) {
	SinglyLinkedList* ptr = new SinglyLinkedList();		// stworzenie wskaznika na nowy element
	ptr->element = value;		// wprowadzenie wartosci do tablicy - value
	ptr->adress = NULL;			// Wskaznik pokazujacy ze to ostatni adres, bo NULL

	if (front == NULL)			// Jezeli poczatku nie ma to wskaznik jest jednoczensnie poczatkiem i koncem
	{
		front = ptr;
		back = ptr;
	}
	else						// Jezeli juz istnieje, to poczatek zostaje, a koniec jest wskaznikiem na element koncowy
	{
		back->adress = ptr;
		back = ptr;
	}
};

// dodawanie na poczatku listy elementu
void frontadd(int value) {
	SinglyLinkedList* ptr = new SinglyLinkedList();		// stworzenie wskaznika na nowy element
	ptr->element = value;		// wprowadzenie wartosci do tablicy - value
	ptr->adress = front;		// wskaznik wskazujacy na adress, ktory bedzie na poczatku, pozwala to tworzyc na poczatku element


	if (front == NULL)			// Jezeli poczatku nie ma to wskaznik jest jednoczensnie poczatkiem i koncem
	{
		front = ptr;
		back = ptr;
	}
	else						// Jezeli juz istnieje, to poczatek zostaje, a koniec jest wskaznikiem na element koncowy
	{
		front = ptr;
	}
};

// sprawdzanie czy lista nie jest pusta
bool empty() {
	if (front == NULL && back == NULL)
		return 1;
	else
		return 0;
};

// Usuwanie z listy elementu na poczatku
void frontdel()
{
	if (empty())						// czy kolejka jest pusta
		cout << "Lista pusta\n";
	else
		if (front == back)				// jezeli nie to czy tab jest pierwszym elementem listy
		{
			free(front);
			front = back = NULL;
		}
		else
		{									// poczatek jest przypisywany nastepnemu poczatkowi, ktory wskazuje na poprzedni element
			SinglyLinkedList* ptr = front;
			front = front->adress;
			free(ptr);						// wskaznik jest zwalniany, by nie tracic pamieci
		}
};

// Usuwanie z listy elementu na koncu
void backdel()
{
	if (empty())						// czy kolejka jest pusta
		cout << "Lista pusta\n";
	else
		if (front == back)				// jezeli nie to czy tab jest pierwszym elementem listy
		{
			free(front);
			front = back = NULL;
		}
		else
		{
			SinglyLinkedList* ptr = front;
			while (ptr->adress->adress != NULL) {			// przekazywanie adresu na tym, ktory nie byl NULL (ostatnim)
				ptr = ptr->adress;							// zmiana adresu
			}
			free(ptr->adress);								// zwalnianie pamieci
			ptr->adress = NULL;							// ustawienie starszego elementu na NULL
			back = ptr;									// przypisanie wskaznika do innego backa

		}
};

// wyswietlanie listy
void display()
{
	if (empty())
		cout << "Lista pusta\n";
	else
	{
		SinglyLinkedList* ptr = front;
		while (ptr != NULL)
		{
			cout << ptr->element << " ";				// wypisywanie elementow
			ptr = ptr->adress;							// przeskakiwanie po elementach
		}
	}

};

// wyswietlenie pierwszego elementu
void frontdisplay()
{
	if (empty())
		cout << "Lista pusta\n";
	else
	{
		cout << " Pierwszy element: ";
		SinglyLinkedList* ptr = front;				// wskaznik - poczatek
		cout << ptr->element << endl;				// wypisanie elementu na ktory wskazuje wskaznik (poczatek)

	}
};

// wyswietlenie ostatniego elementu 
void backdisplay()
{
	if (empty())
		cout << "Lista pusta\n";
	else
	{
		cout << " Ostatni element: ";
		SinglyLinkedList* ptr = back;				// wskaznik - koniec
		cout << ptr->element << endl;				// wypisanie elementu na ktory wskazuje wskaznik (koniec)
	}

};

 //
 //  @@  KLUCZ  @@
 // 

// pomocnicza funkcja do zliczania elementow
int counter()
{
		int a = 1;					// sumator zliczajacy
		SinglyLinkedList* ptr = front;
		while (ptr != NULL)
		{
			a++;
			ptr = ptr->adress;			// przeskakiwanie po kolejnych tablicach

		}
		return a;
};

// PODMIENIA ZAMIAST DODAWAC
void indexadd(int index, int value)
{
	if (index == 0)					// gdy wartosc jest zerem
		frontadd(value);			// dodajemy na poczatek
	else
	if (index >= counter())			// gdy wartosc jest ostatnia
		backadd(value);				// dodajemy na koniec
	else
	{
		SinglyLinkedList* ptr = front;
		SinglyLinkedList* temp;				// pomocnicza klasa

		int i = 0;
		while (ptr->adress != NULL && i < index-1) {
			ptr = ptr->adress;					// wskaznik pokazuje nam adres
			i++;
		}
		temp = ptr->adress;								// tymczasowa / pomocnicza zapamietuje adresy
		ptr->adress = (SinglyLinkedList*)malloc(sizeof(SinglyLinkedList));		// zarezerwowanie pamieci na nowy element
		ptr->adress->element = value;					// zapisujemy elementy dla danego adresu
		ptr->adress->adress=temp;						// przepisuje adresy do wskaznika i glownej klasy
		
	}
};

void indexdel(int index)
{
	if (index == 0)						// podobnie jak wyzej
		frontdel();
	else
	if (index == counter())
		backdel();
	else
	{
		SinglyLinkedList* ptr = front;
		SinglyLinkedList* temp;					// pomocnicza klasa

		int i = 0;
		while (ptr->adress != NULL && i < index - 1) {
			ptr = ptr->adress;					// wskaznik pokazuje nam adres
			i++;
		}

		temp = ptr->adress;						// pomocnicze zapamietanie
		ptr->adress = temp->adress;				// przepisanie adresów
		free(temp);								//zwalnianie pamieci

	}
};

// =============================================== //
//					 OBRAZKI					   //
// =============================================== //

// Nic waznego :)
	void przepraszanko() {
		cout << "         _  /  _       /\n"
			<< "        (o\/--/o)     /\n"
			<< "        ,(/. . )    ,/\n"
			<< "      ,'_/ (Y) )  ,'/\n"
			<< " ___,'_(/ \__ ( ,' /\n"
			<< " \ ,' //\    `-.-./\n"
			<< "  \  (/  `---.__)/)\n"
			<< "   \ /\    \  \ /" << "\n"
			<< "    \__)    )  )__\ " << "\n"
			<< "      (    (  (\n"
			<< "       \    )  )\n"
			<< "        `--^`--^\n";
	}

// Pieseł
/*
▄──────────────▄
────────▌▒█───────────▄▀▒▌
────────▌▒▒▀▄───────▄▀▒▒▒▐
───────▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
─────▄▄▀▒▒▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
───▄▀▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀██▀▒▌
──▐▒▒▒▄▄▄▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄▒▒▌
──▌▒▒▐▄█▀▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
─▐▒▒▒▒▒▒▒▒▒▒▒▌██▀▒▒▒▒▒▒▒▒▀▄▌
─▌▒▀▄██▄▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
─▌▀▐▄█▄█▌▄▒▀▒▒▒▒▒▒░░░░░░▒▒▒▐
▐▒▀▐▀▐▀▒▒▄▄▒▄▒▒▒▒▒░░░░░░▒▒▒▒▌
▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒░░░░░░▒▒▒▐
─▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒▒▒░░░░▒▒▒▒▌
─▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▐
──▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▄▒▒▒▒▌
────▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
───▐▀▒▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀
──▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▀
*/

// =============================================== //
//					 PROGRAM					   //
// =============================================== //

int main() {


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
	przepraszanko();
}