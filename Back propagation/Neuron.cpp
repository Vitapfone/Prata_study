
#include "pch.h"
//#define _USE_MATH_DEFINES //Для встроенных констант.

#include "Neuron.h"



using namespace std;





//Функция для вывода на экран всех весов.
void Neuron::display(int width) const
{
	int i = 0;
	for (const Input & e : dendrits)
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

//То же для сигмоидной функции активации.
void Neuron::process_sigma(std::vector<Neuron>& previous_layer)
{
	//Проверка на то, что на вход подан вектор подходящего размера.
	if (previous_layer.size() != (dendrits.size()-1))
	{
		cout << "Error! Wrong input size!!" << endl;
		exit(1);
	}

	//Суммирование сигналов со входа.
	float sum = 0.0;

	size_t i;
	for ( i = 0; i < dendrits.size()-1; i++)
	{
		sum += dendrits[i].weighing_sigma(previous_layer[i].signal());
	}
	//Учитываем воображаемый нейрон смещения.
	sum = sum + dendrits[i].weighing_sigma(1.0);

	//Применение активационной функции. Вычисление состояния нейрона.
	y = activation_sigma(sum);
}

//Функция для обучения нейрона.
void Neuron::train(int d, float n, std::vector<bool>& input)
// d - желаемый ответ нейрона, n - коэффициент скорости обучения, а input - тот же входной вектор.
{
	//Вычисление ошибки.
	delta = d - y;

	for (size_t i = 0; i < dendrits.size(); i++)
	{
		
		//Каждый вход изменяет свой весовой коэффициент.
		dendrits[i].train(delta, n, input[i]);
	}
}

//Обучение с сигмоидной активационной функцией.
void Neuron::train_sigma(float d, float n, std::vector<Neuron> & previous_layer)
{
	//Вычисление ошибки.
	delta = (d - y)*y*(1 - y);

	size_t i;
	for (i = 0; i < dendrits.size()-1; i++)
	{
		//Каждый вход изменяет свой весовой коэффициент.
		dendrits[i].train_sigma(delta, n, previous_layer[i].signal());
	}
	//Учет воображаемого нейрона смещения.
	dendrits[i].train_sigma(delta, n, 1.0);
}

void Neuron::train_hidden_sigma (const vector<Neuron> & next_layer, float n, int number_of_neuron, const vector<Neuron> & previous_layer)
{
	// где num -- номер позиции этого нейрона в своем слое. Нужен для правильного определения номера входа нейрона следующего слоя при вычислении ошибки.

	//Вычисление ошибки.
	float sum = 0.0f;
	for (size_t i = 0; i < next_layer.size(); ++i)
	{
		sum += next_layer[i].get_delta() * next_layer[i].get_weight(number_of_neuron);
	}
	delta = y * (1 - y)*sum;

	size_t i;
	for ( i = 0; i < dendrits.size()-1; i++)
	{
		//Каждый вход изменяет свой весовой коэффициент.
		dendrits[i].train_sigma(delta, n, previous_layer[i].signal());
	}
	//Обучение входа смещения.
	dendrits[i].train_sigma(delta, n, 1.0);
}

//Функция для вывода сигнала.
float Neuron::signal() const
{
	return y;
}

//Выдать произвольный весовой коэффициент.
 float Neuron::get_weight(int i) const
{
	return dendrits[i].get_weight();
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

//Сигмоидная активация.
float Neuron::activation_sigma(float sum)
{
	return 1 / (1 + pow(2.72, -sum));
}
