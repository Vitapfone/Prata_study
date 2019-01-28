#pragma once

using namespace My_names;


template<size_t W, size_t H>
class Outer_stream
{

	using Frame = array<array<char, W>, H>;

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

template<size_t W, size_t H>
Outer_stream<W, H>::Outer_stream(size_t ms)
{
	//Подготавливаем кадр ввода к приему данных, заполняя его пробелами.
	for (auto &e : input_frame)
	{
		for (auto &e2 : e)
		{
			e2 = ' ';
		}
	}
	//Дека создается пустой.
}

//Отладочный вывод содержимого потока. Параметр -- задержка кадра на экране.
template<size_t W, size_t H>
void Outer_stream<W, H>::play(unsigned dur) const
{
	for (auto & e : data)//Перебираются все кадры.
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
					cout << e[i][j];
				}
			}
			cout << endl;
		}
		cout << endl;

		_sleep(dur);//Задержка.
		system("cls");//Очищаем экран консоли.
	}
}
