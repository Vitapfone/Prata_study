﻿// Streams of memory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Outer_stream.h"
#include "Figures.h"
#include "Warning.h"
#include "Cluster.h"

using namespace My_names;

constexpr size_t WIDTH = 120;//Константа, задающая ширину рабочего пространства.
constexpr size_t HEIGHT = 50;//Константа, задающая высоту рабочего пространства.
constexpr size_t FRAMES = 130;//Количество переданных в поток кадров.

void figure_moving(Square &, size_t);

int main()
{
	system("pause");
	

	Square fig(10, 10, 10);//Фигура для демонстрации записи в поток.

	Outer_stream<WIDTH, HEIGHT> test(100);//Поток заданной длины.

	for (size_t i = 0; i < FRAMES; i++)//Цикл записи.
	{
		//УЧАСТОК ВВОДА ДАННЫХ/////////////////////////////////////////////////////////////////////////////////////////////////////////

		fig.print(test.Input_frame());//Фигура отрисовывает себя на предоставленном потоком кадре ввода.

		test.print_input();//Отрисовка кадра ввода.

		test.process();//Кадр ввода отправляется в поток.



		//УЧАСТОК УПРАВЛЕНИЯ ВНИМАНИЕМ ///////////////////////////////////////////////////////////////////////////////////////////////////

		//Focus_of_attention foc(10, 10, ar1);//Задаем начальное положение фокуса внимания.

		//Вектор для хранения предупреждений от функций управления вниманием внешнего потока.
		vector<Warning> warnings;

		//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Файл Cluster.h
		Warning w1 = most_filled_cluster(test.get_frame(0), ' ');

		//Заносим предупреждение в вектор.
		warnings.push_back(w1);

		//После занесения всех предупреждений сортируем так, чтобы первым эл-том был тот, у кого наибольшая важность.
		sort(warnings.begin(), warnings.end(), [](const Warning & w1, const Warning & w2) {return w1.get_importance() > w2.get_importance(); });
		Warning most_important = warnings[0];

		most_important.what();//Отладочный вывод.

		system("cls");

		//Движение фигуры в зависимости от стадии цикла записи.
		figure_moving(fig, i);


		//УЧАСТОК ПОДГОТОВКИ К СЛЕДУЮЩЕМУ ЦИКЛУ СОЗНАНИЯ ///////////////////////////////////////////////////////////////////////////////

		warnings.clear();//Очищаем список предупреждений, чтобы заполнить его в следующем цикле.

		
	}

	//test.play(10);//Вывод содержимого потока в консоль.

	cout << "End...\n";

	return 0;
}

//Движение фигуры в зависимости от стадии цикла записи.
void figure_moving(Square & fig, size_t i)
{
	//Далее код для простейшего движения фигуры. Фигура пройдет по кругу за время цикла записи.
	if (i <= FRAMES / 4)
	{
		fig.moveRight();
	}
	else if (i <= FRAMES / 2)
	{
		fig.moveDown();
	}
	else if (i <= 0.75*FRAMES)
	{
		fig.moveLeft();
	}
	else
	{
		fig.moveUp();
	}
}
