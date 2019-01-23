﻿#pragma once
#include "Inspector.h"

using namespace My_names;

enum Attention_mode{Distributed, Partially_concentrated};

class Focus_of_attention
{
	//Координаты фокуса внимания.
	Location loc{ 0, 0 };

	char background =' ';//Фон. По умолчанию пробел, как наиболее вероятный фон.
	char object = '0';
	Attention_mode mode = Distributed;//Режим внимания. По умолчанию распределенное.

	Borders borders;//Структура для хранения информации о границах области внимания.

public:
	//КОНСТРУКТОР
	template<size_t W, size_t H> Focus_of_attention(int x, int y, array<array<char, W>, H> & ws) : loc{ x, y }, background(ws[y][x]), borders{ 0, W - 1, 0, H - 1 } {}


	//ГЕТТЕРЫ

	//Выдать фон
	char get_background() const { return background; }

	//Выдать объект
	char get_object() const { return object; }

	//Выдать X.
	int get_x() const { return loc.x; }

	//Выдать Y.
	int get_y() const { return loc.y; }

	//Выдать режим
	int get_mode() const { return mode; }

	//Выдать границы области внимания.
	Borders get_borders()const { return borders; }

	//СЕТТЕРЫ

	//Установить режим частично сосредоточенного внимания.
	void mode_par_con() { mode = Partially_concentrated; }

	//Установить объект.
	template<size_t W, size_t H> 
	void assign_object(array<array<char, W>, H> &ws) { object = ws[loc.y][loc.x]; }



	//Обозначить  положение.
	template<size_t W, size_t H> 
	void mark(array<array<char, W>, H> & ws) { ws[loc.y][loc.x] = '+'; }

	//Переместить.
	void relocate(const Location & new_loc) { loc = new_loc; }

	//Переместить в центр тяжести объекта.
	template<size_t W, size_t H>  
	void to_Weight_Center(array<array<char, W>, H> & ws);

	//Задает координаты 9-ти элементарных кластеров вокруг фокуса.
	template<size_t W, size_t H> 
	Cluster clusterize(array<array<char, W>, H> & ws);

	//Пытается передвинуть фокус внутрь объекта.
	template<size_t W, size_t H> 
	bool go_inside(array<array<char, W>, H> & ws);

	//Определить границы области, в которой полностью находится объект. Соответственно им установить границы области концентрации внимания.
	//Установить режим частичной концентрации.
	template<size_t W, size_t H>
	void part_concentrate_to_object(array<array<char, W>, H> & ws);

};

//Функция переместит фокус внимания в примерный центр тяжести объекта.
template<size_t W, size_t H>  
void Focus_of_attention::to_Weight_Center(array<array<char, W>, H> & ws)
{
	bool foc_move_up = false;//Переменная, показывающая, что фокус уже передвигался вверх.
	bool foc_move_down = false;//Переменная, показывающая, что фокус уже передвигался вниз.
	int upCount = 0;//Счетчик пикселей объекта выше фокуса.
	int downCount = 0;//Счетчик пикселей объекта ниже фокуса.

	while ((foc_move_up == false) || (foc_move_down == false))//Пока фокус не двигался в обе стороны.
	{

		upCount = 0;//Считаем пиксели выше фокуса.
		for (int y = borders.y_min; y < loc.y; ++y)
		{
			for (int x = borders.x_min; x <= borders.x_max; ++x)
			{
				if (ws[y][x] == object)
				{
					++upCount;
				}
			}
		}

		downCount = 0;//Считаем ниже.
		for (int y = loc.y + 1; y <= borders.y_max; ++y)
		{
			for (int x = borders.x_min; x <= borders.x_max; ++x)
			{
				if (ws[y][x] == object)
				{
					++downCount;
				}
			}
		}
		if (upCount > downCount)//Если выше пикселей больше,
		{
			--loc.y;//то передвигаем фокус вверх
			foc_move_up = true;//Теперь фокус двигался вверх.
		}
		else if (upCount < downCount)//Если меньше --
		{
				++loc.y;//передвигаем вниз.
				foc_move_down = true;//Теперь фокус двигался вниз.
		}
		else//Если выше и ниже пикселей одинаково,
		{
				break;//то центр найден и цикл надо завершить.
		}
	}
	cout << "upCount: " << upCount << " downCount " << downCount << endl;

	bool foc_move_left = false;//Переменная, показывающая, что фокус уже передвигался влево.
	bool foc_move_right = false;//Переменная, показывающая, что фокус уже передвигался вправо.
	int leftCount = 0;//Счетчик пикселей объекта левее фокуса.
	int rightCount = 0;//Счетчик пикселей объекта правее фокуса.

	while ((foc_move_left == false) || (foc_move_right == false))//Все аналогично действиям для игреков.
	{

		leftCount = 0;
		for (int x = borders.x_min; x < loc.x; ++x)
		{
			for (int y = borders.y_min; y <= borders.y_max; ++y)
			{
				if (ws[y][x] == object)
				{
					++leftCount;
				}
			}
		}

		rightCount = 0;
		for (int x = loc.x + 1; x <= borders.x_max; ++x)
		{
			for (int y = borders.y_min; y <= borders.y_max; ++y)
			{
				if (ws[y][x] == object)
				{
					++rightCount;
				}
			}
		}
		if (leftCount > rightCount)
		{
			--loc.x;
			foc_move_left = true;
		}
		else if (leftCount < rightCount)
		{
			++loc.x;
			foc_move_right = true;
		}
		else
		{
			break;
		}
	}
	cout << "leftCount: " << leftCount << " rightCount " << rightCount << endl;
}

