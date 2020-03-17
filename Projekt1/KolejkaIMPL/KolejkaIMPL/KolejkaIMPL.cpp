#include "KolejkaIMPL.h"

using namespace std;

class Queue
{
private:
	int size;
	int ptr;
	int counter;
	int * Q;

public:
	Queue(int a);
	~Queue();

	int push(int z);
	int front();
	void pop();
	bool empty();
};