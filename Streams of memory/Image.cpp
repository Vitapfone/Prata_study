#include "pch.h"
#include "Image.h"

//Заполнить вн.вектор и айдишники из бин. файла
void Image::init(ifstream & fin)
{
	auto buf = make_unique<bool[]>(0);//Умный указатель на будущий буфер. Для работы с массивом это должно быть отражено в параметре шаблона.
	vector<bool> temp(width);

	for (size_t i = 0; i < height; i++)
	{
		//Выделяем буфер.
		buf.reset(new bool[width]);
		
		//Читаем в буфер кол-во байт, равное ширине ( размер bool == 1 байт).
		fin.read((char*)buf.get(), width);
		//Создаем временный вектор из буфера.
		temp.assign(buf.get(), buf.get() + width);
		data.push_back(temp);
	}

	//Читаем айдишник связи.
	fin.read((char*)&is_link.id, sizeof is_link.id);
	//Читаем маркер стороны связи.
	fin.read((char*)&is_link.ls, sizeof is_link.ls);
}

int Image::counter = 0;//Инициализация счетчика.

//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
Image::Image(const Borders & bs, const Inner_frame & ws, char bg, char obj) : data(vector<vector<bool>>())
{
	//Обновление счетчика и установка айди.
	++counter;
	id = counter;

	for (int i = bs.y_min, i2 = 0; i <= bs.y_max; ++i, ++i2)
	{
		//cout << "i=" << i << " ";
		data.push_back(vector<bool>());
		for (int j = bs.x_min; j <= bs.x_max; ++j)
		{
			if (j >= 0 && j < ws[0].size() && i >= 0 && i < ws.size())//Условие, предостерегающее от выхода за границы массива.
			{
				if (ws[i][j] == obj)
				{
					data[i2].push_back(1);
				}
				else
				{
					data[i2].push_back(0);
				}
			}
		}
	}

	width = data[0].size();//Ширина равна размеру элемента вн. вектора.
	height = data.size();

	aspect_rate = ((double)width / height);
}


//Выводит в консоль образ в удобном для восприятия виде.
void Image::visualize()
{
	for (size_t i = 0; i < data.size(); ++i)
	{
		for (size_t j = 0; j < data[0].size(); ++j)
		{
			cout << ((data[i][j] == 1)?'0':' ');
		}
		cout << endl;
	}
}

//Прочитать из бинарного файла.
bool Image::bin_read(ifstream & fin)
{
	using std::swap;//Используется прием "copy and swap" для безопасности при исключении.

	Image temp;//Создается временный объект, с которым и происходят все изменения.

	//Прочитать айди.
	if (!fin.read((char*)&temp.id, sizeof id))
	{
		return false;
	}

	//Прочитать ширину и высоту образа.
	fin.read((char*)&temp.width, sizeof width);
	
	fin.read((char*)&temp.height, sizeof height);
	temp.aspect_rate = static_cast<double>(temp.width) / temp.height;//Приведение типов нужно, т.к. при целочисленном делении(когда оба числа целые) отбрасывается дробная часть.

	try
	{
		temp.init(fin);
	}
	catch (std::bad_alloc & ex)
	{
		
		cerr << ex.what() << " in Image::bin_read\n";
		return false;//При исключении чтение завершится.
	}

	//Если все прошло без исключений, то временный объект обменивается с вызывающим.
	swap(*this, temp);

	//Обновляем счетчик,если надо.
	if (counter < id)
		counter = id;

	if (fin)
		return true;
	else
		return false;
}



//Записать в бинарный файл.
bool Image::bin_write(ofstream & fout) const
{
	fout.write((char*)	&id,		sizeof id);
	fout.write((char*)	&width,		sizeof width);
	fout.write((char*)	&height,	sizeof height);

	bool elem;//Временное хранилище для эл-та.
	for (size_t i = 0; i < height; i++)//Поэлементная запись.
	{
		for (size_t j = 0; j < width; j++)
		{
			elem = data[i][j];
			fout.write((char*)&elem, sizeof elem);
		}
	}
	//Запись айди связи.
	fout.write((char*)&is_link.id, sizeof is_link.id);
	//Запись маркера стороны.
	fout.write((char*)&is_link.ls, sizeof is_link.ls);
	

	if (fout)//Если все успешно,
	{
		return true;//то возвращаем true.
	}
	else
	{
		return false;
	}
}


//Оператор выведет эл-ты внутреннего вектора. Вообще используется для записи в текстовый файл.
//ostream & operator<<(ostream & os, const Image & im)
//{
//	for (size_t i = 0; i < im.get_data().size(); ++i)
//	{
//		for (size_t j = 0; j < im.get_data()[0].size(); ++j)
//		{
//			os << im.get_data()[i][j];
//		}
//		os << endl;
//	}
//	os << '\n';
//	os << im.get_is_link().id << ' ' << im.get_non_link().id << endl;
//
//	return os;
//}


//Функция выяснит совпадают ли образы.
bool image_equality(const Image & im1, const Image & im2, double min_equality)
{
	
	//cout << "Start comparison...";
	if (im1.get_aspect() >= im2.get_aspect()*0.9 && im1.get_aspect() <= im2.get_aspect()*1.1)//Если отношения сторон двух образов различаются в пределах +-10%, то их можно 
																							// сравнивать подробнее.
	{
		Image wider		= (im1.get_widht() >= im2.get_widht()) ?	im1 : im2;	//Временный образ для хранения более широкой фигуры.
		Image narrow	= (im1.get_widht() < im2.get_widht()) ?		im1 : im2;	//Временный образ для узкой фигуры.
		Image higher	= (im1.get_height() >= im2.get_height()) ?	im1 : im2;	//Временный образ для хранения более высокой фигуры.
		Image low		= (im1.get_height() < im2.get_height()) ?	im1 : im2;	//Временный образ для низкой фигуры.
		

		unsigned count = 0;//Счетчик совпадений.
		//Тут происходит очень сложная операция сравнения двух образов разных размеров с использованием относительного положения элементов (пикселей).
		for (size_t i = 0; i < higher.get_height(); ++i)
		{
			for (size_t j = 0; j < wider.get_widht(); ++j)
			{
				if (im1.get_data()[round(i*im1.get_height() / higher.get_height())][round(j*im1.get_widht() / wider.get_widht())] ==
																			im2.get_data()[round(i*im2.get_height() / higher.get_height())][round(j*im2.get_widht() / wider.get_widht())])
				{
					++count;
				}
			}
		}

		size_t max_square = higher.get_height()*wider.get_widht();//Максимально возможное кол-во элементов в образе.
		double equality = count / static_cast<double>(max_square);//Доля совпадений из всех проверок.

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
		//cout << "Huge aspect rate difference!" << endl;
		return false;//то понятно, что они не равны.
	}
		
}