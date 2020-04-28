#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// STDLIB do quciksorta i sortowania wynikow

struct Krawedz
{
	int Source;
	int Destination;
	int Weight;
};

struct Graph
{
	struct Krawedz* Krawedz;

	int liczba_wierzcholkow;
	int liczba_krawedzi;
};

struct Subset
{
	int Parent;
	int Rank;
};

struct Graph* CreateGraph(int liczba_wierzcholkow, int KrawedzsCoun)
{
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->liczba_wierzcholkow = liczba_wierzcholkow;
	graph->liczba_krawedzi = KrawedzsCoun;
	graph->Krawedz = (struct Krawedz*)malloc(graph->liczba_krawedzi * sizeof(struct Krawedz));

	return graph;
}

int Find(struct Subset subsets[], int i)
{
	if (subsets[i].Parent != i)
		subsets[i].Parent = Find(subsets, subsets[i].Parent);

	return subsets[i].Parent;
}

void Union(struct Subset subsets[], int x, int y)
{
	int xroot = Find(subsets, x);
	int yroot = Find(subsets, y);

	if (subsets[xroot].Rank < subsets[yroot].Rank)
		subsets[xroot].Parent = yroot;
	else if (subsets[xroot].Rank > subsets[yroot].Rank)
		subsets[yroot].Parent = xroot;
	else
	{
		subsets[yroot].Parent = xroot;
		++subsets[xroot].Rank;
	}
}

int CompareKrawedzs(const void* a, const void* b)
{
	struct Krawedz* a1 = (struct Krawedz*)a;
	struct Krawedz* b1 = (struct Krawedz*)b;
	return a1->Weight > b1->Weight;
}
void Print(struct Krawedz* result, int e)
{
	for (int i = 0; i < e; ++i)
		printf("%d -- %d == %d\n", result[i].Source, result[i].Destination, result[i].Weight);
}

void Kruskal(struct Graph* graph)
{
	int liczba_wierzcholkow = graph->liczba_wierzcholkow;
	struct Krawedz* result = (struct Krawedz*)malloc(sizeof(result) * liczba_wierzcholkow);
	int i = 0;
	int e = 0;

	qsort(graph->Krawedz, graph->liczba_krawedzi, sizeof(graph->Krawedz[0]), CompareKrawedzs);

	struct Subset* subsets = (struct Subset*) malloc(liczba_wierzcholkow * sizeof(struct Subset));

	for (int v = 0; v < liczba_wierzcholkow; ++v)
	{
		subsets[v].Parent = v;
		subsets[v].Rank = 0;
	}

	while (e < liczba_wierzcholkow - 1)
	{
		struct Krawedz nextKrawedz = graph->Krawedz[i++];
		int x = Find(subsets, nextKrawedz.Source);
		int y = Find(subsets, nextKrawedz.Destination);

		if (x != y)
		{
			result[e++] = nextKrawedz;
			Union(subsets, x, y);
		}
	}

	Print(result, e);
}


int main()
{

	int liczba_wierzcholkow = 4;
	int liczba_krawedzi = 5;
	struct Graph* graph = CreateGraph(liczba_wierzcholkow, liczba_krawedzi);

	// Krawedz 0-1
	graph->Krawedz[0].Source = 0;
	graph->Krawedz[0].Destination = 1;
	graph->Krawedz[0].Weight = 10;

	// Krawedz 0-2
	graph->Krawedz[1].Source = 0;
	graph->Krawedz[1].Destination = 2;
	graph->Krawedz[1].Weight = 6;

	// Krawedz 0-3
	graph->Krawedz[2].Source = 0;
	graph->Krawedz[2].Destination = 3;
	graph->Krawedz[2].Weight = 5;

	// Krawedz 1-3
	graph->Krawedz[3].Source = 1;
	graph->Krawedz[3].Destination = 3;
	graph->Krawedz[3].Weight = 15;

	// Krawedz 2-3
	graph->Krawedz[4].Source = 2;
	graph->Krawedz[4].Destination = 3;
	graph->Krawedz[4].Weight = 4;

	Kruskal(graph);

}