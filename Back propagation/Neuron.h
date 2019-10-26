#pragma once

#include "pch.h"
#include "Input.h"

//Класс для самого простого нейрона.

class Neuron
{
	std::vector<Input> dendrits; //Все входы нейрона.

	float tetha = 1; //Предел чувствительности.

	float y = 0; //Выходной сигнал (состояние) нейрона.

	float delta = 0.0; //Ошибка нейрона.

public:

	//Конструктор. Просто задает количество входов.
	Neuron(int num, float th) : dendrits(num), tetha(th) {}

	//Функция для вывода на экран всех весов.
	void display(int width);
	
	//Главная функция. Вычисляет состояние нейрона. Принимает вектор сигналов с других нейронов.
	void process(std::vector<bool> & input);
	//То же для сигмоидной функции активации.
	void process_sigma(std::vector<float> & input);

	//Функция для обучения нейрона.
	void train(int d, float n, std::vector<bool> & input);
	//Обучение с сигмоидной активационной функцией.
	void train_sigma(float d, float n, std::vector<float> & input);

	//Функция для вывода сигнала.
	float signal();

	//Функция для выдачи дельты.
	float get_delta() { return delta; }

	//Выдать произвольный весовой коэффициент.
	float get_weight(int i);

private:

	//Функция активации.
	bool activation(float sum);
	//Сигмоидная активация.
	float activation_sigma(float sum);
};