//Задает координаты 9-ти элементарных кластеров вокруг фокуса.
template<size_t W, size_t H> 
Cluster Focus_of_attention::clusterize(array<array<char, W>, H> & ws)
{
	Cluster cl5(loc.x - 2, loc.y - 2);
	Cluster cl4(loc.x - 7, loc.y - 2);
	Cluster cl6(loc.x + 3, loc.y - 2);
	Cluster cl8(loc.x - 2, loc.y + 3);
	Cluster cl7(loc.x - 7, loc.y + 3);
	Cluster cl9(loc.x + 3, loc.y + 3);
	Cluster cl1(loc.x - 7, loc.y - 7);
	Cluster cl2(loc.x - 2, loc.y - 7);
	Cluster cl3(loc.x + 3, loc.y - 7);

	vector<Cluster> vcl{ cl1, cl2, cl3, cl4, cl5, cl6, cl7, cl8, cl9 };

	for (auto & e : vcl)//Каждый кластер подсчитывает кол-во знаков, отличных от фона.
	{
		e.counter(ws, background);
	}
	//Ищем наиболее заполненный.
	sort(vcl.begin(), vcl.end(), [](Cluster & c1, Cluster & c2) {return c1.count > c2.count; });

	//Возвращаем его.
	return vcl[0];
}

//Пытается передвинуть фокус внутрь объекта.
template<size_t W, size_t H>
bool Focus_of_attention::go_inside(array<array<char, W>, H>& ws)
{
	Cluster fcl = clusterize(ws);//Получаем наиболее заполненный элементарный кластер.
	Location center = { fcl.xC + 3, fcl.yC + 3 }; //Середина этого кластера.
	relocate(center); //Передвигаем фокус. 

	if (ws[loc.y][loc.x] == background)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//Определить границы области, в которой полностью находится объект. Соответственно им установить границы области концентрации внимания.
//Установить режим частичной концентрации.
template<size_t W, size_t H>
void Focus_of_attention::part_concentrate_to_object(array<array<char, W>, H>& ws)
{
	Inspector ins(loc.x, loc.y, background, object);//Создаем инспектора для обхода по контуру.

	Borders object_area = ins.left_inspect(ws, 1);//Обходим фигуру по часовой стрелке, начиная с левого края. Получаем точные габариты в виде структуры, где указано, в каком диапазоне координат 
														// содержится наша фигура.
	cout << "\nAfter inspecting..." << endl;

	//Границы устанавливаются по результатам обхода.
	borders = object_area;

	//Положение центра объекта.
	Location center = { (borders.x_max + borders.x_min) / 2, (borders.y_max + borders.y_min) / 2 };
	relocate(center); //Перенесем фокус внимания в центр области, занимаемой объектом

	//режим внимания меняется на частично сконцентрированный.
	mode = Partially_concentrated;
}
