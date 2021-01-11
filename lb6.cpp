#include <stdlib.h>
#include <math.h>
#include "Matrix.h"

#define ref(a) 0[a]

const int verticesCount = 15;
const int input[] = {
	0,2,0,0,3,2,0,1,1,0,0,0,0,0,0,2,0,0,0,2,1,0,1,0,0,0,0,0,0,0,0,0,0,2,0,3,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,3,1,2,0,1,0,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,3,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,3,0,1,1,2,0,0,1,0,0,0,0,0,0,3,0,0,0,0,2,0,0,0,0,0,3,0,0,0,0,0,0,3,2,0,0,1,0,0,0,1,0,0,1,1,0,3,0,0,0,2,4,0,0,0,2,0,0,0,1,0,2,0,0,0,1,2,0,0,0,0,0,0,0,2,2,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,0,0,1,4,2,0,0,0
};
const int subgraphCount = 3;
const int subgraphVerticesCount[subgraphCount] = {5, 5, 5};


int deltaS(int pInside, int pOutside, int pxy)
{
	return pInside - pOutside - 2 * pxy;
}

int outsideConnectionBetweenOneGraph(Matrix& base, Matrix* G)
{
	int ret = 0;
	for (int i = 0; i < ref(G).GetColCount(); ++i)
	{
		for (int j = 0; j < base.GetColCount(); j++)
		{
			if(ref(G)(i) != j)
			{ 
				ret += base(ref(G)(i), j);
			}
		}
	}
	return ret;
}

int connectionSumBetweenOneGraphByIndex(Matrix& base, Matrix* G, int index)
{
	int ret = 0;
	for (int i = 0; i < ref(G).GetColCount(); ++i)
	{
		ret += base(index, ref(G)(i));
	}
	return ret;
}

int connectionSumBetweenTwoGraphsByIndex(Matrix& base, Matrix * G1, int x, Matrix * G2, int y)
{
	return connectionSumBetweenOneGraphByIndex(base, G2, ref(G1)(x)) + connectionSumBetweenOneGraphByIndex(base, G1, 0[G2](y));
}

int outsideP(Matrix& base, Matrix * G1, int x, Matrix * G2, int y)
{
	return connectionSumBetweenTwoGraphsByIndex(base, G1, x, G2, y);
}

int insideP(Matrix& base, Matrix * G1, int x, Matrix * G2, int y)
{
	return connectionSumBetweenTwoGraphsByIndex(base, G2, x, G1, y);
}

int betweenP(Matrix& base, Matrix * G1, int x, Matrix * G2, int y)
{
	return base(ref(G1)(x), ref(G2)(y));
}

unsigned long long checkTwoSubgraphs(Matrix& base, Matrix * G1, Matrix * G2)
{
	long x = -1, y = -1;
	int maxDeltaS = INT_MIN, tmpDeltaS;
	for (int i = 0; i < ref(G1).GetColCount(); ++i)
	{
		for (int j = 0; j < ref(G2).GetColCount(); ++j)
		{
			tmpDeltaS = deltaS(
				insideP(base, G1, i, G2, j),
				outsideP(base, G1, i, G2, j),
				betweenP(base, G1, i, G2, j)
			);
			if (maxDeltaS < tmpDeltaS && tmpDeltaS > 0)
			{
				maxDeltaS = tmpDeltaS;
				x = i;
				y = j;
			}
			printf("(%d, %d) %d %d %d : %d\n", 
				0[G1](i), 0[G2](j), 
				insideP(base, G1, i, G2, j),
				outsideP(base, G1, i, G2, j),
				betweenP(base, G1, i, G2, j),
				tmpDeltaS);
		}
	}
	unsigned long long ret = 0;
	ret += x;
	ret *= 16;
	ret += y;
	printf("%d %d\n", ref(G1)(x), ref(G2)(y));
	return ret;
}

int checkInput()
{
	if (sizeof(input) / sizeof(int) != verticesCount * verticesCount) { fprintf(stderr, "Invalid input!\n"); return 1; }
	for (int i = 0; i < verticesCount * verticesCount; ++i)
	{
		if (input[i] < 0) { fprintf(stderr, "Invalid input value!\n"); return 1; }
	}
	int tmp = 0;
	for (int i = 0; i < subgraphCount; ++i)
	{
		if (subgraphVerticesCount[i] < 0) { fprintf(stderr, "Subgraph vertices count are invalid!\n"); return 1; }
		tmp += subgraphVerticesCount[i];
	}
	if (tmp != verticesCount) { fprintf(stderr, "Subgraph vertices count are invalid!\n"); return 1; }
	return 0;
}

void byte_to_binary(unsigned long long n)
{
	while (n) {
		if (n & 1)
			printf("1");
		else
			printf("0");
		n >>= 1;
	}
	printf("\n");
}

int main()
{
	if (checkInput() > 0) { return 1; }
	Matrix X(verticesCount, verticesCount);
	Matrix P(verticesCount);
	Matrix PB(verticesCount);

	X.SetData(input, sizeof(input));
	X.Log();

	for (int i = 0; i < 15; ++i)
	{
		P(i) = X.ColSum(i);
		PB(i) = X.ColSum(i) - X.ColSum(i, i);
	}
	P.Log();
	PB.Log();

	Matrix** G = (Matrix**)calloc(subgraphCount, sizeof(Matrix*));
	if (G != nullptr)
	{
		long tmp = 0;
		for (int i = 0; i < subgraphCount; ++i)
		{
			G[i] = new Matrix(subgraphVerticesCount[i]);
			for (int j = 0; j < ref(G[i]).GetColCount(); ++j)
			{
				ref(G[i])(j) = tmp++;
			}
		}

		ref(G[0])(0) = 6;
		ref(G[1])(0) = 0;

		Matrix used(verticesCount);
		used.Identity(1);
		long x = -1;
		long y = -1;
		unsigned long long S;
		for (int i = 0; i < subgraphCount; ++i)
		{
			for (int j = 0; j < subgraphCount; ++j)
			{
				if(i != j)
				{ 
					printf("(%d %d)\n", i, j);
					S = checkTwoSubgraphs(X, G[i], G[j]);
					x = S / 16;
					y = S - (S / 16) * 16;
					printf("%d %d\n", ref(G[i])(x), ref(G[j])(y));
					if (used.Contains(ref(G[i])(x)) < 0 && used.Contains(ref(G[j])(y)) < 0 && x >= 0 && y >= 0)
					{
						tmp = ref(G[i])(x);
						ref(G[i])(x) = ref(G[j])(y);
						ref(G[j])(y) = tmp;
						used(ref(G[i])(x)) = used(ref(G[j])(y)) = 1;
					} 
				}
			}
		}

		for (int i = 0; i < subgraphCount; i++) { 
			//ref(G[i]) += 1;
			ref(G[i]).Log(); 
			tmp += outsideConnectionBetweenOneGraph(X, G[i]);
		}
		printf("%d\n", tmp);
		
	}


	return 0;
}

