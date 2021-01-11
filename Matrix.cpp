#include "Matrix.h"

Matrix::Matrix(int size)
{
	this->rowSize = this->colSize = 0;
	this->data = nullptr;
	if (size > 0)
	{ 
		this->colSize = size;
		this->rowSize = 1;
		this->data = (int*)calloc(size, sizeof(int));
	}
}

Matrix::Matrix(int rows, int columns)
{
	this->rowSize = this->colSize = 0;
	this->data = nullptr;
	if (rows > 0 && columns > 0)
	{
		this->rowSize = rows; 
		this->colSize = columns;
		this->data = (int*)calloc(rows * columns, sizeof(int));
	}
}

int& Matrix::operator()(int i, int j) const
{
	if (i < this->colSize && i >= 0 && j < this->rowSize && j >= 0)
	{
		return this->data[i * this->rowSize + j];
	}
	return this->data[0];
}

int& Matrix::operator()(int i) const
{
	if (i >= 0 && i < this->rowSize * this->colSize)
	{
		return this->data[i];
	}
	return this->data[0];
}

void Matrix::Identity(int number)
{
	for (int i = 0; i < this->rowSize; i++)
	{
		this->Value(i, i) = number;
	}
}

void Matrix::Mirror(void)
{
	if (this->rowSize == this->colSize)
	{
		for (int i = 0; i < this->rowSize; ++i)
		{
			for (int j = 0; j < this->rowSize; ++j)
			{
				this->Value(i, j) = this->Value(j, i);
			}
		}
	}
}

int Matrix::RowSum(int rowIndex)
{
	int ret = 0;
	if (rowIndex < this->rowSize && rowIndex >= 0)
	{
		for (int i = 0; i < this->colSize; i++)
		{
			ret += this->Value(rowIndex, i);
		}
	}
	return ret;
}

int Matrix::RowSum(int rowIndex, int n)
{
	int ret = 0;
	if (rowIndex < this->rowSize && rowIndex >= 0)
	{
		for (int i = 0; i < n; i++)
		{
			ret += this->Value(rowIndex, i);
		}
	}
	return ret;
}

int Matrix::ColSum(int colIndex)
{
	int ret = 0;
	if (colIndex < this->colSize && colIndex >= 0)
	{
		for (int i = 0; i < this->colSize; i++)
		{
			ret += this->Value(i, colIndex);
		}
	}
	return ret;
}

int Matrix::ColSum(int colIndex, int n)
{
	int ret = 0;
	if (colIndex < this->colSize && colIndex >= 0)
	{
		for (int i = 0; i < n; i++)
		{
			ret += this->Value(i, colIndex);
		}
	}
	return ret;
}

void Matrix::SetData(const int* data, size_t size)
{
	memcpy(this->data, data, size);
}

void Matrix::Fill(int n)
{
	memset(this->data, n, this->rowSize * this->colSize * sizeof(int));
}

int Matrix::GetRowCount(void)
{
	return this->rowSize;
}

int & Matrix::Value(int i, int j)
{
	return this->operator()(i, j);
}

int Matrix::GetColCount(void)
{
	return this->colSize;
}

void Matrix::Log(void)
{
	for (int i = 0; i < this->rowSize * this->colSize; ++i)
	{
		if (i % this->colSize == 0)
		{
			printf("\n");
		}
		printf("%d\t", this->data[i]);
	}
	printf("\n");
}

int Matrix::Max(void)
{
	int ret = INT_MIN;
	for (int i = 0; i < this->rowSize * this->colSize; ++i)
	{
		ret = max(ret, this->data[i]);
	}
	return ret;
}

int Matrix::Min(void)
{
	int ret = INT_MAX;
	for (int i = 0; i < this->rowSize * this->colSize; ++i)
	{
		ret = min(ret, this->data[i]);
	}
	return ret;
}

bool Matrix::IsEmpty(void)
{
	for (int i = 0; i < (this->colSize * this->rowSize); ++i)
	{
		if (this->data[i]) { return false; }
	}
	return true;
}

Matrix::~Matrix()
{
	this->rowSize = this->colSize = 0;
	if(this->data != nullptr)
	{ 
		free(this->data);
		this->data = nullptr;
	}
}

