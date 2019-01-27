#pragma once

using namespace My_names;

constexpr size_t WIDTH = 120;//Константа, задающая ширину рабочего пространства.
constexpr size_t HEIGHT = 60;//Константа, задающая высоту рабочего пространства.

using Frame = array<array<char, WIDTH>, HEIGHT>;

class Outer_stream
{
	Frame input_frame;//Кадр потока, в который будут загружать данные функции восприятия внешнего мира.
	deque<Frame> data;//Дека, в которой будут последовательно храниться кадры с данными от органов чувств.
	size_t max_size;//Максимальный размер деки и длина потока.

public:

//КОНСТРУКТОРЫ

	explicit Outer_stream(size_t ms = 100);
	~Outer_stream() {}

//ЗАПРЕЩЕНО
	//Запрещено копирование.
	Outer_stream(const Outer_stream & other) = delete;
	//Запрещено присваивание.
	Outer_stream & operator=(const Outer_stream & other) = delete;

//МЕТОДЫ

//ГЕТТЕРЫ

	//Получить максимальный размер потока.
	size_t get_max_size() const { return max_size; }

	//Получить для заполнения кадр ввода. Не просто геттер, а связь потока внешним миром.
	Frame & Input_frame() { return input_frame; }

//СЕТТЕРЫ

	//Установить новый макс. размер потока.
	void set_max_size(size_t new_size) { max_size = new_size; }

//ДРУГОЕ

	//Отладочный вывод содержимого потока.
	void play(unsigned dur) const;

};

