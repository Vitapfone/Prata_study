#pragma once
#include "My_names.h"
using namespace My_names;

class Id_string
{
public:
	//КОНСТРУКТОРЫ
	Id_string() = default;
	//Конструктор из строки.
	Id_string(const string &s) :data(s) { ++counter; id = counter;/* cout << id<< endl; */}
	//Конструктор из строки и id.
	Id_string(const string &s, int id):data(s), id(id)
	{
		if (counter < id)
			counter = id;
	}
	//конструктор из бинарного файла.
	Id_string(ifstream &);
	~Id_string() {}

	//МЕТОДЫ
	string get_data() const { return data; }//Выдать копию хранимой строки.
	int get_id() const { return id; }//Выдать идентификатор.

	//Записать в бинарный файл.
	bool bin_write(ofstream & fout)const;

	//Прочитать из бинарного файла.
	bool bin_read(ifstream & fin);

	//ФУНКЦИИ-ДРУЗЬЯ.

	//Оператор вывода для записи в текстовый файл.
	friend ostream& operator<< (ostream &, const Id_string &);

	friend istream& operator>>(istream&, Id_string &);

private:
	
	string data;
	int id = 0;
	static int counter;

};

