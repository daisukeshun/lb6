#pragma once
#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define min(a, b) a < b? a : b;
#define max(a, b) a > b? a : b;
class Matrix
{
private:
	int* data;
	int rowSize, colSize;
	int & Value(int i, int j);
public:
	Matrix(int size);	//возвращает квадратную матрицу заданного размера
	Matrix(int rows, int columns);	//возвращает любую матрицу заданного размера

	int& operator()(int i, int j)const;  //можно получать элементы по индексам
	int& operator()(int i) const;  //можно получать элементы по индексу
	void Identity(int number);	//заполняет главную диагональ матрицы числом
	void Mirror(void);	//отражает матрицу относительно главной диагонали
	int rowSum(int rowIndex);	//сумма в строке
	int colSum(int colIndex);	//сумма в колонке
	void Log(void);	//выводит матрицу в консоль
	int Max(void);	//максимальный элемент в матрице
	int Min(void);	//минимальный элемент в матрице
	bool IsEmpty(void);	//проверяет является ли матрица пустой (заполненной нулями)

	~Matrix();
};

