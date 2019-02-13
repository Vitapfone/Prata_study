#pragma once
//#include "My_names.h"
using namespace My_names;

class Id_string
{
public:
//КОНСТРУКТОРЫ

	Id_string() = default;
	//Конструктор из строки.
	Id_string(const string & s) :data(s) { ++counter; id = counter;/* cout << id<< endl; */}
	//Конструктор из строки и id.
	Id_string(const string & s, int id):data(s), id(id)
	{
		if (counter < id)
			counter = id;
	}
	//конструктор из бинарного файла.
	Id_string(ifstream &);
	~Id_string() {}

//МЕТОДЫ

//ГЕТТЕРЫ

	const string get_data() const { return data; }//Выдать копию хранимой строки.
	string & get_data() { return data; }

	int get_id() const { return id; }//Выдать идентификатор.
	int & get_id() { return id; }

	int get_counter() const { return counter; }//Выдать счетчик
	int & get_counter() { return counter; }

	//Записать в бинарный файл.
	bool bin_write(ofstream & fout)const;

private:
	//Заполнить строку и айдишник из бин. файла.
	void init(ifstream & fin, size_t l);

public:
	//Прочитать из бинарного файла.
	bool bin_read(ifstream & fin);

private:
	
	string data;
	int id = 0;
	static int counter;//Не константный статический член нельзя инициализировать в классе.

};

//Оператор вывода для записи в текстовый файл.
ostream & operator<< (ostream &, const Id_string &);

//Оператор ввода из текстового файла.
istream & operator>>(istream &, Id_string &);