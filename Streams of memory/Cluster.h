#pragma once
#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Warning.h"

using namespace My_names;

using Inner_frame = vector<vector<char>>;

template<size_t W, size_t H>
using Outer_frame = array<array<char, W>, H>;

class Cluster
{
	
	Location	loc_	{ 0, 0 };	//Координаты левого верхнего края кластера.
	size_t		s_		= 5;		//Длина стороны квадратного кластера.
	int			count_	= 0;		//Количество точек, признанных отличными от фона, либо особенных по другому признаку(зависит от контекста).

public:

//КОНСТРУКТОРЫ

	//Задает члены. Count задается неявно по умолчанию нулем.
	Cluster(int x = 0, int y = 0, size_t s1 = 5) : loc_{ x, y }, s_(s1) {}
	Cluster(Location lc, size_t s1 = 5) : loc_(lc), s_(s1) {}

//ГЕТТЕРЫ

	//Возвратить длину стороны.
	size_t get_s()const { return s_; }

	//Возвращает размер кластера.
	int size() const { return s_ * s_; }

	//Возвращает положение
	const Location where() const { return loc_; }

	//Возвращает счетчик точек
	int get_count() const { return count_; }


//СЕТТЕРЫ

	//Задать новые координаты и сбросить счетчик.
	void assign(int x, int y) { loc_.x_ = x; loc_.y_ = y; count_ = 0; }


//ДРУГОЕ

	//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
	template<size_t W, size_t H> 
	void counter(const Outer_frame<W, H> & ws, char background) ;

	//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение. Версия для внутреннего потока.
	void counter(const Inner_frame & ws, char background);

	//Функция подсчитывает точки, состояние которых в двух переданных кадрах отличается.
	template<size_t W, size_t H>
	void diff_counter(const Outer_frame<W,H> & frame_1, const Outer_frame<W,H> & frame_2);

	//Функция выводит значения членов.
	void print() const { cout << loc_.x_ << ", " << loc_.y_ << ", " << count_ << endl; }

};

//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
template<size_t W, size_t H>
void Cluster::counter(const Outer_frame<W,H> & ws, char background)
{
	for (int y = loc_.y_; y != (loc_.y_ + s_); ++y)		//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = loc_.x_; x != (loc_.x_ + s_); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)	//Условие, предостерегающее от выхода за границы массива.
			{
				if (ws[y][x] != background)			//Если эл-т не равен фону,
				{
					++count_;						//то увеличивает счетчик таких эл-тов.
				}
			}
		}
	}
}

//Функция подсчитывает точки, состояние которых в двух переданных кадрах отличается.
template<size_t W, size_t H>
void Cluster::diff_counter(const Outer_frame<W,H> & frame_1, const Outer_frame<W,H> & frame_2)
{
	for (int y = loc_.y_; y != (loc_.y_ + s_); ++y)		//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = loc_.x_; x != (loc_.x_ + s_); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)	//Условие, предостерегающее от выхода за границы массива.
			{
				if (frame_1[y][x] != frame_2[y][x])	//Если соответствующие элементы не равны,
				{
					++count_;						//то увеличивает счетчик таких эл-тов.
				}
			}
		}
	}
}


//Простейший сторожевой алгоритм. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Cluster.h.
template<size_t W, size_t H>
const Warning most_filled_cluster(const Outer_frame<W,H> & ws, char background)
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
	
	//Найти наиболее заполненный кластер.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.get_count() > c2.get_count(); });

	//Вычисляем координаты середины кластера.
	int x = vc[0].where().x_ + vc[0].get_s() / 2;
	int y = vc[0].where().y_ + vc[0].get_s() / 2;

	return Warning("Unidentified contrast object!", { x, y }, vc[0].get_count());
}

//Простейший сторожевой алгоритм. Выдает предупреждение с координатами кластера, в котором больше всего точек, состояние которых изменилось с прошлого кадра.
template<size_t W, size_t H>
const Warning most_difference_in_cluster(const Outer_frame<W,H> & frame_1, const Outer_frame<W,H> & frame_2)
{
	static constexpr double difference_coefficient = 1.2;	//Коэффициент важности для предупреждения о разности в кластере.

	//Создаем кластеры для поиска
	vector<Cluster> vc;

	for (int i = 0; i < H; i += 10)
	{
		for (int j = 0; j < W; j += 10)
		{
			vc.push_back(Cluster(j, i, 10));
		}
	}

	for (auto & e : vc)	//Каждый кластер подсчитывает кол-во знаков, состояние которых изменилось с прошлого кадра.
	{
		e.diff_counter(frame_1, frame_2);
	}

	//Найти кластер с наибольшей разницей.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.get_count() > c2.get_count(); });

	//Вычисляем координаты середины кластера.
	int x = vc[0].where().x_ + vc[0].get_s() / 2;
	int y = vc[0].where().y_ + vc[0].get_s() / 2;

	return Warning("Difference in frames! May be motion.", { x, y }, vc[0].get_count()*difference_coefficient);
}