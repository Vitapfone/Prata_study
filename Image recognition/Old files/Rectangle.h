#pragma once
using std::vector;
using std::array;

using Ar60_30 = array<array<char, 60>, 30>;
namespace My//Необходимость в новом пространстве имен возникла из-за наличия одноименной функции в стандарте.
{
	//Класс прямоугольника.
	struct Rectangle : public Figure
	{
		size_t a = 0;//Длина меньшей стороны.

		//КОНСТРУКТОР

		Rectangle(int x, int y, size_t a1) :Figure(x, y), a(a1) {}

		void print(Ar60_30 &ws);//Функция отрисовки прямоугольника, унаследованная от предка.

		template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.

	};
}

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H>
void My::Rectangle::print(array<array<char, W>, H>& ws)
{
	for (int y = y0; y != (y0 + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = x0; x != (x0 + 1.6*a); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}
