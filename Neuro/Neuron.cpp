#include "pch.h"
#include "Neuron.h"

using namespace std;





//Функция для вывода на экран всех весов.
void Neuron::display(int width)
{
	int i = 0;
	for (Input & e : dendrits)
	{
		cout << setprecision(2);
		cout << setw(8) << e.get_weight() << ' ';
		++i;

		if (i % width == 0)
		{
			cout << endl;
		}
		
	}
	cout << endl;
}

//Главная функция. Вычисляет состояние нейрона. Принимает вектор сигналов с других нейронов.
void Neuron::process(std::vector<bool>& input)
{
	//Проверка на то, что на вход подан вектор подходящего размера.
	if (input.size() != dendrits.size())
	{
		cout << "Error! Wrong input size!!" << endl;
		exit(1);
	}

	//Суммирование сигналов со входа.
	float sum = 0.0;

	for (size_t i = 0; i < dendrits.size(); i++)
	{
		sum += dendrits[i].weighing(input[i]);
	}

	//Применение активационной функции. Вычисление состояния нейрона.
	y = activation(sum);
}

//Функция для обучения нейрона.
void Neuron::train(int d, float n, std::vector<bool>& input)
// d - желаемый ответ нейрона, n - коэффициент скорости обучения, а input - тот же входной вектор.
{
	for (size_t i = 0; i < dendrits.size(); i++)
	{
		//Каждый вход изменяет свой весовой коэффициент.
		dendrits[i].train(d, y, n, input[i]);
	}
}

//Функция для вывода сигнала.
bool Neuron::signal()
{
	return y;
}

//Простейшая функция активации.
bool Neuron::activation(float sum)
{
	if (sum >= tetha)
	{
		return true;
	}
	return false;
}
