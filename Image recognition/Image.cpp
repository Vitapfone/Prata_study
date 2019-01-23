#include "pch.h"
#include "Image.h"
#include "My_names.h"

using namespace My_names;

//Конструктор заполнит внутренний вектор из бинарного файла.
Image::Image(ifstream & ifs) : data(vector<vector<bool>>())
{
	//Прочитать ширину и высоту образа.
	ifs.read((char*)&width, sizeof width);
	ifs.read((char*)&height, sizeof height);
	aspect_rate = (double) width / height;//Приведение типов нужно, т.к. при целочисленном делении(когда оба числа целые) отбрасывается дробная часть.

	shared_ptr<bool> buf(new bool[width]);//Выделяем буфер.
	for (size_t i = 0; i < height; i++)
	{
		ifs.read((char*)buf.get(), width);//Читаем в буфер кол-во байт, равное ширине ( размер bool == 1 байт).
		vector<bool> temp(buf.get(), buf.get() + width);//Создаем временный вектор из буфера.
		data.push_back(temp);
		//delete[] buf;//Очищаем буфер.
	}

	//Читаем айдишники.
	ifs.read((char*)&id_is_ps, sizeof id_is_ps);
	ifs.read((char*)&id_non_ps, sizeof id_non_ps);
}


//Выводит в консоль образ в удобном для восприятия виде.
void Image::visualize()
{
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < data[0].size(); ++j)
		{
			cout << ((data[i][j] == 1)?'0':' ');
		}
		cout << endl;
	}
}

//Прочитать из бинарного файла.
bool Image::bin_read(ifstream & fin)
{
	//Прочитать ширину и высоту образа.
	
	if (!fin.read((char*)&width, sizeof width))
	{
		return false;
	}
	fin.read((char*)&height, sizeof height);
	aspect_rate = (double)width / height;//Приведение типов нужно, т.к. при целочисленном делении(когда оба числа целые) отбрасывается дробная часть.

	if (!data.empty())//Если вн. вектор не пуст, то очистим его. На всякий случай.
	{
		data.clear();
	}

	shared_ptr<bool> buf;//Умный указатель на будущий буфер.
	vector<bool> temp(width);

	for (size_t i = 0; i < height; i++)
	{
		buf.reset(new bool[width]);//Выделяем буфер.
		//cout << "Read into buf\n";
		fin.read((char*)buf.get(), width);//Читаем в буфер кол-во байт, равное ширине ( размер bool == 1 байт).
		temp.assign(buf.get(), buf.get() + width);//Создаем временный вектор из буфера.
		data.push_back(temp);
	}

	//Читаем айдишники.
	fin.read((char*)&id_is_ps, sizeof id_is_ps);
	fin.read((char*)&id_non_ps, sizeof id_non_ps);

	if (fin)
		return true;
	else
		return false;
}

//Записать в бинарный файл.
bool Image::bin_write(ofstream & fout) const
{
	fout.write((char*)&width, sizeof width);//Запись ширины.
	fout.write((char*)&height, sizeof height);//Запись высоты.

	bool elem;//Временное хранилище для эл-та.
	for (size_t i = 0; i < height; i++)//Поэлементная запись.
	{
		for (size_t j = 0; j < width; j++)
		{
			elem = data[i][j];
			fout.write((char*)&elem, sizeof elem);
		}
	}
	//Запись айди связей.
	fout.write((char*)&id_is_ps, sizeof id_is_ps);
	fout.write((char*)&id_non_ps, sizeof id_non_ps);

	if (fout)//Если все успешно,
	{
		return true;//то возвращаем true.
	}
	else
	{
		return false;
	}
}


//Оператор выведет эл-ты внутреннего вектора. Вообще используется для записи в файл.
ostream & operator<<(ostream & os, const Image & im)
{
	for (int i = 0; i < im.data.size(); ++i)
	{
		for (int j = 0; j < im.data[0].size(); ++j)
		{
			os << im.data[i][j];
		}
		os << endl;
	}
	os << '\n';
	os << im.id_is_ps << ' ' << im.id_non_ps << endl;

	return os;
}


//Функция выяснит совпадают ли образы.
bool image_equality(const Image & im1, const Image & im2, double min_equality)
{
	
	//cout << "Start comparison...";
	if (im1.get_aspect() >= im2.get_aspect()*0.9 && im1.get_aspect() <= im2.get_aspect()*1.1)//Если отношения сторон двух образов различаются в пределах +-10%, то их можно 
																							// сравнивать подробнее.
	{
		Image wider = (im1.get_widht() >= im2.get_widht()) ? im1 : im2;//Временный образ для хранения более широкой фигуры.
		//cout << "Wider image:" << endl;
		//wider.visualize();

		Image narrow = (im1.get_widht() < im2.get_widht()) ? im1 : im2;//Временный образ для узкой фигуры.
		//cout << "Narrow image:" << endl;
		//narrow.visualize();

		Image higher = (im1.get_height() >= im2.get_height()) ? im1 : im2;//Временный образ для хранения более высокой фигуры.
		//cout << "Higher image:" << endl;
		//higher.visualize();

		Image low = (im1.get_height() < im2.get_height()) ? im1 : im2;//Временный образ для низкой фигуры.
		//cout << "Lower image:" << endl;
		//low.visualize();

		size_t count = 0;//Счетчик совпадений.
		//Тут происходит очень сложная операция сравнения двух образов разных размеров с использованием относительного положения элементов (пикселей).
		for (int i = 0; i < higher.get_height(); ++i)
		{
			for (int j = 0; j < wider.get_widht(); ++j)
			{
				if (im1.data[round(i*im1.get_height() / higher.get_height())][round(j*im1.get_widht() / wider.get_widht())] ==
																			im2.data[round(i*im2.get_height() / higher.get_height())][round(j*im2.get_widht() / wider.get_widht())])
				{
					++count;
				}
			}
		}

		size_t max_square = higher.get_height()*wider.get_widht();//Максимально возможное кол-во элементов в образе.
		double equality = count / static_cast<double>(max_square);//Доля совпадений из всех проверок.

		cout << count << " " << max_square << " " << equality << endl;

		if (equality >= min_equality)//Константа, определяющая минимальное сходство образов для решения об их идентичности.
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else //Если отношения сторон сильно различаются,
	{
		cout << "Huge aspect rate difference!" << endl;
		return false;//то понятно, что они не равны.
	}
		
}