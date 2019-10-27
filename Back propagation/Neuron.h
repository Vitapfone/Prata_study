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
	Neuron(int num = 1, float th = 1) : dendrits(num), tetha(th) {}

	//Функция для вывода на экран всех весов.
	void display(int width) const;
	
	//Главная функция. Вычисляет состояние нейрона. Принимает вектор сигналов с других нейронов.
	void process(std::vector<bool> & input);
	//То же для сигмоидной функции активации.
	void process_sigma(std::vector<Neuron> & previous_layer);

	//Функция для обучения нейрона.
	void train(int d, float n, std::vector<bool> & input);
	//Обучение с сигмоидной активационной функцией.
	void train_sigma(float d, float n, std::vector<Neuron> & previous_layer);

	//Обучение скрытого нейрона с сигмоидной активационной функцией.
	void train_hidden_sigma(const std::vector<Neuron> & next_layer, float n, int num, const std::vector<Neuron> & previous_layer);

	//Функция для вывода сигнала.
	float signal() const ;

	//Функция для выдачи дельты.
	float get_delta() const { return delta; } 

	//Выдать произвольный весовой коэффициент.
	float get_weight(int i) const;

	//Установить сигнал. Используется для нейронов входного слоя.
	void set_signal(float new_signal) { y = new_signal; }

private:

	//Функция активации.
	bool activation(float sum);
	//Сигмоидная активация.
	float activation_sigma(float sum);
};

