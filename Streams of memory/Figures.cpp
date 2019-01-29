﻿#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Figures.h"


using namespace My_names;

// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Унаследованная функция отрисовки.
void Circle::print(Ar60_30 & ws)
{
	for (int y = where().y - radius; y <= where().y + radius; ++y)
	{
		for (int x = where().x - radius; x <= where().x + radius; ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)
			{
				if ((x - where().x)*(x - where().x) + (y - where().y)*(y - where().y) <= radius * radius)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}


// RECTANGLE ////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Функция отрисовки прямоугольника, унаследованная от предка.
void My::Rectangle::print(Ar60_30 & ws)
{
	for (int y = where().y; y != (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x != (where().x + 1.6*a); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}


// RHOMB ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Rhomb::print(Ar60_30 & ws)//Определение унаследованной виртуальной функции.
{
	for (int y = (where().y - diagonal / 2); y <= where().y; ++y)
	{
		for (int x = (where().x - diagonal / 2); x <= (where().x + diagonal / 2); ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= where().x - (y - (where().y - diagonal / 2)) && x <= where().x + (y - (where().y - diagonal / 2)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	for (int y = where().y; y <= where().y + diagonal / 2; ++y)
	{
		for (int x = where().x - diagonal / 2; x <= where().x + diagonal / 2; ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= where().x - (where().y + diagonal / 2 - y) && x <= where().x + (where().y + +diagonal / 2 - y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}


// SQUARE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Функция отрисовки квадрата, унаследованная от предка.
void Square::print(Ar60_30 & ws)
{

	for (int y = where().y; y != (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x != (where().x + a); ++x)//Внутренний цикл печатает символы ряда
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}


//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
//template<size_t W, size_t H> 
void Square::print(/*array<array<char, W>, H>*/ vector<vector<char>> & ws)
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

void Triangle::print(Ar60_30 & ws)//Унаследованная функция отрисовки треугольника.
{
	for (int y = where().y; y <= point_A.y; ++y)
	{
		for (int x = where().x; x <= point_B.x; ++x)
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - where().x < y - where().y)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
