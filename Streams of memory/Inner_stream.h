#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

using Inner_frame = vector<vector<char>>;

class Inner_stream
{
	size_t				height		= 0;	//Высота кадра.
	size_t				width		= 0;	//Ширина кадра.
	size_t				max_size	= 0;	//Максимальный размер деки и длина потока.
	Inner_frame			input_frame;		//Кадр потока, в который будут поступать данные из внешнего потока (через фильтр восприятия).
	deque<Inner_frame>	data;				//Дека, в которой будут последовательно храниться кадры с данными, которые должны быть запомнены.
	
public:

//КОНСТРУКТОРЫ

	Inner_stream(size_t w, size_t h, size_t l) : height(h), width(w), input_frame(Inner_frame(height, vector<char>(width, ' '))), max_size(l) {}


//ЗАПРЕЩЕНО

	//Запрещено копирование.
	Inner_stream(const Inner_stream & other) = delete;
	//Запрещено присваивание.
	Inner_stream & operator=(const Inner_stream & other) = delete;


//МЕТОДЫ

//ГЕТТЕРЫ

	//Получить максимальный размер потока.
	const size_t get_max_size() const { return max_size; }

	//Получить текущий размер потока.
	const size_t get_size() const { return data.size(); }

	//Получить для заполнения кадр ввода. Не просто геттер, а связь потока внешним миром.
	Inner_frame & Input_frame (){ return input_frame; }

	//Получить для чтения произвольный кадр потока.
	const Inner_frame & get_ro_frame(size_t num) const;
	//Получить произвольный кадр для изменяющих действий.
	Inner_frame & get_frame(size_t num);

//СЕТТЕРЫ

	//Установить новый макс. размер потока.
	void set_max_size(size_t new_size) { max_size = new_size; }


//ДРУГОЕ

	//Внести новые данные в поток. Удалить старые.
	void process();

	//Отладочный вывод содержимого потока.
	//void play(unsigned dur);

private:

	//Подготовить кадр ввода для повторного заполнения.
	void prepare_for_input();
};

//Свободная функция для отрисовки кадра. Inner_stream.h
void print_frame(Inner_frame & fr);

//Вспомогательная ф-я для отрисовки кадра в консоли. Дает кадру видимые границы.  Inner_stream.h
void make_borders(Inner_frame &);