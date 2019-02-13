#include "pch.h"
#include "My_names.h"
#include "Inner_stream.h"

//Получить для чтения произвольный кадр потока.
const Inner_frame & Inner_stream::get_frame(size_t num) const
{
	//Особенность в том, что num должен считаться с конца деки, т.к. надо, чтобы кадр с большим номером был отснят ранее.

	size_t len = data.size();

	if (data.empty())
	{
		throw std::logic_error("Empty stream!\n");
	}
	if (num < 0 || num >= len)
	{
		throw std::out_of_range("Out of range!\n");
	}
	return data[len - 1 - num];
}

//Перегрузка для изменяющих действий.
Inner_frame & Inner_stream::get_frame(size_t num)
{
	//Особенность в том, что num должен считаться с конца деки, т.к. надо, чтобы кадр с большим номером был отснят ранее.

	return const_cast<Inner_frame &> (const_cast<const Inner_stream* >(this)->get_frame(num));
}

//Подготовить кадр ввода для повторного заполнения.
void Inner_stream::prepare_for_input()
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

//Внести новые данные в поток. Удалить старые.
void Inner_stream::process()
{
	data.push_back(input_frame);//Вставляем заполненный кадр ввода в деку.
	//cout << data.size() << ' ';
	if (data.size() > max_size)//Если размер деки превышает максимум, то убираем один кадр из начала, где находятся самые старые данные. 
	{
		//cout << max_size << endl;
		//cout << "???\n";
		data.pop_front();
	}

	prepare_for_input();//Подготовить кадр ввода для повторного заполнения.
}

//Вспомогательная ф-я для отрисовки кадра в консоли. Дает кадру видимые границы. 
void make_borders(Inner_frame & fr)
{
	size_t width = fr[0].size();
	size_t height = fr.size();

	for (int i = 0; i < width; ++i)
	{
		fr[0][i] = '=';
		fr[height - 1][i] = '=';
	}
	for (int j = 0; j < height; ++j)
	{
		fr[j][0] = '!';
		fr[j][width - 1] = '!';
	}
}

////Функция отрисовки одного кадра.
//void Inner_stream::print_frame(Inner_frame & fr)
//{
//	::print_frame(fr);
//}

//Отладочный вывод содержимого потока.
void Inner_stream::play(unsigned dur)
{
	Inner_frame frame_copy;//Копия кадра, чтобы не записывать видимые границы кадра(только для удобства просмотра в консоли) в сам поток.
	for (const auto & e : data)
	{
		frame_copy = e;
		print_frame(frame_copy);//Отрисовываем копию.

		Sleep(dur);//Задержка. Windows.h
		system("cls");//Очищаем экран консоли.
	}
}

//Свободная функция для отрисовки кадра.
void print_frame(Inner_frame & fr)
{
	make_borders(fr);

	for (const auto &e : fr)// Выводим в консоль.
	{
		for (const auto &e2 : e)
		{
			cout << e2;
		}
		cout << endl;
	}
	cout << endl;
}
