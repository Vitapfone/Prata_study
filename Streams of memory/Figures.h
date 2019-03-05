#pragma once

#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"

using namespace My_names;



using Frame = array<array<char, 120>, 80>;


// Класс для абстрактной фигуры, на основе которой сделаны конкретные.
class Figure
{
	Location loc_{ 0, 0 };

public:

//КОНСТРУКТОРЫ

	Figure() = default;
	Figure(int x, int y) : loc_{ x, y } {}
	explicit Figure(const Location & lc) : loc_(lc) {}
	//Виртуальный деструктор.
	virtual ~Figure() {}

	

//ГЕТТЕРЫ

	constexpr const Location where() const { return loc_; }


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

	virtual void moveRight() { ++loc_.x_; }
	virtual void moveLeft() { --loc_.x_; }
	virtual void moveUp() { --loc_.y_; }
	virtual void moveDown() { ++loc_.y_; }

public:

//ДРУГИЕ

	//Чистая виртуальная функция отрисовки фигуры. Делает этот класс абстрактным.
	virtual void print(Frame & ws) const = 0; 
};



// CIRCLE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Circle : public Figure//Наследуется от Figure.
{
	int radius_ = 0;//Радиус круга.

public:

//КОНСТРУКТОРЫ

	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius_(r) { }
	Circle(const Location & lc, size_t r) : Figure(lc), radius_(r) {}
	~Circle() {}

//ГЕТТЕРЫ

	//Получить радиус.
	int get_radius() const { return radius_; }

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
	for (int y = where().y_; y <= where().y_ + 2*radius_; ++y)
	{
		for (int x = where().x_; x <= where().x_ + 2*radius_; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
			{
				if ((x - (where().x_+radius_))*(x - (where().x_+radius_)) + (y - (where().y_+radius_))*(y - (where().y_+radius_)) <= radius_ * radius_)
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
		int a_ = 0;	//Длина меньшей стороны.

	public:

	//КОНСТРУКТОРЫ

		Rectangle(int x, int y, size_t a1) :Figure(x, y), a_(a1) { }
		Rectangle(const Location & lc, size_t a1) : Figure(lc), a_(a1) {}

	//ГЕТТЕРЫ

		//Выдать длину стороны.
		int get_side_length() const { return a_; }

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
	for (int y = where().y_; y <= (where().y_ + a_); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x_; x <= (where().x_ + 1.6*a_); ++x)//Внутренний цикл печатает символы ряда. Большая сторона  увеличена в 1.6 раза.
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
	int diagonal_ = 0;

public:

//КОНСТРУКТОРЫ

	Rhomb() = default;
	Rhomb(int x, int y, size_t diag) : Figure(x, y), diagonal_(diag) {}
	Rhomb(const Location & lc, size_t diag) : Figure(lc), diagonal_(diag) {}
	~Rhomb() {}

//ГЕТТЕРЫ

	//Получить диагональ.
	int get_diagonal() const { return diagonal_; }

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
	for (int y = where().y_; y <= (where().y_+diagonal_/2); ++y)
	{
		for (int x = where().x_; x <= (where().x_ + diagonal_); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= ((where().x_+diagonal_/2) - (y - where().y_)) && x <= (where().x_+diagonal_/2) + (y - where().y_))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	
	if (diagonal_ % 2 != 0)//Случай нечетной длины диагонали. Нужно в связи с ограничениями растрового представления.
	{
		for (int y = where().y_ + diagonal_ / 2-1; y <= (where().y_ + diagonal_-1); ++y)
		{
			for (int x = where().x_+1; x < (where().x_ + diagonal_-1); ++x)
			{
				if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
				{
					if (x-1 >= ((where().x_ + diagonal_ / 2) - (where().y_ + diagonal_ - y)) && x+1 <= ((where().x_ + diagonal_ / 2) + (where().y_ + diagonal_ - y)))
					{
						ws[y][x] = '0';
					}
				}
			}
		}
		return;
	}

	
	for (int y = where().y_+diagonal_/2; y <= (where().y_ + diagonal_); ++y)//Для четной длины диагонали.
	{
		for (int x = where().x_; x < (where().x_ + diagonal_); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x >= ((where().x_+diagonal_/2) - (where().y_ + diagonal_ - y)) && x <= ((where().x_+diagonal_/2) + (where().y_ + diagonal_ - y)))
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
	size_t a_ = 0;//Длина стороны.

public:

	//КОНСТРУКТОРЫ

	Square(int x = 0, int y = 0, size_t a1 = 0) : Figure(x, y), a_(a1) {}
	Square(const Location & lc, size_t a1 = 0) : Figure(lc), a_(a1) {}
	~Square() {}
	
//ГЕТТЕРЫ

	//Выдать длину стороны.
	int get_side_length() const { return a_; }


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

	for (int y = where().y_; y != (where().y_ + a_); ++y)		//Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = where().x_; x != (where().x_ + a_); ++x)	//Внутренний цикл печатает символы ряда
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
	size_t		cathetus_		= 0;		// Длина катета.
	Location	point_A_		{ 0, 0 };	//Координаты вершины с прямым углом.
	Location	point_B_		{ 0, 0 };	//Координаты второй вершины с острым углом. Координаты первой наследуются от Figure. 
	

public:

//КОНСТРУКТОРЫ
	Triangle() = default;
	Triangle(int x, int y, size_t cat) :	Figure(x, y), 
											cathetus_(cat), 
											point_A_{ x, y + static_cast<int>(cathetus_) }, 
											point_B_{ x + static_cast<int>(cathetus_), y + static_cast<int>(cathetus_) }
											{}

	Triangle(const Location & lc, size_t cat) : Figure(lc), 
												cathetus_(cat), 
												point_A_{ lc.x_, lc.y_ + static_cast<int>(cathetus_) }, 
												point_B_{ lc.x_ + static_cast<int>(cathetus_), lc.y_ + static_cast<int>(cathetus_) }
												{}

	~Triangle() {}

//ГЕТТЕРЫ

	//Получить длину катета.
	size_t get_cathetus() const { return cathetus_; }
	//Получить точку А.
	Location get_point_A() const { return point_A_; }
	//Получить точку Б.
	Location get_point_B() const { return point_B_; }


//ДРУГИЕ

	//Переопределение виртуальной функции из базового класса.
	void print(Frame &ws) const; 

	//Отрисовка треугольника для рабочего пространства любого размера.
	template<size_t W, size_t H> 
	void print(array<array<char, W>, H> & ws) const;


	//МЕТОДЫ ДВИЖЕНИЯ

private:

	virtual void moveRight()	{ Figure::moveRight(); point_A_.x_++; point_B_.x_++; }	//Передвинуть правее.
	virtual void moveLeft()		{ Figure::moveLeft(); point_A_.x_--; point_B_.x_--; }	//Передвинуть левее.
	virtual void moveUp()		{ Figure::moveUp(); point_A_.y_--; point_B_.y_--; }		//Передвинуть выше.
	virtual void moveDown()		{ Figure::moveDown(); point_A_.y_++; point_B_.y_++; }	//Передвинуть ниже.

};

//Отрисовка треугольника для рабочего пространства любого размера.
template<size_t W, size_t H> 
void Triangle::print(array<array<char, W>, H> & ws) const
{
	for (int y = where().y_; y <= point_A_.y_; ++y)
	{
		for (int x = where().x_; x <= point_B_.x_; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - where().x_ < y - where().y_)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
