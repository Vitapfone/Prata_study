#include "pch.h"
#include "Link.h"

int Link::counter = 0;//Инициализация счетчика.

//Конструктор с полной спецификацией аргументов.
Link::Link(Image * l_ptr, int l_id, int l_str, Id_string * r_ptr, int r_id, int r_str): left_ptr(l_ptr), left_id(l_id), left_strength(l_str),
		right_ptr(r_ptr), right_id(r_id), right_strength(r_str)
{
	//Обновление счетчика и установка айди.
	++counter;
	id = counter;

	//Запись даты и времени создания.
	const time_t timer = time(0);
	ctime_s(time_date, 26, &timer);
}

//Установить связь с левым объектом.
inline void Link::set_left_obj(Image * l_ptr, int l_id, int l_str)
{
	left_ptr = l_ptr;
	left_id = l_id;
	left_strength = l_str;
}

//Установить связь с правым объектом.
inline void Link::set_right_obj(Id_string * r_ptr, int r_id, int r_str)
{
	right_ptr = r_ptr;
	right_id = r_id;
	right_strength = r_str;
}

//Установить айди.
void Link::set_id(int new_id)
{
	id = new_id;
	if (counter < id)
		counter = id;
}

//Инициализировать информацию о дате и времени создания.
inline void Link::Time_date()
{
	const time_t timer = time(0);
	ctime_s(time_date, 26, &timer);
}


//ДАЛЕЕ ФУНКЦИИ НЕ-ЧЛЕНЫ.

//Записать связь в бинарный файл.
bool Links::bin_write(ofstream & fout, const Link & link)
{
	int id = link.get_id();
	fout.write((char*)&id, sizeof(id));

	const string time_date = link.get_time_date();
	fout.write(time_date.c_str(), 26);

	id = link.get_left_id();
	fout.write((char*)&id, sizeof(id));

	int strength = link.get_left_strength();
	fout.write((char*)&strength, sizeof(strength));

	id = link.get_right_id();
	fout.write((char*)&id, sizeof(id));

	strength = link.get_right_strength();
	fout.write((char*)&strength, sizeof(strength));

	if (fout)//Ели все успешно записано, возвращаем true.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Прочитать связь из бинарного файла.
bool Links::bin_read(ifstream & fin, Link & link)
{
	//Чтение данных во временные переменные.

	int id;
	if (!fin.read((char*)&id, sizeof(id)))
	{
		return false;
	}

	char time_date[26];
	fin.read(time_date, 26);
	int l_id;
	fin.read((char*)&l_id, sizeof(l_id));
	int l_str;
	fin.read((char*)&l_str, sizeof(l_str));
	int r_id;
	fin.read((char*)&r_id, sizeof(r_id));
	int r_str;
	fin.read((char*)&r_str, sizeof(r_str));

	if (!fin)//Если произошел сбой, то сразу возвращаем отказ.
	{
		return false;
	}

	//Установка членов.
	link.set_id(id);
	link.set_time_date(time_date);
	link.set_left_attr(l_id, l_str);
	link.set_right_attr(r_id, r_str);

	return true;
}
