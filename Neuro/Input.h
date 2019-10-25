#pragma once

//Для начала маленький класс, представляющий один вход нейрона.

class Input
{
	float w; //Весовой коэффициент сигнала для этого входа.

public:

	//Конструктор
	Input();

	//Геттер
	float get_weight() { return w; }

	//Взвешивание полученного сигнала.
	float weighing(bool x) { return w * x; }
	//Взвешивание для сигмоидной функции активации.
	float weighing_sigma(float x) { return w * x; }

	//Обучение.
	void train(int d, bool y, float n, bool x);
	//Обучение для сигмоидной функции активации.
	void train_sigma(float d, float y, float n, float x);

};