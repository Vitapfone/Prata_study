#pragma once

#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"

using namespace My_names;



using Frame = array<array<char, 120>, 80>;


// Класс для абстрактной фигуры, на основе которой сделаны конкретные.
class Figure
{
	Location loc{ 0, 0 };

public:

//КОНСТРУКТОРЫ

	Figure() = default;
	Figure(int x, int y) : loc{ x, y } {}
	explicit Figure(const Location & lc) : loc(lc) {}
	//Виртуальный деструктор.
	virtual ~Figure() {}

	

//ГЕТТЕРЫ

	constexpr const Location where() const { return loc; }


//МЕТОДЫ ДВИЖЕНИЯ

	//Используется NVI (невиртуальный интерфейс).

	//Передвинуть правее.
	void move_right() { moveRight(); }
	//Передвинуть левее.
	void move_left() { moveLeft(); }
	//Передвинуть выше.
	void move_up() { moveUp(); }
	//Передвинуть ниже.
	void move_down() { moveDown(); }

protected:

	virtual void moveRight() { ++loc.x; }
	virtual void moveLeft() { --loc.x; }
	virtual void moveUp() { --loc.y; }
	virtual void moveDown() { ++loc.y; }

public:

//ДРУГИЕ

	//Чистая виртуальная функция отрисовки фигуры. Делает этот класс абстрактным.
	virtual void print(Frame & ws) const = 0; 
};



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Circle : public Figure//Наследуется от Figure.
{
	int radius = 0;//Радиус круга.

public:

//КОНСТРУКТОРЫ

	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius(r) { }
	Circle(const Location & lc, size_t r) : Figure(lc), radius(r) {}
	~Circle() {}

//ГЕТТЕРЫ

	//Получить радиус.
	int get_radius() const { return radius; }

//ДРУГИЕ

	//Унаследованная функция отрисовки.
	void print(Frame & ws) const;

	//Функция отрисовки круга для любого рабочего пространства.
	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;
};

