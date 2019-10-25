#include "pch.h"
#include "Input.h"


using namespace std;

//Нужно для рандомизации начального значения весового коэффициента.

mt19937 engine(12342); //Вихрь мерсенна.
uniform_real_distribution<float> dist(-0.99, 1.0);//Распределение для чисел с плавающей запятой.

Input::Input()
{
	//Вес получает случайноге значение.
	w = dist(engine);
}

//Обучение. d - желаемый ответ нейрона, n - коэффициент скорости обучения, а x -- входной сигнал.
void Input::train(int d, bool y, float n, bool x)
{
	w = w + (d - y)*n*x; //Формула обучения согласно Дельта-правилу.
}
//Обучение для сигмоидной функции активации.
void Input::train_sigma(float d, float y, float n, float x)
{
	w = w + (d - y)*y*(1 - y)*x;
}
