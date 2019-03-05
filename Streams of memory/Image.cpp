#include "pch.h"
#include "Image.h"

//Заполнить вн.вектор и айдишники из бин. файла
void Image::init(ifstream & fin)
{
	auto buf = make_unique<bool[]>(0);//Умный указатель на будущий буфер. Для работы с массивом это должно быть отражено в параметре шаблона.
	vector<bool> temp(width_);

	for (size_t i = 0; i < height_; i++)
	{
		//Выделяем буфер.
		buf.reset(new bool[width_]);
		
		//Читаем в буфер кол-во байт, равное ширине ( размер bool == 1 байт).
		fin.read((char*)buf.get(), width_);
		//Создаем временный вектор из буфера.
		temp.assign(buf.get(), buf.get() + width_);
		data_.push_back(temp);
	}

	//Читаем айдишник связи.
	fin.read((char*)&is_link_.id_, sizeof is_link_.id_);
	//Читаем маркер стороны связи.
	fin.read((char*)&is_link_.ls_, sizeof is_link_.ls_);
}

int Image::counter_ = 0;//Инициализация счетчика.

//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
Image::Image(const Borders & bs, const Inner_frame & ws, char bg, char obj) : data_(vector<vector<bool>>())
{
	//Обновление счетчика и установка айди.
	++counter_;
	id_ = counter_;

	for (int i = bs.y_min_, i2 = 0; i <= bs.y_max_; ++i, ++i2)
	{
		//cout << "i=" << i << " ";
		data_.push_back(vector<bool>());
		for (int j = bs.x_min_; j <= bs.x_max_; ++j)
		{
			if (j >= 0 && j < ws[0].size() && i >= 0 && i < ws.size())//Условие, предостерегающее от выхода за границы массива.
			{
				if (ws[i][j] == obj)
				{
					data_[i2].push_back(1);
				}
				else
				{
					data_[i2].push_back(0);
				}
			}
		}
	}

	width_ = data_[0].size();//Ширина равна размеру элемента вн. вектора.
	height_ = data_.size();

	aspect_rate_ = ((double)width_ / height_);
}


//Выводит в консоль образ в удобном для восприятия виде.
void Image::visualize()
{
	for (size_t i = 0; i < data_.size(); ++i)
	{
		for (size_t j = 0; j < data_[0].size(); ++j)
		{
			cout << ((data_[i][j] == 1)?'0':' ');
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
	if (!fin.read((char*)&temp.id_, sizeof id_))
	{
		return false;
	}

	//Прочитать ширину и высоту образа.
	fin.read((char*)&temp.width_, sizeof width_);
	
	fin.read((char*)&temp.height_, sizeof height_);
	temp.aspect_rate_ = static_cast<double>(temp.width_) / temp.height_;//Приведение типов нужно, т.к. при целочисленном делении(когда оба числа целые) отбрасывается дробная часть.

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
	if (counter_ < id_)
		counter_ = id_;

	if (fin)
		return true;
	else
		return false;
}



//Записать в бинарный файл.
bool Image::bin_write(ofstream & fout) const
{
	fout.write((char*)	&id_,		sizeof id_);
	fout.write((char*)	&width_,		sizeof width_);
	fout.write((char*)	&height_,	sizeof height_);

	bool elem;//Временное хранилище для эл-та.
	for (size_t i = 0; i < height_; i++)//Поэлементная запись.
	{
		for (size_t j = 0; j < width_; j++)
		{
			elem = data_[i][j];
			fout.write((char*)&elem, sizeof elem);
		}
	}
	//Запись айди связи.
	fout.write((char*)&is_link_.id_, sizeof is_link_.id_);
	//Запись маркера стороны.
	fout.write((char*)&is_link_.ls_, sizeof is_link_.ls_);
	

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
//	os << im.get_is_link().id_ << ' ' << im.get_non_link().id_ << endl;
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