#include "pch.h"
#include "Id_string.h"

int Id_string::counter = 0;	//Инициализация не константного статического члена должна быть в его определении в области видимости файла.

//Заполнить строку и айдишник из бин. файла.
void Id_string::init(ifstream & fin, size_t len)
{
	
	//Выделяем под нее память. Для работы с массивом это должно быть отражено в параметре шаблона.
	auto buf = make_unique<char[]>(len);
	//Читаем в эту память.
	fin.read(buf.get(), len);
	//Присваиваем содержимое буфера строке.
	data.assign(buf.get());

	//Прочитать айди связи.
	fin.read((char*)&im_link.id, sizeof im_link.id);
	//Прочитать маркер стороны связи.
	fin.read((char*)&im_link.ls, sizeof im_link.ls);
}

////Конструктор из бинарного файла.
//Id_string::Id_string(ifstream & fin)
//{
//	size_t len;
//	fin.read((char*)&len, sizeof len);
//
//	init(fin, len);//Заполнить все остальное.
//}

//Записать в бинарный файл.
bool Id_string::bin_write(ofstream & fout) const
{
	//Записываем id.
	fout.write((char*)&id, sizeof id);
	
	//Получаем размер строки, хранимой объектом.
	size_t len = data.size() + 1;
	//Записываем этот размер.
	fout.write((char*)&len, sizeof len);
	//Записываем саму строку.
	fout.write(data.c_str(), len);
	
	//Записываем айди связи.
	fout.write((char*)&im_link.id, sizeof im_link.id);
	//Записываем маркер стороны связи.
	fout.write((char*)&im_link.ls, sizeof im_link.ls);

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

	//Читаем айди строки.
	if (!fin.read((char*)&temp.id, sizeof temp.id))//Если чтение неудачное (конец файла),
	{
		return false;//то возвращаем false.
	}
	
	//Читаем длину строки.

	size_t len;
	fin.read((char*)&len, sizeof len);

	try
	{
		//Заполнить все остальное.
		temp.init(fin, len);
	}
	catch (std::bad_alloc & ex)//Если будет исключение, то чтение файла откатится назад к началу записи об этой строке.
	{
		cerr << ex.what() << " in Id_string::bin_read\n";
		int l = sizeof len;
		fin.seekg(-l, ifstream::cur);
		return false;
	}

	swap(*this, temp);//Если все прошло без исключений, то временный объект обменивается с вызывающим.

	if (counter < id)//Обновляем счетчик,если надо.
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

//Оператор вывода.
ostream & operator<<(ostream & os, const Id_string & ids)
{
	os << ids.get_id() << ' ' << ids.get_data() << ' ' << ids.get_link_id() << ' ' << static_cast<int>(ids.get_ls()) << endl;
	return os;
}

//Оператор для чтения из текстового файла.
//istream & operator>>(istream & is, Id_string & ids)
//{
//	std::getline(is, ids.get_data());
//	is>>ids.get_id();
//	is.ignore(1, '\n');
//	if (ids.get_counter() < ids.get_id())
//		ids.get_counter() = ids.get_id();
//	return is;
//}
