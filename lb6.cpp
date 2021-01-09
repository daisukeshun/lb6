#include <random>
#include "Matrix.h"

int main()
{
	Matrix a(10);

	for (int i = 0; i < 100; ++i)
	{
		a(i) = rand() % 10;
	}
	a.Identity(0);
	a.Mirror();
	a.Log();

	return 0;
}

