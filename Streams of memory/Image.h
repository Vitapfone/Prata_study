#pragma once
#include "pch.h"
#include "My_names.h"
#include "Id_string.h"
#include "Simple structures.h"

using namespace My_names;

using Inner_frame = vector<vector<char>>;

class Link;//Предварительное объявление для класса связи.

class Image
{
	int id				= 0;	//Идентификатор самого образа.
	static int counter;			//Статический счетчик для получения уникальных айди.

	vector<vector<bool>> data;// Вектор булевых векторов, где будет храниться образ.

	size_t	width		= 0;	//Высота и ширина образа.
	size_t	height		= 0;	
	double	aspect_rate = 0.0;	//Отношение ширины к высоте.

	Link_ptr is_link;//Связь для подтверждающей строки.
	
public:

//КОНСТРУКТОРЫ

	Image() = default;

	//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
	Image(const Borders & bs, const Inner_frame & ws, char, char);

	~Image() {}

//МЕТОДЫ

//ГЕТТЕРЫ

	size_t	get_widht() const	{ return width; }
	size_t	get_height() const	{ return height; }
	double	get_aspect() const	{ return aspect_rate; }

	int get_id()const { return id; }

	//Выдать подтверждающую связь.
	const Link_ptr get_is_link() const {  return is_link; }

	//Выдать вектор образа.
	const vector<vector<bool>> & get_data() const { return data; }

//private:
	//vector<vector<bool>> & get_data() { return data; }//Выдать вектор образа. Неконстантная закрытая перегрузка.

//public:

//СЕТТЕРЫ

	//Установить связь.
	void	set_is_link(Link* is)				{ is_link.pl = is; }
	void	set_is_link(Link_ptr const & other) { is_link = other; }
	

//ДРУГИЕ

	//Выводит в консоль образ в удобном для восприятия виде.
	void visualize();

	//Прочитать из бинарного файла.
	bool bin_read(ifstream & fin);

	//Уменьшить счетчик.
	static void decrease_counter() { --counter; }

private:
	//Заполнить вн.вектор и айдишники из бин. файла
	void init(ifstream & fin);

public:
	//Записать в бинарный файл.
	bool bin_write(ofstream & fout)const;

};

//Оператор выведет эл-ты внутреннего вектора.
//ostream & operator<<(ostream &, const Image &);

//Функция выяснит совпадают ли образы. 
bool image_equality(const Image & im1, const Image & im2, double min_equality);


