#include "pch.h"
#include "Figure.h"
#include "Circle.h"


//Унаследованная функция отрисовки.
void Circle::print(Ar60_30 & ws)
{
	for (int y = y0 - radius; y <= y0 + radius; ++y)
	{
		for (int x = x0 - radius; x <= x0 + radius; ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)
			{
				if ((x - x0)*(x - x0) + (y - y0)*(y - y0) <= radius * radius)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
