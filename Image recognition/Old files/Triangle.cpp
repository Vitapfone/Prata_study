#include "pch.h"
#include "Figure.h"
#include "Triangle.h"
using std::cout; using std::endl;
using std::array;
using Ar60_30 = array<array<char, 60>, 30>;

void Triangle::print(Ar60_30 & ws)//”наследованна€ функци€ отрисовки треугольника.
{
	for (size_t y = y0; y <= point_A_y; ++y)
	{
		for (size_t x = x0; x <= point_B_x; ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//”словие, предохран€ющее от выхода за границы массива.
			{
				if (x-x0 < y-y0)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
