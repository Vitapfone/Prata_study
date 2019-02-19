#pragma once
#include "pch.h"
#include "My_names.h"
#include "Id_string.h"
#include "Simple structures.h"

using namespace My_names;
using Inner_frame = vector<vector<char>>;
enum class Link_side {no, left, right}; //Перечисление для определения стороны связи, к которой прикреплен этот образ.
class Link;//Предварительное объявление для класса связи.

class Image
{
	int id = 0;//Идентификатор самого образа.
	static int counter;//Статический счетчик для получения уникальных айди.

	vector<vector<bool>> data;// Вектор булевых векторов, где будет храниться образ.

	size_t width = 0, height = 0; //Высота и ширина образа.
	double aspect_rate = 0.0;//Отношение ширины к высоте.

	

	struct Link_ptr //Структура для представления нумерованной связи объекта.
	{
		Link* pl = nullptr; //Указатель, имитирующий некую информативную связь объекта образа.
		Link_side ls = Link_side::no;
		int id = 0; //Идентификатор для этого указателя, позволит потом найти эту строку.
	};


	Link_ptr is_link;//Связь для подтверждающей строки.
	

public:

//КОНСТРУКТОРЫ

	Image() = default;

	//Конструктор заполнит внутренний вектор на основе предоставленных диапазонов координат.
	Image(const Borders & bs, const Inner_frame & ws, char, char);

	~Image() {}

//МЕТОДЫ

//ГЕТТЕРЫ

	size_t get_widht() const { return width; }//Выдать ширину.
	size_t get_height() const { return height; }//Выдать высоту.
	double get_aspect() const { return aspect_rate; }//Выдать отношение ширины к высоте.

	int get_id()const { return id; }
	const Link_ptr get_is_link() const { return is_link; }//Выдать подтверждающую связь.
	
	
	const vector<vector<bool>> & get_data() const { return data; }//Выдать вектор образа.

//private:
	//vector<vector<bool>> & get_data() { return data; }//Выдать вектор образа. Неконстантная закрытая перегрузка.

//public:

//СЕТТЕРЫ

	void set_is_link(Link* is) { is_link.pl = is; /*is_link.id = is->get_id();*/ }//Установить связь.
	void set_is_link(Link_ptr const & other) { is_link = other; }
	

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


