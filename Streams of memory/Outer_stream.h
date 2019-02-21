#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

//Псевдоним шаблона кадра потока.
template<size_t W, size_t H>
using Outer_frame = array<array<char, W>, H>;

template<size_t W, size_t H>
class Outer_stream
{
	Outer_frame<W, H>			input_frame;	//Кадр потока, в который будут загружать данные функции восприятия внешнего мира.
	deque<Outer_frame<W, H>>	data;			//Дека, в которой будут последовательно храниться кадры с данными от органов чувств.
	size_t						max_size;		//Максимальный размер деки и длина потока.

public:

//КОНСТРУКТОРЫ

	explicit Outer_stream(size_t max_sz = 100);

	~Outer_stream() {}

//ЗАПРЕЩЕНО

	//Запрещено копирование.
	Outer_stream(const Outer_stream & other) = delete;
	//Запрещено присваивание.
	Outer_stream & operator=(const Outer_stream & other) = delete;

//МЕТОДЫ

//ГЕТТЕРЫ

	//Получить максимальный размер потока.
	const size_t get_max_size() const { return max_size; }

	//Получить текущий размер потока.
	const size_t get_size() const { return data.size(); }

	//Получить для заполнения кадр ввода. Не просто геттер, а связь потока внешним миром.
	Outer_frame<W, H> & Input_frame() { return input_frame; }

	//Получить для чтения произвольный кадр потока.
	const Outer_frame<W, H>  & get_ro_frame(size_t num) const;

//СЕТТЕРЫ

	//Установить новый макс. размер потока.
	void set_max_size(size_t new_size) { max_size = new_size; }

//ДРУГОЕ

	//Отладочный вывод кадра ввода.
	void print_input() const;

	//Отладочный вывод содержимого потока.
	//void play(unsigned dur) const;

	//Внести новые данные в поток. Удалить старые.
	void process();

	
private:

	//Отрисовать отдельный кадр.
	void print_frame(const Outer_frame<W, H> & fr) const;

	//Подготовить кадр ввода.
	void prepare_for_input();
};

//Подготовить кадр ввода.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::prepare_for_input()
{
	//Подготавливаем кадр ввода к приему данных, заполняя его пробелами.
	for (auto &e : input_frame)
	{
		for (auto &e2 : e)
		{
			e2 = ' ';
		}
	}
}

//Конструктор.
template<size_t W, size_t H>
Outer_stream<W, H>::Outer_stream(size_t max_sz) : max_size(max_sz)
{
	//Подготавливаем кадр ввода.
	prepare_for_input();

	//Дека создается пустой.
}


//Отрисовать отдельный кадр.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::print_frame(const Outer_frame<W, H> & fr) const
{
	for (size_t i = 0; i < H; ++i)//В каждой строке
	{

		for (size_t j = 0; j < W; ++j)//перебираются все символы.
		{

			//Далее код для рисования границы кадров.
			if (i == 0 || i == H - 1)
			{
				cout << '=';
			}
			else if (j == 0 || j == W - 1)
			{
				cout << '!';
			}
			else
			{
				cout << fr[i][j];
			}
		}
		cout << endl;
	}
}


//Получить для чтения произвольный кадр потока.
template<size_t W, size_t H>
const Outer_frame<W, H> & Outer_stream<W, H>::get_ro_frame(size_t num) const
{
	//Особенность в том, что num должен считаться с конца деки, т.к. надо, чтобы кадр с большим номером был отснят ранее.

	size_t len = data.size();

	assert(num >= 0 && num < len);

	return data[len - 1 - num];
}

//Отладочный вывод кадра ввода.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::print_input() const
{
	print_frame(input_frame);
}


//Отладочный вывод содержимого потока. Параметр -- задержка кадра на экране.
//template<size_t W, size_t H>
//void Outer_stream<W, H>::play(unsigned dur) const
//{
//	int i = 0;//Счетчик выведенных кадров.
//	
//	for (auto & e : data)//Перебираются все кадры.
//	{
//		print_frame(e);
//
//		cout << ++i << endl;
//
//		Sleep(dur);//Задержка. Windows.h
//		system("cls");//Очищаем экран консоли.
//	}
//}

//Внести новые данные в поток. Удалить старые.
template<size_t W, size_t H>
void Outer_stream<W, H>::process()
{
	//Вставляем заполненный кадр ввода в деку.
	data.push_back(input_frame);
	
	if (data.size() > max_size)//Если размер деки превышает максимум, то убираем один кадр из начала, где находятся самые старые данные. 
	{
		data.pop_front();
	}

	//Подготовить кадр ввода для повторного заполнения.
	prepare_for_input();
}


