#include "Kopiec.h"

#include <iostream>
#define MAX 100
using namespace std;

// klasa
class Heap {
public:
	Heap() { size = 0; };		// konstuktor
	
	int tab[MAX];				// tablica
	int size;					// wielkosc

	void display(int num);
	void sort();
	void del();
	void add(int value);
};

//  @@@@@@@@@@@@@@@@@
//		METODY
//  @@@@@@@@@@@@@@@@@@

void Heap::display(int num)
{
	if (num <= size)
		cout << num << " : " << tab[num] << "\n";
	if (num*2 <= size)
		display(num * 2);
	if (num*2 + 1 <= size)
		display(num * 2 + 1);
};

void Heap::add(int value)
{
	int pom[MAX];					// tablica pomocnicza
	tab[size + 1] = value;
	int p = size + 1;				// zmienna pomocnicza
	while (p != 1) {
		if (tab[p / 2] < tab[p])
		{
			pom[1] = tab[p];
			tab[p] = tab[p / 2];
			tab[p / 2] = pom[1];

			p = p / 2;
		}
		else
			break;
	}
	size++;
};

void Heap::del()
{
	int pom1[MAX];					// tablica pomocnicza
	tab[1] = tab[size];
	size--;

	int pom = 1;

	while (pom * 2 <= size)
	{
		if (tab[pom] < tab[pom * 2] || tab[pom] < tab[pom * 2 + 1])
		{
			if (tab[pom * 2] > tab[pom * 2 + 1] || pom * 2 + 1 > size)
			{
				pom1[1] = tab[pom];
				tab[pom] = tab[pom * 2];
				tab[pom / 2] = pom1[1];

				pom = pom * 2;
			}
			else
				pom1[1] = tab[pom];
			tab[pom] = tab[pom * 2 + 1];
			tab[pom / 2] = pom1[1];

			pom = pom * 2 + 1;
		}
		else
			break;
	}
};

void Heap::sort()
{
	for (int j = 0; j <= size; j++)
	{
		cout << tab[1] << " ";
		del();
	}
	cout << tab[1] << "\n";
};


int main()
{
	char x=0;
	Heap h;

	h.add(2);
	h.add(3);
	h.add(4);

	h.display(1);

	cout << "\n";
	h.del();
	h.del();
	h.display(1);

	cout << "\n";
	h.sort();

	h.display(1);

	cin >> x;
	return 0;



}