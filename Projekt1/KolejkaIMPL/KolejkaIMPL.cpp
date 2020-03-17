#include "KolejkaIMPL.h"

#include <cstdlib>
#include <iostream>

using namespace std;

class Queue
{
public:
// elementy
	int element;
	Queue* wsk;

// metody
	void push(int z);
	void pop();
	void sfront();
	bool empty();
	void show();
};

// ustawienie wskaznikow poczatka i konca na tab[0] = NULL
Queue* front = NULL;
Queue* back = NULL;


// Dodawanie do kolejki elementow 'z'
void Queue::push(int z)
{
	Queue* ptr = new Queue();	// stworzenie wskaznika na nowy element
	ptr->element = z;			// przypisanie 1 elementu tablicy wartoscia
	ptr->wsk = NULL;			// przypisanie 2 elementu tablicy na NULL

	if (front == NULL)			// Jezeli poczatku nie ma to wskaznik jest jednoczensnie poczatkiem i koncem
	{
		front = ptr;
		back = ptr;
	}
	else						// Jezeli juz istnieje, to poczatek zostaje, a koniec jest wskaznikiem na element koncowy
	{
		back->wsk = ptr;
		back = ptr;
	}
}

// sprawdzanie czy kolejka nie jest pusta
bool Queue::empty() {
	if (front == NULL && back == NULL)
		return 1;
	else
		return 0;
};

// Usuwanie z kolejki elementow
void Queue::pop()
{
	if (Queue::empty())					// czy kolejka jest pusta
		cout << "Kolejka pusta\n";
	else 
	if (front == back)					// jezeli nie to czy tab
	{
		free(front);
		front = back = NULL;
	}
	else
	{									// poczatek jest przypisywany nastepnemu poczatkowi, ktory wskazuje na 2 element
		Queue *ptr = front;
		front = front->wsk;	
		free(ptr);						// wskaznik jest zwalniany, by nie tracic pamieci
	}
}

// sprawdzanie poczatku kolejki
void Queue::sfront()
{
	if (Queue::empty())
		cout << "Kolejka pusta\n";
	else
		cout << "Pierwszy element w kolejce: " << front->element << endl;
}

// sprawdzanie liczby elementow kolejki
void Queue::show()
{
	int a = 0;					// sumator zliczajacy
	Queue* ptr = front;
	while (ptr != NULL)
	{
		a++;
		ptr = ptr->wsk;			// przeskakiwanie po kolejnych tablicach

	}
	cout << "Liczba elementow: " << a << endl;
}


//
// Program glowny
//
int main() {

	cout << "				MENU					\n";		// menu
	cout << "(a) dodawanie elementu do kolejki\n"
		<< "(b) usuwanie elementu z kolejki\n"
		<< "(c) sprawdzanie czy kolejka jest pusta\n"
		<< "(d) wyswietlenie pierwszego elementu w kolejce\n"
		<< "(e) wyswietlenie liczby elementów w kolejce\n\n"
		<< "(f) wyjscie z programu\n\n";

	char x = 0;
	int z;

	Queue q;			// tworzenie nowego obiektu

	while (x != 102)	// warunek na wyjscie z programu ASCII  102 ='f'
	{
		switch (x = getchar())		// instrukcja warunkowa wyboru z menu
		{
			case 'a':
				cout << "Podaj wartosc: ";
				cin >> z;
				q.push(z);
				break;

			case 'b':
				q.pop();
				break;

			case 'c':
				if (q.empty() == 0)
					cout << "Kolejka nie jest pusta\n";
				else
					cout << "Kolejka jest pusta\n";
				break;

			case 'd':
				q.sfront();
				break;

			case 'e':
				q.show();
				break;

		}
	}
}