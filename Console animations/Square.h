#pragma once
// Здесь будет находиться класс квадрата для отображения в консольной анимации.
using std::vector;
using std::array;

using Ar60_30 = array<array<char, 60>, 30>;

struct Square
{
	int x0=0, y0=0;//Координаты левого верхнего угла квадрата.
	unsigned a = 0;//Длина стороны.

	vector<vector<char>> vision;//Область "зрения" квадрата.
private:
	//Функция делает видимыми границы области зрения.
	void make_border();

	//Функция смотрит в область зрения и определяет приближение границы рабочей области.
	bool see_border();

public:
	//Функция вывода в консоль области зрения.
	void print_vis();


	//Функция реализации зрения. Присваивает значения эл-тов рабочего пространства эл-там области зрения.
	void see_you(Ar60_30 &, int);

	Square(int x = 0, int y = 0, unsigned a1 = 0); //Конструктор.


	//МЕТОДЫ ДВИЖЕНИЯ

	void moveRight() { ++x0; }//Передвинуть правее.
	void moveLeft() { --x0; }//Передвинуть левее.
	void moveUp() { --y0; }//Передвинуть выше.
	void moveDown() { ++y0; }//Передвинуть ниже.

	int program_move(vector<int> &);//Функция запрограммированного движения, принимающая в качестве программы вектор целых чисел. Возвращающая текущее движение в программе.


	vector<int>::iterator correct_replace(vector<int>::iterator act, vector<int> &pr); //Функция коррекции заменой.

	//vector<int>::iterator correct_plus(vector<int>::iterator act, vector<int> &pr);// Функция коррекции программы положительного типа, т.е. добавляющая эл-ты в вектор.
	//vector<int>::iterator correct_minus(vector<int>::iterator act, vector<int> &pr); //Функция отрицательной коррекции, удаляющая эл-ты из программы.

	
	void printSquare(Ar60_30 &ar);//Функция отрисовки квадрата.
};