#pragma once
#include "Warning.h"


using namespace My_names;

struct Cluster
{
	int xC = 0, yC = 0;//Координаты левого верхнего края кластера.
	int s = 5; //Длина стороны квадратного кластера.
	int count = 0; //Количество точек, признанных отличными от фона.

	//КОНСТРУКТОРЫ

	//Задает члены. Count задается неявно по умолчанию нулем.
	Cluster(int x = 0, int y = 0, int s1 = 5) :xC(x), yC(y), s(s1) {}


	//Возвращает размер кластера.
	int size() { return s * s; }

	//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
	template<size_t W, size_t H>  void counter(array<array<char, W>, H> &ws, char background);

	//Функция выводит значения членов.
	void print() const { cout << xC << ", " << yC << ", " << count << endl; }

	//Задать новые координаты и сбросить счетчик.
	void assign(int x, int y) { xC = x; yC = y; count = 0; }
};

//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
template<size_t W, size_t H>
void Cluster::counter(array<array<char, W>, H> &ws, char background)
{
	//cout << "Counting... " << endl;
	for (int y = yC; y != (yC + s); ++y)//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = xC; x != (xC + s); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				if (ws[y][x] != background)//Если эл-т не равен фону,
				{
					++count;//то увеличивает счетчик таких эл-тов.
				}
			}
		}
	}
}


//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Cluster.h.
template<size_t W, size_t H>
Warning most_filled_cluster(array<array<char, W>, H> &ws, char background)
{
	//Создаем кластеры для поиска
	vector<Cluster> vc;

	for (int i = 0; i < H; i += 10)
	{
		for (int j = 0; j < W; j += 10)
		{
			vc.push_back(Cluster(j, i, 10));
		}
	}

	for (auto & e : vc)//Каждый кластер подсчитывает кол-во знаков, отличных от фона.
	{
		e.counter(ws, background);
	}
	cout << "After cluster counting" << endl;

	//Найти наиболее заполненный кластер.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.count > c2.count; });

	//Вычисляем координаты середины кластера.
	int x = vc[0].xC + vc[0].s / 2;
	int y = vc[0].yC + vc[0].s / 2;

	return Warning("Unidentified contrast object!", { x, y }, 10);
}