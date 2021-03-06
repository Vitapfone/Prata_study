#pragma once

//#include "My_names.h"
using namespace My_names;

using Ar60_30 = array<array<char, 60>, 30>;


// Класс для абстрактной фигуры, на основе которой сделаны конкретные.
class Figure
{
	Location loc{ 0, 0 };

public:

//Конструкторы.
	Figure() = default;
	Figure(int x, int y) : loc{ x, y } {}
	explicit Figure(const Location & lc) : loc(lc) {}
	//Виртуальный деструктор.
	virtual ~Figure() {}

	virtual void print(Ar60_30 & ws) const = 0; //Чистая виртуальная функция отрисовки фигуры. Делает этот класс абстрактным.

//ГЕТТЕРЫ

	constexpr const Location where() const { return loc; }


//МЕТОДЫ ДВИЖЕНИЯ

	void moveRight() { ++loc.x; }//Передвинуть правее.
	void moveLeft() { --loc.x; }//Передвинуть левее.
	void moveUp() { --loc.y; }//Передвинуть выше.
	void moveDown() { ++loc.y; }//Передвинуть ниже.

};



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Circle : public Figure//Наследуется от Figure.
{
	int radius = 0;//Радиус круга.

public:

	//Конструкторы.
	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius(r) {}
	Circle(const Location & lc, size_t r) : Figure(lc), radius(r) {}
	~Circle() {}

	void print(Ar60_30 & ws) const override;//Унаследованная функция отрисовки.

	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> &ws) const;//Функция отрисовки круга для любого рабочего пространства.
};

//Функция отрисовки круга для любого рабочего пространства.
template<size_t W, size_t H> 
void Circle::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y - radius; y <= where().y + radius; ++y)
	{
		for (int x = where().x - radius; x <= where().x + radius; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
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

namespace My//Необходимость в новом пространстве имен возникла из-за наличия одноименной функции в стандарте.
{
	//Класс прямоугольника.
	class Rectangle : public Figure
	{
		int a = 0;//Длина меньшей стороны.

	public:

		//КОНСТРУКТОРЫ

		Rectangle(int x, int y, size_t a1) :Figure(x, y), a(a1) {}
		Rectangle(const Location & lc, size_t a1) : Figure(lc), a(a1) {}

		void print(Ar60_30 &ws) const override;//Функция отрисовки прямоугольника, унаследованная от предка.

		template<size_t W, size_t H> 
		void print(array<array<char, W>, H> & ws) const;//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.

	};
}

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H>
void My::Rectangle::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y; y != (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x != (where().x + 1.6*a); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
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
	int diagonal = 0;

public:

	//КОНСТРУКТОРЫ
	Rhomb() = default;
	Rhomb(int x, int y, size_t diag) : Figure(x, y), diagonal(diag) {}
	Rhomb(const Location & lc, size_t diag) : Figure(lc), diagonal(diag) {}
	~Rhomb() {}

	void print(Ar60_30 & ws) const override; //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;//Шаблон функции для отрисовки в рабочем пространстве любого размера.

};

template<size_t W, size_t H> 
void Rhomb::print(array<array<char, W>, H> & ws) const
{
	for (int y = (where().y - diagonal / 2); y <= where().y; ++y)
	{
		for (int x = (where().x - diagonal / 2); x <= (where().x + diagonal / 2); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
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
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
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

//Класс квадрата.
class Square : public Figure
{
	int a = 0;//Длина стороны.

public:

	//КОНСТРУКТОР
	Square(int x = 0, int y = 0, int a1 = 0) : Figure(x, y), a(a1) {}
	Square(const Location & lc, int a1 = 0) : Figure(lc), a(a1) {}

	void print(Ar60_30 &ws) const override;//Функция отрисовки квадрата.

	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.

};

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H> 
void Square::print(array<array<char, W>, H> & ws) const
{

	for (int y = where().y; y != (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x != (where().x + a); ++x)//Внутренний цикл печатает символы ряда
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
	int cathetus = 0;// Длина катета.
	Location point_A{ 0, 0 };//Координаты вершины с прямым углом.
	//int point_A_x = 0, point_A.y = 0;
	Location point_B{ 0, 0 };//Координаты второй вершины с острым углом. Координаты первой наследуются от Figure. 
	//int point_B.x = 0, point_B_y = 0; 

public:

	//КОНСТРУКТОРЫ
	Triangle() = default;
	Triangle(int x, int y, int cat) : Figure(x, y), cathetus(cat), point_A{ x, y + cathetus }, point_B{ x + cathetus, y + cathetus }
	{
		//cout << point_A_x << " " << point_A.y << " " << point_B.x << " " << point_B_y << endl;
	}
	Triangle(const Location & lc, int cat) : Figure(lc), cathetus(cat), point_A{ lc.x, lc.y + cathetus }, point_B{ lc.x + cathetus, lc.y + cathetus }{}
	~Triangle() {}

	void print(Ar60_30 &ws) const override; //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;//Отрисовка треугольника для рабочего пространства любого размера.

};

//Отрисовка треугольника для рабочего пространства любого размера.
template<size_t W, size_t H> 
void Triangle::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y; y <= point_A.y; ++y)
	{
		for (int x = where().x; x <= point_B.x; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - where().x < y - where().y)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
