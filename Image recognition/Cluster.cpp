#include "pch.h"
#include "Square.h"
#include "Cluster.h"

//������� ������������ ���������� ����� � ��������, ���������� �������� �� ���� ��������.
template<size_t W, size_t H>  void Cluster::counter(array<array<char, W>, H> ws, char background)
{
	//cout << "Counting... " << endl;
	for (int y = yC; y != (yC + s); ++y)//���������� ��� ��-�� �������� ������������ � �������� ����������� ��������.
	{
		for (int x = xC; x != (xC + s); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, ���������������� �� ������ �� ������� �������.
			{
				if (ws[y][x] != background)//���� ��-� �� ����� ����,
				{
					++count;//�� ����������� ������� ����� ��-���.
				}
			}
		}
	}
}
