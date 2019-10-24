#pragma once

#include "pch.h"
#include "Input.h"

//Класс для самого простого нейрона.

class Neuron
{
	std::vector<Input> dendrits; //Все входы нейрона.

	float tetha = 1; //Предел чувствительности.

	bool y = 0; //Выходной сигнал (состояние) нейрона.

public:

	//Конструктор. Просто задает количество входов.
	Neuron(int num, float th) : dendrits(num), tetha(th) {}

	//Функция для вывода на экран всех весов.
	void display(int width);
	
	//Главная функция. Вычисляет состояние нейрона. Принимает вектор сигналов с других нейронов.
	void process(std::vector<bool> & input);

	//Функция для обучения нейрона.
	void train(int d, float n, std::vector<bool> & input);

	//Функция для вывода сигнала.
	bool signal();

private:

	//Функция активации.
	bool activation(float sum);
};

