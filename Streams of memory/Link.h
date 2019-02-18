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
	//Установить связь с правым объектом.
	void set_right_obj(Id_string* r_ptr, int r_id, int r_str);
	//Установить айди.
	void set_id(int new_id) {id=new_id;}
	//Инициализировать информацию о дате и времени создания.
	void Time_date();
};


//НЕ ЧЛЕНЫ
namespace Links
{
	//Записать связь в бинарный файл.
	bool bin_write(ofstream & fout, const Link & link);

	//Прочитать связь из бинарного файла.
	bool bin_read(ifstream & fin, Link & link);
}