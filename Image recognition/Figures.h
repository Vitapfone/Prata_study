#pragma once
#include "My_names.h"
using namespace My_names;

using Ar60_30 = array<array<char, 60>, 30>;


// Структура для абстрактной фигуры, на основе которой сделаны конкретные.
struct Figure
{
	size_t x0 = 0, y0 = 0;//Координаты.

	//Конструкторы.
	Figure() = default;
	Figure(size_t x, size_t y) :x0(x), y0(y) {}
	//Виртуальный деструктор.
	virtual ~Figure() = default;

	virtual void print(Ar60_30 &ws) = 0; //Чистая виртуальная функция отрисовки фигуры. Делает этот класс абстрактным.

	//МЕТОДЫ ДВИЖЕНИЯ

	void moveRight() { ++x0; }//Передвинуть правее.
	void moveLeft() { --x0; }//Передвинуть левее.
	void moveUp() { --y0; }//Передвинуть выше.
	void moveDown() { ++y0; }//Передвинуть ниже.

};



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Circle : public Figure//Наследуется от Figure.
{
	size_t radius = 0;//Радиус круга.

	//Конструкторы.
	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius(r) {}

	~Circle() {}

	void print(Ar60_30 &ws);//Унаследованная функция отрисовки.

	template<size_t W, size_t H> void print(array<array<char, W>, H> &ws);//Функция отрисовки круга для любого рабочего пространства.
};

//Функция отрисовки круга для любого рабочего пространства.
template<size_t W, size_t H> void Circle::print(array<array<char, W>, H> & ws)
{
	for (int y = y0 - radius; y <= y0 + radius; ++y)
	{
		for (int x = x0 - radius; x <= x0 + radius; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
			{
				if ((x - x0)*(x - x0) + (y - y0)*(y - y0) <= radius * radius)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}



// RECTANGLE ////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


// RHOMB ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Структура ромба.
struct Rhomb : public Figure
{
	size_t diagonal = 0;

	//КОНСТРУКТОРЫ
	Rhomb() = default;
	Rhomb(size_t x, size_t y, size_t diag) : Figure(x, y), diagonal(diag) {}

	~Rhomb() {}

	void print(Ar60_30 &ws); //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Шаблон функции для отрисовки в рабочем пространстве любого размера.

};

template<size_t W, size_t H> void Rhomb::print(array<array<char, W>, H> & ws)
{
	for (size_t y = (y0 - diagonal / 2); y <= y0; ++y)
	{
		for (size_t x = (x0 - diagonal / 2); x <= (x0 + diagonal / 2); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= x0 - (y - (y0 - diagonal / 2)) && x <= x0 + (y - (y0 - diagonal / 2)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	for (size_t y = y0; y <= y0 + diagonal / 2; ++y)
	{
		for (size_t x = x0 - diagonal / 2; x <= x0 + diagonal / 2; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= x0 - (y0 + diagonal / 2 - y) && x <= x0 + (y0 + +diagonal / 2 - y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}



// SQUARE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Структура квадрата.
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



// TRIANGLE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


struct Triangle : Figure //Структура, представляющая равнобедренный прямоугольный треугольник.
{
	size_t cathetus = 0;// Длина катета.
	size_t point_A_x = 0, point_A_y = 0;//Координаты вершины с прямым углом.
	size_t point_B_x = 0, point_B_y = 0; //Координаты второй вершины с острым углом. Координаты первой наследуются от Figure. 

	//КОНСТРУКТОРЫ
	Triangle() = default;
	Triangle(size_t x, size_t y, size_t cat) : Figure(x, y), cathetus(cat), point_A_x(x), point_A_y(y + cathetus), point_B_x(x + cathetus), point_B_y(y + cathetus)
	{
		//cout << point_A_x << " " << point_A_y << " " << point_B_x << " " << point_B_y << endl;
	}

	~Triangle() {}

	void print(Ar60_30 &ws); //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Отрисовка треугольника для рабочего пространства любого размера.

};

//Отрисовка треугольника для рабочего пространства любого размера.
template<size_t W, size_t H> void Triangle::print(array<array<char, W>, H> & ws)
{
	for (size_t y = y0; y <= point_A_y; ++y)
	{
		for (size_t x = x0; x <= point_B_x; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - x0 < y - y0)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
