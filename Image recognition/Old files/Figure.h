#pragma once
using std::array;
using Ar60_30 = array<array<char, 60>, 30>;

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