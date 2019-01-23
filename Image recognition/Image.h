#pragma once
#include "My_names.h"
#include "Id_string.h"
#include "Simple structures.h"

using namespace My_names;

class Image
{
	vector<vector<bool>> data;// Вектор булевых векторов, где будет храниться образ.

	size_t width = 0, height = 0; //Высота и ширина образа.
	double aspect_rate = 0.0;//Отношение ширины к высоте.

	Id_string *is_ps = nullptr;//Указатель, имитирующий некую информативную связь объекта образа.
	int id_is_ps = 0;//Идентификатор для этого указателя, позволит потом найти эту строку.
	Id_string *non_ps = nullptr;
	int id_non_ps = 0;

public:
	Image() = default;
	//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
	template<size_t W, size_t H> 
	Image(const Borders & bs, array<array<char, W>, H> &, char, char);
	//Конструктор заполнит внутренний вектор из бинарного файла.
	Image(ifstream &);

	~Image() {}

	//МЕТОДЫ

	size_t get_widht() const { return width; }//Выдать ширину.
	size_t get_height() const { return height; }//Выдать высоту.
	double get_aspect() const { return aspect_rate; }//Выдать отношение ширины к высоте.
	Id_string * get_is_ps() const { return is_ps; }//Выдать хранимый указатель.
	Id_string * get_non_ps() const { return non_ps; }

	int get_id_is_ps() const { return id_is_ps; }//Выдать идентификатор указателя.
	int get_id_non_ps() const { return id_non_ps; }
	
	void set_is_ps(Id_string* other) { is_ps = other; id_is_ps = other->get_id(); }//Установить связь указателя с некоей строкой с идентификатором.
	void set_non_ps(Id_string* other) { non_ps = other; id_non_ps = other->get_id(); }

	//Выводит в консоль образ в удобном для восприятия виде.
	void visualize();

	//Прочитать из бинарного файла.
	bool bin_read(ifstream & fin);

	//Записать в бинарный файл.
	bool bin_write(ofstream & fout)const;

	//Оператор выведет эл-ты внутреннего вектора.
	friend ostream & operator<<(ostream &, const Image &);

	//Функция выяснит совпадают ли образы. 
	friend bool image_equality(const Image & im1, const Image & im2, double min_equality);	
};



//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
template<size_t W, size_t H> Image::Image(const Borders & bs, array<array<char, W>, H> & ws, char bg, char obj) : data(vector<vector<bool>>())
{
	//cout << "Constructing... ";
	for (int i = bs.y_min, i2 = 0; i <= bs.y_max; ++i, ++i2)
	{
		//cout << "i=" << i << " ";
		data.push_back(vector<bool>());
		for (int j = bs.x_min; j <= bs.x_max; ++j)
		{
			if (j >= 0 && j < W && i >= 0 && i < H)//Условие, предостерегающее от выхода за границы массива.
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