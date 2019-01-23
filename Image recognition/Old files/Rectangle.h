#pragma once
using std::vector;
using std::array;

using Ar60_30 = array<array<char, 60>, 30>;
namespace My//������������� � ����� ������������ ���� �������� ��-�� ������� ����������� ������� � ���������.
{
	//����� ��������������.
	struct Rectangle : public Figure
	{
		size_t a = 0;//����� ������� �������.

		//�����������

		Rectangle(int x, int y, size_t a1) :Figure(x, y), a(a1) {}

		void print(Ar60_30 &ws);//������� ��������� ��������������, �������������� �� ������.

		template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//������ ��� ��������� �������� � ������� ������������ ������ �������.

	};
}

//������ ��� ��������� �������� � ������� ������������ ������ �������.
template<size_t W, size_t H>
void My::Rectangle::print(array<array<char, W>, H>& ws)
{
	for (int y = y0; y != (y0 + a); ++y) //������� ������������ �������, ��������� �� ������� ���������� �����.
	{
		for (int x = x0; x != (x0 + 1.6*a); ++x)//���������� ���� �������� ������� ����. ������� �������  ��������� � 1.6 ����.
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, ���������������� �� ������ �� ������� �������.
			{
				ws[y][x] = '0';
			}
		}
	}
}
