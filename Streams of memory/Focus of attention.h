#pragma once
//#include "Inspector.h"
#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
//#include "Cluster.h"


using namespace My_names;

using Inner_frame = vector<vector<char>>;

//Перечисление для режимов внимания.
enum class Attention_mode{Distributed, Partially_concentrated};

class Focus_of_attention
{
	
	Location	loc			{ 0, 0 };//Координаты фокуса внимания.
	char		background	=' ';	//Фон. По умолчанию пробел, как наиболее вероятный фон.
	char		object		= '0';
	Borders		borders;			//Структура для хранения информации о границах области внимания.

	Attention_mode mode = Attention_mode::Distributed;//Режим внимания. По умолчанию распределенное.

public:
//КОНСТРУКТОР
	 
	Focus_of_attention(int x, int y, const Inner_frame & ws, char back = ' ') : loc{ x, y }, background(back), borders{ 0, static_cast<int>(ws[0].size() - 1), 0, static_cast<int>(ws.size() - 1) } {}

//ЗАПРЕЩЕНО

	//Запрещено копирование
	Focus_of_attention(const Focus_of_attention &) = delete;
	//Запрещено присвоение.
	Focus_of_attention & operator=(const Focus_of_attention &) = delete;

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
	Attention_mode get_mode() const { return mode; }

	//Выдать границы области внимания.
	const Borders get_borders()const { return borders; }

//СЕТТЕРЫ

	//Установить режим частично сосредоточенного внимания.
	void mode_par_con() { mode = Attention_mode::Partially_concentrated; }

	//Установить объект.
	void assign_object(const Inner_frame & ws) { object = ws[loc.y][loc.x]; }

//ДРУГИЕ

	//Обозначить  положение.
	void mark(Inner_frame & ws) { ws[loc.y][loc.x] = '+'; }

	//Переместить.
	void relocate(const Location & new_loc) { loc = new_loc; }

	//Переместить в центр тяжести объекта.
	void to_Weight_Center(const Inner_frame & ws);

	//Задает координаты 9-ти элементарных кластеров вокруг фокуса и возвращает местоположение наиболее заполненного.
	const Location clusterize(const Inner_frame & ws);

	//Пытается передвинуть фокус внутрь объекта.
	bool go_inside(const Inner_frame & ws);

	//Определить границы области, в которой полностью находится объект. Соответственно им установить границы области концентрации внимания.
	//Установить режим частичной концентрации.
	void part_concentrate_to_object(const Inner_frame & ws);
};

