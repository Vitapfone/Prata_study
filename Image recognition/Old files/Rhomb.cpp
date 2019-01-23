#include "pch.h"
#include "Figure.h"
#include "Rhomb.h"

void Rhomb::print(Ar60_30 & ws)//ќпределение унаследованной виртуальной функции.
{
	for (size_t y = (y0 - diagonal / 2); y <= y0; ++y)
	{
		for (size_t x = (x0 - diagonal / 2); x <= (x0 + diagonal / 2); ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//”словие, предохран€ющее от выхода за границы массива.
			{
				if (x >= x0-(y-(y0-diagonal/2)) && x<=x0+ (y - (y0 - diagonal / 2)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	for (size_t y = y0 ; y <= y0 + diagonal / 2; ++y)
	{
		for (size_t x = x0 - diagonal / 2; x <= x0 + diagonal / 2; ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//”словие, предохран€ющее от выхода за границы массива.
			{
				if (x >= x0-(y0+diagonal/2-y) && x <= x0+ (y0 +  + diagonal / 2 - y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
