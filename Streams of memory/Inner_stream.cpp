#include "pch.h"
#include "Inner_stream.h"

//Получить для чтения произвольный кадр потока.
const Inner_frame & Inner_stream::get_ro_frame(size_t num) const
{
	//Особенность в том, что num должен считаться с конца деки, т.к. надо, чтобы кадр с большим номером был отснят ранее.

	size_t len = data_.size();

	assert(num >= 0 && num < len);

	return data_[len - 1 - num];
}

//Получить произвольный кадр для изменяющих действий.
Inner_frame & Inner_stream::get_frame(size_t num)
{
	//Особенность в том, что num должен считаться с конца деки, т.к. надо, чтобы кадр с большим номером был отснят ранее.

	return const_cast<Inner_frame &> ((this)->get_ro_frame(num));
}

//Подготовить кадр ввода для повторного заполнения.
void Inner_stream::prepare_for_input()
{
	//Подготавливаем кадр ввода к приему данных, заполняя его пробелами.
	for (auto &e : input_frame_)
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
	//Вставляем заполненный кадр ввода в деку.
	data_.push_back(input_frame_);
	
	if (data_.size() > max_size_)//Если размер деки превышает максимум, то убираем один кадр из начала, где находятся самые старые данные. 
	{
		data_.pop_front();
	}

	//Подготовить кадр ввода для повторного заполнения.
	prepare_for_input();
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

//Отладочный вывод содержимого потока.
//void Inner_stream::play(unsigned dur)
//{
//	Inner_frame frame_copy;//Копия кадра, чтобы не записывать видимые границы кадра(только для удобства просмотра в консоли) в сам поток.
//	for (const auto & e : data_)
//	{
//		frame_copy = e;
//		print_frame(frame_copy);//Отрисовываем копию.
//
//		Sleep(dur);//Задержка. Windows.h
//		system("cls");//Очищаем экран консоли.
//	}
//}

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
