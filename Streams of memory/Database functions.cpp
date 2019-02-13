#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Id_string.h"
#include "Image.h"

using namespace My_names;

//Заполнение переданных контейнеров базы данных из файлов.
void database_initialization(const string & file1, const string & file2, map<int, Id_string> & strings, list<Image> & images)
{
	//Чтение строк из файла.

	ifstream ifs_str(file1, ifstream::binary);
	Id_string temp;//Временный объект строки.

	while (temp.bin_read(ifs_str))//Пока не достигнут конец файла.
	{
		strings[temp.get_id()] = temp;//Вставляем прочитанное в карту.
	}

	//Конструирование образов из файлов.

	ifstream ifs_Images(file2, ifstream::binary);
	Image temp1;//Временный объект образа.

	while (temp1.bin_read(ifs_Images))//Чтение из файла во временный объект.
	{
		temp1.set_is_link(&strings[temp1.get_is_link().id]);//Восстановление связей.
		temp1.set_non_link(&strings[temp1.get_non_link().id]);

		images.push_back(temp1);
	}
}

//Запись содержимого контейнеров в файлы.
void database_recording(const string & file1, const string & file2, map<int, Id_string>& strings, list<Image>& images)
{
	ofstream ofstrings(file1, ofstream::binary);//Создаем файл для записи связанных с образами строк. Папка должна быть создана заранее.
	for (const auto &e : strings)//Записываем все строки из карты.
	{
		e.second.bin_write(ofstrings);
	}
	
	ofstream ofsImages(file2, ofstream::binary);//Создаем файл для записи образов.
	for (const auto & e : images)
	{
		e.bin_write(ofsImages);
	}
}
