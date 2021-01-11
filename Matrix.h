#pragma once
#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <string.h>

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
	void operator+=(int n);
	void Identity(int number);	//��������� ������� ��������� ������� ������
	void Mirror(void);	//�������� ������� ������������ ������� ���������
	int RowSum(int rowIndex);	//����� � ������
	int RowSum(int rowIndex, int n);	//����� ���������� ���������� ��������� � ������
	int ColSum(int colIndex);	//����� � �������
	int ColSum(int colIndex, int n);	//����� ���������� ���������� ��������� � �������
	void SetData(const int * data, size_t size);	//����� ���������� ����� ������ � �������
	void Fill(int n);	//��������� ������� ����� ���������
	int GetRowCount(void);	//���������� ���������� �����
	int GetColCount(void);	//���������� ���������� ��������
	void Log(void);	//������� ������� � �������
	int Max(void);	//������������ ������� � �������
	int Min(void);	//����������� ������� � �������
	bool IsEmpty(void);	//��������� �������� �� ������� ������ (����������� ������)
	int Contains(int value);	//��������� ���� �� �������� � �������

	~Matrix();
};

