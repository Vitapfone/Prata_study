#include "pch.h"
#include "Cluster.h"

//Подсчет отличных от фона пикселей.
void Cluster::counter(const Inner_frame & ws, char background)
{
	for (int y = loc_.y_; y != (loc_.y_ + s_); ++y)//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = loc_.x_; x != (loc_.x_ + s_); ++x)
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предостерегающее от выхода за границы массива.
			{
				if (ws[y][x] != background)//Если эл-т не равен фону,
				{
					++count_;//то увеличивает счетчик таких эл-тов.
				}
			}
		}
	}
}
