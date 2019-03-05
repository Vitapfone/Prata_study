#pragma once
#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"

using namespace My_names;

class Warning //Класс сообщения от функций первичного управления вниманием.
{
	string		message_;				//Сообщение о типе обнаруженного.
	Location	loc_			{ 0, 0 };	//Координаты обнаруженного.
	int			importance_		= 10;		//Степень важности сообщения.

public:

//КОНСТРУКТОРЫ

	Warning() = default;
	Warning(const string & mes, const Location & l, int imp) : message_(mes), loc_(l), importance_(imp) {}
	~Warning() {}

//МЕТОДЫ

//ГЕТТЕРЫ

	//Возвратить местоположение обнаруженного.
	const Location where() const { return loc_; }

	//Возвратить важность.
	int get_importance()const { return importance_; }

//ДРУГИЕ

	//Вывести отладочное сообщение.
	void what() const;
};

