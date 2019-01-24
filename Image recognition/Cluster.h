#pragma once
#include "Warning.h"


using namespace My_names;

class Cluster
{
	
	Location loc{ 0, 0 };//Координаты левого верхнего края кластера.
	int s = 5; //Длина стороны квадратного кластера.
	int count = 0; //Количество точек, признанных отличными от фона.

public:

//КОНСТРУКТОРЫ

	//Задает члены. Count задается неявно по умолчанию нулем.
	Cluster(int x = 0, int y = 0, int s1 = 5) : loc{ x, y }, s(s1) {}
	Cluster(Location lc, int s1 = 5) : loc(lc), s(s1) {}

//ЗАПРЕЩЕНО

	//Копирование запрещено.
	//Cluster(const Cluster & other) = delete;//При заперещении копирования оказывается, что объект нельлзя поместить в контейнер.
	//Такое представляется целесообразным только для уникальных объектов типа фокуса внимания.

	//Присваивание запрещено.
	//Cluster & operator=(const Cluster &) = delete;//При запрещении присваивания становятся невозможными алгоритмы, изменяющие содержимое контейнеров с такими объектами.
	//Пойдет для уникальных объектов.

//ГЕТТЕРЫ

	//Возвращает размер кластера.
	int size() const { return s * s; }

	//Возвращает положение
	Location where() const { return loc; }

	//Возвращает счетчик точек
	int Count() const { return count; }


//СЕТТЕРЫ

	//Задать новые координаты и сбросить счетчик.
	void assign(int x, int y) { loc.x = x; loc.y = y; count = 0; }


	//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
	template<size_t W, size_t H>  void counter(array<array<char, W>, H> &ws, char background);

	//Функция выводит значения членов.
	void print() const { cout << loc.x << ", " << loc.y << ", " << count << endl; }

	

//ДРУЗЬЯ

	//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Cluster.h.
	template<size_t W, size_t H>
	friend Warning most_filled_cluster(array<array<char, W>, H> &ws, char background);

};

//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
template<size_t W, size_t H>
void Cluster::counter(array<array<char, W>, H> &ws, char background)
{
	//cout << "Counting... " << endl;
	for (int y = loc.y; y != (loc.y + s); ++y)//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = loc.x; x != (loc.x + s); ++x)
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
	int x = vc[0].loc.x + vc[0].s / 2;
	int y = vc[0].loc.y + vc[0].s / 2;

	return Warning("Unidentified contrast object!", { x, y }, 10);
}