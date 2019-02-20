#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

enum class Link_side { no, left, right }; //Перечисление для определения стороны связи, к которой прикреплена эта строка.

class Link;//Предварительное объявление для класса связи.

struct Link_ptr //Структура для представления нумерованной связи объекта. Id_string.h
{
	Link* pl		= nullptr;		 //Указатель, имитирующий некую информативную связь объекта строки.
	Link_side ls	= Link_side::no; //Маркер стороны связи. Указывает, к какой стороне связи присоединена строка. По умолчанию ни к какой.
	int id			= 0;			 //Идентификатор для этого указателя, позволит потом найти этот образ.
};

class Id_string
{
public:
//КОНСТРУКТОРЫ

	Id_string() = default;
	//Конструктор из строки.
	Id_string(const string & s) :data(s) { ++counter; id = counter; }
	//Конструктор из строки и id.
	Id_string(const string & s, int id):data(s), id(id)
	{
		if (counter < id)
			counter = id;
	}
	
	~Id_string() {}

//МЕТОДЫ

//ГЕТТЕРЫ

	const string	get_data() const	{ return data; }	//Выдать копию хранимой строки.
	string &		get_data()			{ return data; }

	int		get_id() const	{ return id; }	//Выдать идентификатор.
	int &	get_id()		{ return id; }

	int		get_counter() const { return counter; }	//Выдать счетчик
	int &	get_counter()		{ return counter; }

	//Выдать айди связи.
	int get_link_id()const { return im_link.id; }
	//Выдать маркер стороны.
	Link_side get_ls()const { return im_link.ls; }

	const Link_ptr get_im_link() const { return im_link; }//Выдать связь.

//СЕТТЕРЫ

	void	set_is_link(Link* is)				{ im_link.pl = is; }	//Установить связь.
	void	set_is_link(Link_ptr const & other) { im_link = other; }


//ДРУГИЕ

	//Записать в бинарный файл.
	bool bin_write(ofstream & fout)const;

private:
	//Заполнить строку и айдишник из бин. файла.
	void init(ifstream & fin, size_t l);

public:
	//Прочитать из бинарного файла.
	bool bin_read(ifstream & fin);

private:
	
	string		data;
	int			id		= 0;
	static int	counter;//Не константный статический член нельзя инициализировать в классе.

	Link_ptr	im_link;//Связь для некоего образа.
};

//Оператор вывода.
ostream & operator<< (ostream &, const Id_string &);

////Оператор ввода из текстового файла.
//istream & operator>>(istream &, Id_string &);