#pragma once

//Для начала маленький класс, представляющий один вход нейрона.

class Input
{
	float w; //Весовой коэффициент сигнала для этого входа.
	

public:

	//Конструктор
	Input();

	//Геттер
	float get_weight() const { return w; } 

	//Взвешивание полученного сигнала.
	float weighing(float x) { return w * x; }
	//Взвешивание для сигмоидной функции активации.
	float weighing_sigma(float x) { return w * x; }

	//Обучение.
	void train(float delta, float n, float x);
	//Обучение для сигмоидной функции активации.
	void train_sigma(float delta, float n, float x);
	//Обучение для

};