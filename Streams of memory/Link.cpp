#include "pch.h"
#include "Link.h"

int Link::counter_ = 0;//Инициализация счетчика.

//Конструктор с полной спецификацией аргументов.
Link::Link(Image * l_ptr, int l_id, int l_str, Id_string * r_ptr, int r_id, int r_str): left_ptr_(l_ptr), left_id_(l_id), left_strength_(l_str),
		right_ptr_(r_ptr), right_id(r_id), right_strength_(r_str)
{
	//Обновление счетчика и установка айди.
	++counter_;
	id_ = counter_;

	//Запись даты и времени создания.
	const time_t timer = time(0);
	ctime_s(time_date_, 26, &timer);
}

//Установить связь с левым объектом.
inline void Link::set_left_obj(Image * l_ptr, int l_id, int l_str)
{
	left_ptr_		= l_ptr;
	left_id_		= l_id;
	left_strength_	= l_str;
}

//Установить связь с правым объектом.
inline void Link::set_right_obj(Id_string * r_ptr, int r_id, int r_str)
{
	right_ptr_		= r_ptr;
	right_id		= r_id;
	right_strength_	= r_str;
}

//Установить айди.
inline void Link::set_id(int new_id)
{
	id_ = new_id;
	if (counter_ < id_)
		counter_ = id_;
}

//Инициализировать информацию о дате и времени создания.
inline void Link::Time_date()
{
	const time_t timer = time(0);
	ctime_s(time_date_, 26, &timer);
}

//Записать связь в бинарный файл.
bool Link::bin_write(ofstream & fout) const
{
	fout.write((char*)&id_, sizeof(id_));
	fout.write(time_date_, 26);
	fout.write((char*)&left_id_, sizeof(left_id_));
	fout.write((char*)&left_strength_, sizeof(left_strength_));
	fout.write((char*)&right_id, sizeof(right_id));
	fout.write((char*)&right_strength_, sizeof(right_strength_));

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
bool Link::bin_read(ifstream & fin)
{
	using std::swap;	//Используется прием "copy and swap" для безопасности при исключении.

	Link temp;			//Создается временный объект, с которым и происходят все изменения.

	//Прочитать айди.
	if (!fin.read((char*)&temp.id_, sizeof id_))
	{
		return false;
	}

	fin.read(temp.time_date_, 26);
	fin.read((char*)&temp.left_id_, sizeof(left_id_));
	fin.read((char*)&temp.left_strength_, sizeof(left_strength_));
	fin.read((char*)&temp.right_id, sizeof(right_id));
	fin.read((char*)&temp.right_strength_, sizeof(right_strength_));

	if (!fin)//Если произошел сбой, то сразу возвращаем отказ.
	{
		return false;
	}

	//Если все прошло без исключений, то временный объект обменивается с вызывающим.
	swap(*this, temp);

	//Обновляем счетчик,если надо.
	if (counter_ < id_)
		counter_ = id_;

	return true;
}
