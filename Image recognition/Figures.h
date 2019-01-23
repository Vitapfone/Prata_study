#pragma once
#include "My_names.h"
using namespace My_names;

using Ar60_30 = array<array<char, 60>, 30>;


// ��������� ��� ����������� ������, �� ������ ������� ������� ����������.
struct Figure
{
	size_t x0 = 0, y0 = 0;//����������.

	//������������.
	Figure() = default;
	Figure(size_t x, size_t y) :x0(x), y0(y) {}
	//����������� ����������.
	virtual ~Figure() = default;

	virtual void print(Ar60_30 &ws) = 0; //������ ����������� ������� ��������� ������. ������ ���� ����� �����������.

	//������ ��������

	void moveRight() { ++x0; }//����������� ������.
	void moveLeft() { --x0; }//����������� �����.
	void moveUp() { --y0; }//����������� ����.
	void moveDown() { ++y0; }//����������� ����.

};



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Circle : public Figure//����������� �� Figure.
{
	size_t radius = 0;//������ �����.

	//������������.
	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius(r) {}

	~Circle() {}

	void print(Ar60_30 &ws);//�������������� ������� ���������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> &ws);//������� ��������� ����� ��� ������ �������� ������������.
};

//������� ��������� ����� ��� ������ �������� ������������.
template<size_t W, size_t H> void Circle::print(array<array<char, W>, H> & ws)
{
	for (int y = y0 - radius; y <= y0 + radius; ++y)
	{
		for (int x = x0 - radius; x <= x0 + radius; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
			{
				if ((x - x0)*(x - x0) + (y - y0)*(y - y0) <= radius * radius)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}



// RECTANGLE ////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


// RHOMB ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������� �����.
struct Rhomb : public Figure
{
	size_t diagonal = 0;

	//������������
	Rhomb() = default;
	Rhomb(size_t x, size_t y, size_t diag) : Figure(x, y), diagonal(diag) {}

	~Rhomb() {}

	void print(Ar60_30 &ws); //��������������� ����������� ������� �� �������� ������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//������ ������� ��� ��������� � ������� ������������ ������ �������.

};

template<size_t W, size_t H> void Rhomb::print(array<array<char, W>, H> & ws)
{
	for (size_t y = (y0 - diagonal / 2); y <= y0; ++y)
	{
		for (size_t x = (x0 - diagonal / 2); x <= (x0 + diagonal / 2); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, �������������� �� ������ �� ������� �������.
			{
				if (x >= x0 - (y - (y0 - diagonal / 2)) && x <= x0 + (y - (y0 - diagonal / 2)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	for (size_t y = y0; y <= y0 + diagonal / 2; ++y)
	{
		for (size_t x = x0 - diagonal / 2; x <= x0 + diagonal / 2; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, �������������� �� ������ �� ������� �������.
			{
				if (x >= x0 - (y0 + diagonal / 2 - y) && x <= x0 + (y0 + +diagonal / 2 - y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}



// SQUARE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//��������� ��������.
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



// TRIANGLE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct Triangle : Figure //���������, �������������� �������������� ������������� �����������.
{
	size_t cathetus = 0;// ����� ������.
	size_t point_A_x = 0, point_A_y = 0;//���������� ������� � ������ �����.
	size_t point_B_x = 0, point_B_y = 0; //���������� ������ ������� � ������ �����. ���������� ������ ����������� �� Figure. 

	//������������
	Triangle() = default;
	Triangle(size_t x, size_t y, size_t cat) : Figure(x, y), cathetus(cat), point_A_x(x), point_A_y(y + cathetus), point_B_x(x + cathetus), point_B_y(y + cathetus)
	{
		//cout << point_A_x << " " << point_A_y << " " << point_B_x << " " << point_B_y << endl;
	}

	~Triangle() {}

	void print(Ar60_30 &ws); //��������������� ����������� ������� �� �������� ������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//��������� ������������ ��� �������� ������������ ������ �������.

};

//��������� ������������ ��� �������� ������������ ������ �������.
template<size_t W, size_t H> void Triangle::print(array<array<char, W>, H> & ws)
{
	for (size_t y = y0; y <= point_A_y; ++y)
	{
		for (size_t x = x0; x <= point_B_x; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, �������������� �� ������ �� ������� �������.
			{
				if (x - x0 < y - y0)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}