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
	Matrix(int size);	//���������� ���������� ������� ��������� �������
	Matrix(int rows, int columns);	//���������� ����� ������� ��������� �������

	int& operator()(int i, int j)const;  //����� �������� �������� �� ��������
	int& operator()(int i) const;  //����� �������� �������� �� �������
	void Identity(int number);	//��������� ������� ��������� ������� ������
	void Mirror(void);	//�������� ������� ������������ ������� ���������
	int rowSum(int rowIndex);	//����� � ������
	int colSum(int colIndex);	//����� � �������
	void Log(void);	//������� ������� � �������
	int Max(void);	//������������ ������� � �������
	int Min(void);	//����������� ������� � �������
	bool IsEmpty(void);	//��������� �������� �� ������� ������ (����������� ������)

	~Matrix();
};

