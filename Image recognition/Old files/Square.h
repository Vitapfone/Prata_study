#pragma once
#include "Figure.h"
// Здесь будет находиться класс квадрата для отображения в консольной анимации.
using std::vector;
using std::array;

using Ar60_30 = array<array<char, 60>, 30>;


struct Square : public Figure
{
	
	unsigned a = 0;//Длина стороны.
	
	//КОНСТРУКТОР
	Square(int x = 0, int y = 0, unsigned a1 = 0) : Figure(x, y), a(a1) {}


	void print(Ar60_30 &ws);//Функция отрисовки квадрата.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.

};

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H> void Square::print(array<array<char, W>, H> & ws)
{

	for (int y = y0; y != (y0 + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = x0; x != (x0 + a); ++x)//Внутренний цикл печатает символы ряда
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}