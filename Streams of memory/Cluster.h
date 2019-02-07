#pragma once
//#include "Warning.h"


using namespace My_names;

class Cluster
{
	
	Location loc{ 0, 0 };//Координаты левого верхнего края кластера.
	size_t s = 5; //Длина стороны квадратного кластера.
	int count = 0; //Количество точек, признанных отличными от фона, либо особенных по другому признаку(зависит от контекста).

public:

//КОНСТРУКТОРЫ

	//Задает члены. Count задается неявно по умолчанию нулем.
	Cluster(int x = 0, int y = 0, size_t s1 = 5) : loc{ x, y }, s(s1) {}
	Cluster(Location lc, size_t s1 = 5) : loc(lc), s(s1) {}

//ЗАПРЕЩЕНО

	//Копирование запрещено.
	//Cluster(const Cluster & other) = delete;//При заперещении копирования оказывается, что объект нельлзя поместить в контейнер.
	//Такое представляется целесообразным только для уникальных объектов типа фокуса внимания.

	//Присваивание запрещено.
	//Cluster & operator=(const Cluster &) = delete;//При запрещении присваивания становятся невозможными алгоритмы, изменяющие содержимое контейнеров с такими объектами.
	//Пойдет для уникальных объектов.

//ГЕТТЕРЫ

	//Возвратить длину стороны.
	size_t get_s()const { return s; }

	//Возвращает размер кластера.
	int size() const { return s * s; }

	//Возвращает положение
	const Location where() const { return loc; }

	//Возвращает счетчик точек
	int get_count() const { return count; }


//СЕТТЕРЫ

	//Задать новые координаты и сбросить счетчик.
	void assign(int x, int y) { loc.x = x; loc.y = y; count = 0; }


//ДРУГОЕ

	

	//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
	template<size_t W, size_t H> 
	void counter(const array<array<char, W>, H> & ws, char background) ;

	//Функция подсчитывает точки, состояние которых в двух переданных кадрах отличается.
	template<size_t W, size_t H>
	void diff_counter(const array<array<char, W>, H> & frame_1, const array<array<char, W>, H> & frame_2);

	//Функция выводит значения членов.
	void print() const { cout << loc.x << ", " << loc.y << ", " << count << endl; }

};

//Функция подсчитывает количество точек в кластере, содержащих отличное от фона значение.
template<size_t W, size_t H>
void Cluster::counter(const array<array<char, W>, H> & ws, char background)
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

//Функция подсчитывает точки, состояние которых в двух переданных кадрах отличается.
template<size_t W, size_t H>
void Cluster::diff_counter(const array<array<char, W>, H> & frame_1, const array<array<char, W>, H> & frame_2)
{
	for (int y = loc.y; y != (loc.y + s); ++y)//Перебирает все эл-ты рабочего пространства в границах квадратного кластера.
	{
		for (int x = loc.x; x != (loc.x + s); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предостерегающее от выхода за границы массива.
			{
				if (frame_1[y][x] != frame_2[y][x])//Если соответствующие элементы не равны,
				{
					++count;//то увеличивает счетчик таких эл-тов.
				}
			}
		}
	}
}


//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Cluster.h.
template<size_t W, size_t H>
const Warning most_filled_cluster(const array<array<char, W>, H> & ws, char background)
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
	//cout << "After cluster counting" << endl;

	//Найти наиболее заполненный кластер.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.get_count() > c2.get_count(); });

	//Вычисляем координаты середины кластера.
	int x = vc[0].where().x + vc[0].get_s() / 2;
	int y = vc[0].where().y + vc[0].get_s() / 2;

	//cout << vc[0].get_count() << " Bacground '" << background << "'\n";

	return Warning("Unidentified contrast object!", { x, y }, vc[0].get_count());
}

//Простейшая ф-я управления вниманием. Выдает предупреждение с координатами кластера, в котором больше всего точек, состояние которых изменилось с прошлого кадра.
template<size_t W, size_t H>
const Warning most_difference_in_cluster(const array<array<char, W>, H> & frame_1, const array<array<char, W>, H> & frame_2)
{
	static constexpr double difference_coefficient = 1.2;//Коэффициент важности для предупреждения о разности в кластере.

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
		e.diff_counter(frame_1, frame_2);
	}

	//Найти кластер с наибольшей разницей.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.get_count() > c2.get_count(); });

	//Вычисляем координаты середины кластера.
	int x = vc[0].where().x + vc[0].get_s() / 2;
	int y = vc[0].where().y + vc[0].get_s() / 2;

	return Warning("Difference in frames! May be motion.", { x, y }, vc[0].get_count()*difference_coefficient);
}