#include "pch.h"
#include "My_names.h"
#include "Id_string.h"

int Id_string::counter = 0;//Инициализация не константного статического члена должна быть в его определении в области видимости файла.

//Заполнить строку и айдишник из бин. файла.
void Id_string::init(ifstream & fin, size_t len)
{
	//Выделяем под нее память. Для работы с массивом это должно быть отражено в параметре шаблона.
	unique_ptr<char[]> buf(new char[len]);
	
	fin.read(buf.get(), len);//Читаем в эту память.
	data.assign(buf.get());//Присваиваем содержимое буфера строке.

	//Читаем id.
	fin.read((char*)&id, sizeof id);

	if (counter < id)
		counter = id;
}

//Конструктор из бинарного файла.
Id_string::Id_string(ifstream & fin)
{
	size_t len;
	fin.read((char*)&len, sizeof len);

	init(fin, len);//Заполнить все остальное.
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
	using std::swap;//Используется прием "copy and swap" для безопасности при исключении.

	Id_string temp;//Создается временный объект, с которым и происходят все изменения.

	//Читаем длину строки.
	size_t len;
	if (!fin.read((char*)&len, sizeof len))//Если чтение неудачное (конец файла),
	{
		return false;//то возвращаем false.
	}

	try
	{
		temp.init(fin, len);//Заполнить все остальное.
	}
	catch (std::bad_alloc & ex)//Если будет исключение, то чтение файла откатится назад к началу записи об этой строке.
	{
		cerr << ex.what() << endl;
		int l = sizeof len;
		fin.seekg(-l, ifstream::cur);
		return false;
	}

	swap(*this, temp);//Если все прошло без исключений, то временный объект обменивается с вызывающим.

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
ostream & operator<<(ostream & os, const Id_string & ids)
{
	os << ids.get_data() << "\n" << ids.get_id() << endl;
	return os;
}

//Оператор для чтения из текстового файла.
istream & operator>>(istream & is, Id_string & ids)
{
	std::getline(is, ids.get_data());
	is>>ids.get_id();
	is.ignore(1, '\n');
	if (ids.get_counter() < ids.get_id())
		ids.get_counter() = ids.get_id();
	return is;
}
