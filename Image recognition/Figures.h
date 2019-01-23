#pragma once
#include "My_names.h"
using namespace My_names;

using Ar60_30 = array<array<char, 60>, 30>;


// Класс для абстрактной фигуры, на основе которой сделаны конкретные.
class Figure
{
protected:

	Location loc{ 0, 0 };

public:

	//Конструкторы.
	Figure() = default;
	Figure(int x, int y) : loc{ x, y } {}
	explicit Figure(const Location & lc) : loc(lc) {}
	//Виртуальный деструктор.
	virtual ~Figure() = default;

	virtual void print(Ar60_30 &ws) = 0; //Чистая виртуальная функция отрисовки фигуры. Делает этот класс абстрактным.

	//МЕТОДЫ ДВИЖЕНИЯ

	void moveRight() { ++loc.x; }//Передвинуть правее.
	void moveLeft() { --loc.x; }//Передвинуть левее.
	void moveUp() { --loc.y; }//Передвинуть выше.
	void moveDown() { ++loc.y; }//Передвинуть ниже.

};



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Circle : public Figure//Наследуется от Figure.
{
	size_t radius = 0;//Радиус круга.

public:

	//Конструкторы.
	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius(r) {}
	Circle(const Location & lc, size_t r) : Figure(lc), radius(r) {}
	~Circle() {}

	void print(Ar60_30 &ws);//Унаследованная функция отрисовки.

	template<size_t W, size_t H> void print(array<array<char, W>, H> &ws);//Функция отрисовки круга для любого рабочего пространства.
};

//Функция отрисовки круга для любого рабочего пространства.
template<size_t W, size_t H> void Circle::print(array<array<char, W>, H> & ws)
{
	for (int y = loc.y - radius; y <= loc.y + radius; ++y)
	{
		for (int x = loc.x - radius; x <= loc.x + radius; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
			{
				if ((x - loc.x)*(x - loc.x) + (y - loc.y)*(y - loc.y) <= radius * radius)
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
	class Rectangle : public Figure
	{
		size_t a = 0;//Длина меньшей стороны.

	public:

		//КОНСТРУКТОРЫ

		Rectangle(int x, int y, size_t a1) :Figure(x, y), a(a1) {}
		Rectangle(const Location & lc, size_t a1) : Figure(lc), a(a1) {}

		void print(Ar60_30 &ws);//Функция отрисовки прямоугольника, унаследованная от предка.

		template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.

	};
}

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H>
void My::Rectangle::print(array<array<char, W>, H>& ws)
{
	for (int y = loc.y; y != (loc.y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = loc.x; x != (loc.x + 1.6*a); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}


// RHOMB ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Класс ромба.
class Rhomb : public Figure
{
	size_t diagonal = 0;

public:

	//КОНСТРУКТОРЫ
	Rhomb() = default;
	Rhomb(int x, int y, size_t diag) : Figure(x, y), diagonal(diag) {}
	Rhomb(const Location & lc, size_t diag) : Figure(lc), diagonal(diag) {}
	~Rhomb() {}

	void print(Ar60_30 &ws); //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Шаблон функции для отрисовки в рабочем пространстве любого размера.

};

template<size_t W, size_t H> void Rhomb::print(array<array<char, W>, H> & ws)
{
	for (size_t y = (loc.y - diagonal / 2); y <= loc.y; ++y)
	{
		for (size_t x = (loc.x - diagonal / 2); x <= (loc.x + diagonal / 2); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= loc.x - (y - (loc.y - diagonal / 2)) && x <= loc.x + (y - (loc.y - diagonal / 2)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	for (size_t y = loc.y; y <= loc.y + diagonal / 2; ++y)
	{
		for (size_t x = loc.x - diagonal / 2; x <= loc.x + diagonal / 2; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= loc.x - (loc.y + diagonal / 2 - y) && x <= loc.x + (loc.y + +diagonal / 2 - y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}



// SQUARE ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Класс квадрата.
class Square : public Figure
{
	size_t a = 0;//Длина стороны.

public:

	//КОНСТРУКТОР
	Square(int x = 0, int y = 0, size_t a1 = 0) : Figure(x, y), a(a1) {}
	Square(const Location & lc, size_t a1 = 0) : Figure(lc), a(a1) {}

	void print(Ar60_30 &ws);//Функция отрисовки квадрата.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.

};

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H> void Square::print(array<array<char, W>, H> & ws)
{

	for (int y = loc.y; y != (loc.y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = loc.x; x != (loc.x + a); ++x)//Внутренний цикл печатает символы ряда
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}



// TRIANGLE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Triangle : public Figure //Класс, представляющий равнобедренный прямоугольный треугольник.
{
	size_t cathetus = 0;// Длина катета.
	Location point_A{ 0, 0 };//Координаты вершины с прямым углом.
	//int point_A_x = 0, point_A.y = 0;
	Location point_B{ 0, 0 };//Координаты второй вершины с острым углом. Координаты первой наследуются от Figure. 
	//int point_B.x = 0, point_B_y = 0; 

public:

	//КОНСТРУКТОРЫ
	Triangle() = default;
	Triangle(int x, int y, size_t cat) : Figure(x, y), cathetus(cat), point_A{ x, y + int(cathetus) }, point_B{ x + int(cathetus), y + int(cathetus) }
	{
		//cout << point_A_x << " " << point_A.y << " " << point_B.x << " " << point_B_y << endl;
	}
	Triangle(const Location & lc, size_t cat) : Figure(lc), cathetus(cat), point_A{ lc.x, lc.y + int(cathetus) }, point_B{ lc.x + int(cathetus), lc.y + int(cathetus) }{}
	~Triangle() {}

	void print(Ar60_30 &ws); //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Отрисовка треугольника для рабочего пространства любого размера.

};

//Отрисовка треугольника для рабочего пространства любого размера.
template<size_t W, size_t H> void Triangle::print(array<array<char, W>, H> & ws)
{
	for (size_t y = loc.y; y <= point_A.y; ++y)
	{
		for (size_t x = loc.x; x <= point_B.x; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - loc.x < y - loc.y)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
