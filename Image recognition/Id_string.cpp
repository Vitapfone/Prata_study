﻿#include "pch.h"
#include "Id_string.h"

int Id_string::counter = 0;//Инициализация не константного статического члена должна быть в его определении в области видимости файла.

//Конструктор из бинарного файла.
Id_string::Id_string(ifstream & fin)
{
	
	size_t len;
	fin.read((char*)&len, sizeof len);

	shared_ptr<char> buf(new char[len]);
	fin.read(buf.get(), len);
	data.assign(buf.get());
	

	fin.read((char*)&id, sizeof id);

	if (counter < id)
		counter = id;
}

//Записать в бинарный файл.
bool Id_string::bin_write(ofstream & fout) const
{
	size_t len = data.size() + 1;//Получаем размер строки, хранимой объектом.
	fout.write((char*)&len, sizeof len);//Записываем этот размер.
	fout.write(data.c_str(), len);//Записываем саму строку.
	fout.write((char*)&id, sizeof id);//Записываем id.

	if (fout)//Ели все успешно записано, возвращаем true.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Прочитать из бинарного файла.
bool Id_string::bin_read(ifstream & fin)
{
	//Читаем длину строки.
	size_t len;
	if (!fin.read((char*)&len, sizeof len))//Если чтение неудачное (конец файла),
	{
		return false;//то возвращаем false.
	}

	//cout <<"LEN "<< len << endl;

	//Выделяем под нее память.
	shared_ptr<char> buf(new char[len]);
	
	fin.read(buf.get(), len);//Читаем в эту память.
	data.assign(buf.get());//Присваиваем содержимое буфера строке.
	
	//Читаем id.
	fin.read((char*)&id, sizeof id);

	if (counter < id)
		counter = id;

	if (fin)//Если все прочитано успешно, то возвращаем true.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Оператор вывода для записи в текстовый файл.
ostream & operator<<(ostream &os, const Id_string &ids)
{
	os << ids.data << "\n" << ids.id << endl;
	return os;
}

//Оператор для чтения из текстового файла.
istream & operator>>(istream &is, Id_string & ids)
{
	std::getline(is, ids.data);
	is>>ids.id;
	is.ignore(1, '\n');
	if (Id_string::counter < ids.id)
		Id_string::counter = ids.id;
	return is;
}
