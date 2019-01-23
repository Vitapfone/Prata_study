#pragma once
#include "Figure.h"
// ����� ����� ���������� ����� �������� ��� ����������� � ���������� ��������.
using std::vector;
using std::array;

using Ar60_30 = array<array<char, 60>, 30>;


struct Square : public Figure
{
	
	unsigned a = 0;//����� �������.
	
	//�����������
	Square(int x = 0, int y = 0, unsigned a1 = 0) : Figure(x, y), a(a1) {}


	void print(Ar60_30 &ws);//������� ��������� ��������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//������ ��� ��������� �������� � ������� ������������ ������ �������.

};

//������ ��� ��������� �������� � ������� ������������ ������ �������.
template<size_t W, size_t H> void Square::print(array<array<char, W>, H> & ws)
{

	for (int y = y0; y != (y0 + a); ++y) //������� ������������ �������, ��������� �� ������� ���������� �����.
	{
		for (int x = x0; x != (x0 + a); ++x)//���������� ���� �������� ������� ����
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, ���������������� �� ������ �� ������� �������.
			{
				ws[y][x] = '0';
			}
		}
	}
}