//Функция отрисовки круга для любого рабочего пространства.
template<size_t W, size_t H> 
void Circle::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y; y <= where().y + 2*radius; ++y)
	{
		for (int x = where().x; x <= where().x + 2*radius; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
			{
				if ((x - (where().x+radius))*(x - (where().x+radius)) + (y - (where().y+radius))*(y - (where().y+radius)) <= radius * radius)
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
		int a = 0;	//Длина меньшей стороны.

	public:

	//КОНСТРУКТОРЫ

		Rectangle(int x, int y, size_t a1) :Figure(x, y), a(a1) { }
		Rectangle(const Location & lc, size_t a1) : Figure(lc), a(a1) {}

	//ГЕТТЕРЫ

		//Выдать длину стороны.
		int get_side_length() const { return a; }

	//ДРУГИЕ

		//Функция отрисовки прямоугольника, унаследованная от предка.
		void print(Frame &ws) const;

		//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
		template<size_t W, size_t H> 
		void print(array<array<char, W>, H> & ws) const;
	};
}

//Шаблон для отрисовки прямоугольника в рабочем пространстве любого размера.
template<size_t W, size_t H>
void My::Rectangle::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y; y <= (where().y + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x <= (where().x + 1.6*a); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
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

//ГЕТТЕРЫ

	//Получить диагональ.
	int get_diagonal() const { return diagonal; }

//ДРУГИЕ

	//Переопределение виртуальной функции из базового класса.
	void print(Frame & ws) const; 

	//Шаблон функции для отрисовки в рабочем пространстве любого размера.
	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;

};

template<size_t W, size_t H> 
void Rhomb::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y; y <= (where().y+diagonal/2); ++y)
	{
		for (int x = where().x; x <= (where().x + diagonal); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= ((where().x+diagonal/2) - (y - where().y)) && x <= (where().x+diagonal/2) + (y - where().y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	
	if (diagonal % 2 != 0)//Случай нечетной длины диагонали. Нужно в связи с ограничениями растрового представления.
	{
		for (int y = where().y + diagonal / 2-1; y <= (where().y + diagonal-1); ++y)
		{
			for (int x = where().x+1; x < (where().x + diagonal-1); ++x)
			{
				if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
				{
					if (x-1 >= ((where().x + diagonal / 2) - (where().y + diagonal - y)) && x+1 <= ((where().x + diagonal / 2) + (where().y + diagonal - y)))
					{
						ws[y][x] = '0';
					}
				}
			}
		}
		return;
	}

	
	for (int y = where().y+diagonal/2; y <= (where().y + diagonal); ++y)//Для четной длины диагонали.
	{
		for (int x = where().x; x < (where().x + diagonal); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= ((where().x+diagonal/2) - (where().y + diagonal - y)) && x <= ((where().x+diagonal/2) + (where().y + diagonal - y)))
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

	//КОНСТРУКТОРЫ

	Square(int x = 0, int y = 0, size_t a1 = 0) : Figure(x, y), a(a1) {}
	Square(const Location & lc, size_t a1 = 0) : Figure(lc), a(a1) {}
	~Square() {}
	
//ГЕТТЕРЫ

	//Выдать длину стороны.
	int get_side_length() const { return a; }


//ДРУГИЕ

	//Функция отрисовки квадрата.
	void print(Frame &ws) const;

	//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;

};

//Шаблон для отрисовки квадрата в рабочем пространстве любого размера.
template<size_t W, size_t H> 
void Square::print(array<array<char, W>, H> & ws) const
{

	for (int y = where().y; y != (where().y + a); ++y)		//Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x; x != (where().x + a); ++x)	//Внутренний цикл печатает символы ряда
		{
			if (x >= 0 && x < W && y >= 0 && y < H)			//Условие, предостерегающее от выхода за границы массива.
			{
				ws[y][x] = '0';
			}
		}
	}
}



// TRIANGLE ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Triangle : public Figure //Класс, представляющий равнобедренный прямоугольный треугольник.
{
	size_t		cathetus	= 0;		// Длина катета.
	Location	point_A		{ 0, 0 };	//Координаты вершины с прямым углом.
	Location	point_B		{ 0, 0 };	//Координаты второй вершины с острым углом. Координаты первой наследуются от Figure. 
	

public:

//КОНСТРУКТОРЫ
	Triangle() = default;
	Triangle(int x, int y, size_t cat) :	Figure(x, y), 
											cathetus(cat), 
											point_A{ x, y + static_cast<int>(cathetus) }, 
											point_B{ x + static_cast<int>(cathetus), y + static_cast<int>(cathetus) }
											{}

	Triangle(const Location & lc, size_t cat) : Figure(lc), 
												cathetus(cat), 
												point_A{ lc.x, lc.y + static_cast<int>(cathetus) }, 
												point_B{ lc.x + static_cast<int>(cathetus), lc.y + static_cast<int>(cathetus) }
												{}

	~Triangle() {}

//ГЕТТЕРЫ

	//Получить длину катета.
	size_t get_cathetus() const { return cathetus; }
	//Получить точку А.
	Location get_point_A() const { return point_A; }
	//Получить точку Б.
	Location get_point_B() const { return point_B; }


//ДРУГИЕ

	//Переопределение виртуальной функции из базового класса.
	void print(Frame &ws) const; 

	//Отрисовка треугольника для рабочего пространства любого размера.
	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;


	//МЕТОДЫ ДВИЖЕНИЯ

private:

	virtual void moveRight()	{ Figure::moveRight(); point_A.x++; point_B.x++; }	//Передвинуть правее.
	virtual void moveLeft()		{ Figure::moveLeft(); point_A.x--; point_B.x--; }	//Передвинуть левее.
	virtual void moveUp()		{ Figure::moveUp(); point_A.y--; point_B.y--; }		//Передвинуть выше.
	virtual void moveDown()		{ Figure::moveDown(); point_A.y++; point_B.y++; }	//Передвинуть ниже.

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
