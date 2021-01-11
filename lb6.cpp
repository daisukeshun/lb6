#include <stdlib.h>
#include "Matrix.h"

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

int connectionSumBetwenOneGraphByIndex(Matrix& base, Matrix* G, int index)
{
	int ret = 0;
	for (int i = 0; i < 0[G].GetColCount(); ++i)
	{
		ret += base(index, 0[G](i));
	}
	return ret;
}

int connectionSumBetweenTwoGraphsByIndex(Matrix& base, Matrix * G1, int x, Matrix * G2, int y)
{
	return connectionSumBetwenOneGraphByIndex(base, G2, 0[G1](x)) + connectionSumBetwenOneGraphByIndex(base, G1, 0[G2](y));
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
	return base(0[G1](x), 0[G2](y));
}

int checkTwoSubgraphs(Matrix & base, Matrix * G1, Matrix * G2)
{
	int tmp1, tmp2, tmp3;
	int maxDeltaS = INT_MIN;
	for (int i = 0; i < 0[G1].GetColCount(); ++i)
	{
		for (int j = 0; j < 0[G2].GetColCount(); ++j)
		{
			tmp1 = insideP(base, G1, i, G2, j);
			tmp2 = outsideP(base, G1, i, G2, j);
			tmp3 = betweenP(base, G1, i, G2, j);
			maxDeltaS = max(
				maxDeltaS, 
				deltaS(
					insideP(base, G1, i, G2, j),
					outsideP(base, G1, i, G2, j),
					betweenP(base, G1, i, G2, j)
				)
			);

			/*
			printf("(%d, %d) %d %d %d : %d\n", 
				0[G1](i), 0[G2](j), 
				tmp1, tmp2, tmp3,
				deltaS(tmp1, tmp2, tmp3));
			*/
		}
	}
	return maxDeltaS;
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
		int tmp = 0;
		for (int i = 0; i < subgraphCount; ++i)
		{
			G[i] = new Matrix(subgraphVerticesCount[i]);
			for (int j = 0; j < 0[G[i]].GetColCount(); ++j)
			{
				0[G[i]](j) = tmp++;
			}
		}

		for (int i = 0; i < subgraphCount; ++i)
		{
			for (int j = 0; j < subgraphCount; ++j)
			{
				if(i != j)
				{ 
					int S = checkTwoSubgraphs(X, G[i], G[j]);
					printf("(%d %d) : %d\n", i, j, S);
					printf("\n");
				}
			}
		}
	}



	return 0;
}

