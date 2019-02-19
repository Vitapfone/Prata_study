#pragma once

#include "Image.h"

class Link
{
	int id = 0;//Идентификатор самой связи.
	static int counter;//Статический счетчик для получения уникальных айди.

	char time_date[26] = { '\0' };//Время и дата создания связи.

	Image* left_ptr = nullptr;//Указатель на левый объект.
	int left_id = 0;//Айди этого объекта.
	int left_strength = 0;//Сила связи для него.

	Id_string* right_ptr = nullptr;//Указатель на правый объект.
	int right_id = 0;
	int right_strength = 0;

public:

//КОНСТРУКТОРЫ

	Link() = default;
	//Конструктор с полной спецификацией аргументов.
	Link(Image* l_ptr, int l_id, int l_str, Id_string* r_ptr, int r_id, int r_str); 
	

//МЕТОДЫ

//ГЕТТЕРЫ

	//Выдать идентификатор
	int get_id() const { return id; }
	//Выдать значение счетчика.
	int get_counter() const{ return counter; }
	//Выдать информацию о дате и времени создания.
	const string get_time_date() const { return time_date; }

	//Выдать указатель на левый объект.
	Image* get_left_ptr() const { return left_ptr; }
	//Выдать левый идентификатор.
	int get_left_id() const { return left_id; }
	//Выдать левую силу.
	int get_left_strength() const { return left_strength; }

	//Выдать указатель на правый объект.
	Id_string* get_right_ptr() const { return right_ptr; }
	//Выдать правый идентификатор.
	int get_right_id() const{ return right_id; }
	//Выдать правую силу.
	int get_right_strength() const { return right_strength; }

//СЕТТЕРЫ

	//Установить связь с левым объектом.
	void set_left_obj(Image* l_ptr, int l_id, int l_str);
	//Установить указатель на левый объект.
	void set_left_ptr(Image* l_ptr) { left_ptr = l_ptr; }
	//Установить атрибуты левого объекта
	void set_left_attr(int l_id, int l_str) { left_id = l_id; left_strength = l_str; }

	//Установить связь с правым объектом.
	void set_right_obj(Id_string* r_ptr, int r_id, int r_str);
	//Установить указатель на правый объект.
	void set_right_ptr(Id_string* r_ptr) { right_ptr = r_ptr; }
	//Установить атрибуты правого объекта.
	void set_right_attr(int r_id, int r_str) { right_id = r_id; right_strength = r_str; }

	//Установить айди.
	void set_id(int new_id);
	//Установить счетчик.
	void set_counter(int new_counter) { counter = new_counter; }
	//Инициализировать информацию о дате и времени создания.
	void Time_date();
	//Установить информацию о дате и времени создания.
	void set_time_date(const string & t_d) { strcpy_s(time_date, 26, t_d.c_str()); }
	void set_time_date(const char* t_d){ strcpy_s(time_date, 26, t_d); }
};


//НЕ ЧЛЕНЫ

namespace Links
{
	//Записать связь в бинарный файл.
	bool bin_write(ofstream & fout, const Link & link);

	//Прочитать связь из бинарного файла.
	bool bin_read(ifstream & fin, Link & link);
}