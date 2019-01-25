#pragma once
//#include "My_names.h"
//#include "Id_string.h"
//#include "Simple structures.h"

using namespace My_names;

class Image
{
	struct Link_ptr //Структура для представления нумерованной связи объекта.
	{
		Id_string* ps = nullptr; //Указатель, имитирующий некую информативную связь объекта образа.
		int id = 0; //Идентификатор для этого указателя, позволит потом найти эту строку.
	};

	vector<vector<bool>> data;// Вектор булевых векторов, где будет храниться образ.

	size_t width = 0, height = 0; //Высота и ширина образа.
	double aspect_rate = 0.0;//Отношение ширины к высоте.

	Link_ptr is_link;//Связь для подтверждающей строки.
	Link_ptr non_link;//Связь для опровергающей строки.

public:
	Image() = default;
	//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
	template<size_t W, size_t H> 
	Image(const Borders & bs, const array<array<char, W>, H> &, char, char);
	//Конструктор заполнит внутренний вектор из бинарного файла.
	Image(ifstream &);

	~Image() {}

//МЕТОДЫ

	size_t get_widht() const { return width; }//Выдать ширину.
	size_t get_height() const { return height; }//Выдать высоту.
	double get_aspect() const { return aspect_rate; }//Выдать отношение ширины к высоте.

	Link_ptr get_is_link()const { return is_link; }//Выдать подтверждающую связь.
	Link_ptr get_non_link()const { return non_link; }//Выдать опровергающую связь.
	
	void set_is_link(Id_string* is) { is_link.ps = is; /*is_link.id = is->get_id();*/ }//Установить связь с некоей строкой с идентификатором.
	void set_is_link(Link_ptr const & other) { is_link = other; }
	void set_non_link(Id_string* is) { non_link.ps = is; /*non_link.id = is->get_id();*/ }
	void set_non_link(Link_ptr const & other) { non_link = other; }

	//Выводит в консоль образ в удобном для восприятия виде.
	void visualize();

	//Прочитать из бинарного файла.
	bool bin_read(ifstream & fin);

private:
	//Заполнить вн.вектор и айдишники из бин. файла
	void init(ifstream & fin);

public:
	//Записать в бинарный файл.
	bool bin_write(ofstream & fout)const;

	//Оператор выведет эл-ты внутреннего вектора.
	friend ostream & operator<<(ostream &, const Image &);

	//Функция выяснит совпадают ли образы. 
	friend bool image_equality(const Image & im1, const Image & im2, double min_equality);	
};



//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
template<size_t W, size_t H> Image::Image(const Borders & bs, const array<array<char, W>, H> & ws, char bg, char obj) : data(vector<vector<bool>>())
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