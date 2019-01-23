#pragma once
#include "My_names.h"
using namespace My_names;

//Здесь шаблоны функций, которые должны отрисовать рабочее пространство любых размеров.
//Делает границы рабочего пространства видимыми.

template<size_t W, size_t H> void make_border(array<array<char, W>, H> & ar)
{
	for (int i = 0; i < W; ++i)
	{
		ar[0][i] = '=';
		ar[H - 1][i] = '=';
	}
	for (int j = 0; j < H; ++j)
	{
		ar[j][0] = '!';
		ar[j][W - 1] = '!';
	}
}

//Отрисовывает все рабочее пространство
template<size_t W, size_t H> void print_workspase(array<array<char, W>, H> & ar)
{
	make_border(ar);
	for (auto &e : ar)// Выводим в консоль.
	{
		for (auto &e2 : e)
		{
			cout << e2;
		}
		cout << endl;
	}
	cout << endl;

}