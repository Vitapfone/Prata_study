#include "pch.h"
#include "Figures.h"



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Унаследованная функция отрисовки.
void Circle::print(Frame & ws) const
{
	
	for (int y = where().y; y <= where().y + 2 * radius; ++y)
	{
		for (int x = where().x; x <= where().x + 2 * radius; ++x)
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())
			{
				if ((x - (where().x + radius))*(x - (where().x + radius)) + (y - (where().y + radius))*(y - (where().y + radius)) <= radius * radius)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}


// RECTANGLE ////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Функция отрисовки прямоугольника, унаследованная от предка.
void My::Rectangle::print(Frame & ws) const
{
	for (int y = where().y; y < (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x < (where().x + 1.6*a); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}


// RHOMB ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Определение унаследованной виртуальной функции.
void Rhomb::print(Frame & ws) const
{
	for (int y = where().y; y <= (where().y + diagonal / 2); ++y)
	{
		for (int x = where().x; x <= (where().x + diagonal); ++x)
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= ((where().x + diagonal / 2) - (y - where().y)) && x <= (where().x + diagonal / 2) + (y - where().y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}


	if (diagonal % 2 != 0)//Случай нечетной длины диагонали. Нужно в связи с ограничениями растрового представления.
	{
		for (int y = where().y + diagonal / 2 - 1; y <= (where().y + diagonal - 1); ++y)
		{
			for (int x = where().x + 1; x < (where().x + diagonal - 1); ++x)
			{
				if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предохраняющее от выхода за границы массива.
				{
					if (x - 1 >= ((where().x + diagonal / 2) - (where().y + diagonal - y)) && x + 1 <= ((where().x + diagonal / 2) + (where().y + diagonal - y)))
					{
						ws[y][x] = '0';
					}
				}
			}
		}
		return;
	}


	for (int y = where().y + diagonal / 2; y <= (where().y + diagonal); ++y)//Для четной длины диагонали.
	{
		for (int x = where().x; x < (where().x + diagonal); ++x)
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= ((where().x + diagonal / 2) - (where().y + diagonal - y)) && x <= ((where().x + diagonal / 2) + (where().y + diagonal - y)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}


// SQUARE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Функция отрисовки квадрата, унаследованная от предка.
void Square::print(Frame & ws) const
{

	for (int y = where().y; y != (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x != (where().x + a); ++x)//Внутренний цикл печатает символы ряда
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}


// TRIANGLE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Унаследованная функция отрисовки треугольника.
void Triangle::print(Frame & ws) const
{
	for (int y = where().y; y <= point_A.y; ++y)
	{
		for (int x = where().x; x <= point_B.x; ++x)
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - where().x < y - where().y)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
