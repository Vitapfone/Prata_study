#include "pch.h"
#include "Square.h"
#include "Cluster.h"

//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
template<size_t W, size_t H>  void Cluster::counter(array<array<char, W>, H> ws, char background)
{
	//cout << "Counting... " << endl;
	for (int y = yC; y != (yC + s); ++y)//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = xC; x != (xC + s); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				if (ws[y][x] != background)//Если эл-т не равен фону,
				{
					++count;//то увеличивает счетчик таких эл-тов.
				}
			}
		}
	}
}
