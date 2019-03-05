#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

enum class Link_side { no, left, right }; //Перечисление для определения стороны связи, к которой прикреплена эта строка.

class Link;//Предварительное объявление для класса связи.

struct Link_ptr //Структура для представления нумерованной связи объекта. Id_string.h
{
	Link* pl_		= nullptr;		 //Указатель, имитирующий некую информативную связь объекта строки.
	Link_side ls_	= Link_side::no; //Маркер стороны связи. Указывает, к какой стороне связи присоединена строка. По умолчанию ни к какой.
	int id_			= 0;			 //Идентификатор для этого указателя, позволит потом найти этот образ.
};

class Id_string
{
public:
//КОНСТРУКТОРЫ

	Id_string() = default;
	//Конструктор из строки.
	Id_string(const string & s) :data_(s) { ++counter_; id_ = counter_; }
	//Конструктор из строки и id_.
	Id_string(const string & s, int id):data_(s), id_(id)
	{
		if (counter_ < id_)
			counter_ = id_;
	}
	
	~Id_string() {}

//МЕТОДЫ

//ГЕТТЕРЫ

	const string	get_data() const	{ return data_; }	//Выдать копию хранимой строки.
	string &		get_data()			{ return data_; }

	int		get_id() const	{ return id_; }	//Выдать идентификатор.
	int &	get_id()		{ return id_; }

	int		get_counter() const { return counter_; }	//Выдать счетчик
	int &	get_counter()		{ return counter_; }


	//Выдать айди связи.
	int get_link_id()const { return im_link_.id_; }
	//Выдать маркер стороны.
	Link_side get_ls()const { return im_link_.ls_; }

	const Link_ptr get_im_link() const { return im_link_; }//Выдать связь.

//СЕТТЕРЫ

	//Установить связь.
	void	set_is_link(Link* is)				{ im_link_.pl_ = is; }	
	void	set_is_link(Link_ptr const & other) { im_link_ = other; }

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
	
	string		data_;
	int			id_		= 0;
	static int	counter_;//Не константный статический член нельзя инициализировать в классе.

	Link_ptr	im_link_;//Связь для некоего образа.
};

//Оператор вывода.
ostream & operator<< (ostream &, const Id_string &);

////Оператор ввода из текстового файла.
//istream & operator>>(istream &, Id_string &);