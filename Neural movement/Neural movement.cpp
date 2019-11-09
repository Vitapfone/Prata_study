// Neural movement.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Обучение нейросети для управления движением к цели некоего объекта.

#include "pch.h"
#include "Neuron.h"

using namespace std;
using std::cout; using std::cin;

constexpr int NUM_OF_INPUT_NEURONS = 2;			//Количество нейронов входного слоя.
constexpr int NUM_OF_HIDDEN_NEURONS = 24;		//Количество нейронов скрытого слоя.
constexpr int NUM_OF_OUTPUT_NEURONS = 2;		//Количество нейронов выходного слоя.
constexpr int GENERAL_SPEED_MULT = 25;		//Общий множитель для скорости обучения.
constexpr float HIDDEN_SPEED = (1.0 / NUM_OF_INPUT_NEURONS) * GENERAL_SPEED_MULT;	//Коэффициент скорости обучения скрытого слоя. Зависит от количества входов, т.е. нейронов входного слоя/размерности входного вектора.
constexpr float OUTPUT_SPEED = (1.0 / NUM_OF_HIDDEN_NEURONS) * GENERAL_SPEED_MULT; //Скорость обучения для выходного слоя. Зависит от кол-ва нейронов скрытого.

//Настройки нормализации входа.
constexpr float MINIMAL_SIGNAL = -100.0F;//Минимальный входной сигнал. 
constexpr float MAXIMAL_SIGNAL = 100.0f;//Максимальный входной сигнал.
constexpr float TARGET_RANGE_MINIMUM = -1.0f;//Желаемый минимум сигнала.
constexpr float TARGET_RANGE_MAXIMUM = 1.0f;//Желаемый максимум сигнала.

//Функция для приведения входного сигнала к нужному диапазону.
float normalize(float current_signal, float minimal_signal, float maximal_signal, float target_range_minimum, float target_range_maximum);

int main()
{
	system("pause");//Пауза, чтоб успели запуститься средства диагностики.

//ПОДГОТОВКА ВХОДНЫХ ДАННЫХ.

	//Вектор кординат цели по оси икс.
	vector<float> target_xs{ -50.0f, 40.0f, -30.0f, 20.0f, -10.0f, 0.0f, 10.0f, -20.0f, 30.0f, -40.0f, 50.0f, -15.0f, 15.0f, -5.0f, 5.0f, -5.0f, 5.0f };
	//Вектор координат движущегося объекта по оси икс.
	vector<float> object_xs{ 0.0f };
	//Вектор координат движущегося объекта по оси игрек.
	vector<float> object_ys{ 10.0f };
	//Тестовые векторы.
	vector<float> test_xs{ 45.0f, 35.0f, 25.0f, 7.0f, 2.0f, 2.0f, 7.0f, 25.0f, 35.0f, 45.0f };//Вектор иксов.
	vector<float> test_ys{ 2.0f, 45.0f, 7.0f, 35.0f, 10.0f, 25.0f, 20.0f, 15.0f, 35.0f, 7.0f };//Вектор игреков.


//СОЗДАНИЕ СЕТИ

	//Тренировка будет идти для сети, воспринимающей только иксы, чтобы потом дублировать ее для игреков.

	//Создание входного слоя.
	vector<Neuron> input_layer(NUM_OF_INPUT_NEURONS);

	//Создание скрытого слоя.
	vector<Neuron> hidden_layer;
	for (size_t i = 0; i < NUM_OF_HIDDEN_NEURONS; ++i) //Слой содержит NUM_OF_HIDDEN_NEURONS нейронов.
	{
		Neuron N(NUM_OF_INPUT_NEURONS + 1);//Каждый нейрон имеет на 1 вход больше, чем размер предыдущего слоя. Последний вход всегда для смещения.
		hidden_layer.push_back(N);
	}

	//Создание выходного слоя.
	vector<Neuron> output_layer;
	for (size_t i = 0; i < NUM_OF_OUTPUT_NEURONS; ++i) 
	{
		Neuron N(NUM_OF_HIDDEN_NEURONS + 1);//Каждый нейрон имеет на 1 вход больше, чем размер предыдущего слоя. Последний вход всегда для смещения.
		output_layer.push_back(N);
	}


//ОБУЧАЮЩИЙ ЦИКЛ.

	for (float obj_x : object_xs)//Для каждого положения объекта
	{
		//надо перебрать все положения цели.
		for (float x : target_xs)
		{
			
			cout << "Target X is: " << x << ". ";

			while (obj_x!=x)//Обучение будет идти, пока объект не достигнет цели.
			{
				//Нормализация входа.
				float signal = normalize(x - obj_x, MINIMAL_SIGNAL, MAXIMAL_SIGNAL, TARGET_RANGE_MINIMUM, TARGET_RANGE_MAXIMUM);

				cout << "Signal is " << signal << ".\n\n";

				//Создание вектора данных.
				vector<float> data(2);
				if (signal < 0)
				{
					data[0] = 0.99f;
					data[1] = 0.01f;
				}
				else if (signal > 0)
				{
					data[0] = 0.01f;
					data[1] = 0.99f;
				}
				else
				{
					data[0] = 0.01f;
					data[1] = 0.01f;
				}


				//Инициализация входного слоя.
				for (size_t neuron_N = 0; neuron_N < NUM_OF_INPUT_NEURONS; neuron_N++)
				{
					input_layer[neuron_N].set_signal(data[neuron_N]); 
				}

				//Прямой ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
				{
					hidden_layer[neuron_number].process_sigma(input_layer);
				}

				//Прямой ход выходного слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_OUTPUT_NEURONS; neuron_number++)
				{
					output_layer[neuron_number].process_sigma(hidden_layer);
				}

				//Оглашение результатов. Сигнал первого выходного нейрона соответствует намерению сети двигаться влево, а второго -- вправо.
				cout << "Left signal is: " << setw(10) << output_layer[0].signal() << ". Right signal is: " << setw(10) << output_layer[1].signal() << ".\n\n";

				//Если уровень сигнала достаточно высок, то объект передвинется.
				auto output = output_layer[0].signal();
				if (output > 0.9f)
				{
					obj_x--;//Влево.
					cout << "To the left! " << obj_x << "  ";
				}
				output = output_layer[1].signal();
				if (output > 0.9f)
				{
					obj_x++;//Вправо.
					cout << "To the right! " << obj_x << "  ";
				}


				//Далее начинается обучение.
				//Создание вектора ответов.
				vector<float>answers(2);
				
				if (obj_x > x)//Если объект правее цели,
				{ 
					answers[0] = 0.99f;//то надо двигаться влево.
					answers[1] = 0.01f;
				}
				else if (obj_x == x)//Если достиг цели,
				{
					//то двигаться не надо.
					answers[0] = 0.01f;
					answers[1] = 0.01f;
				}
				else//Если левее,
				{
					answers[0] = 0.01f;
					answers[1] = 0.99f;//то надо вправо.
				}

				//Обратный ход выходного слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_OUTPUT_NEURONS; neuron_number++)
				{
					output_layer[neuron_number].train_sigma(answers[neuron_number], OUTPUT_SPEED, hidden_layer);
				}

				//Обратный ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
				{
					hidden_layer[neuron_number].train_hidden_sigma(output_layer, HIDDEN_SPEED, neuron_number, input_layer);
				}

			}//while (obj_x != x)//Обучение будет идти, пока объект не достигнет цели.

			cout << "\n\n/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
		}//надо перебрать все положения цели. for (float x : target_xs)

	}//for (float obj_x : object_xs)//Для каждого положения объекта

	cout << "GENERAL_SPEED_MULT = " << GENERAL_SPEED_MULT << "  HIDDEN_SPEED = " << HIDDEN_SPEED << "  OUTPUT_SPEED = " << OUTPUT_SPEED << endl;

//ТЕСТИРОВАНИЕ СЕТИ.

	cout << "\nTESTING\n\n" << "Any key for continue." << endl;
	cin.get();

	//Создание второй сети для движения по игреку. Она будет копией уже обученной сети.
	auto input_layer_2(input_layer);	//Входной слой.
	auto hidden_layer_2(hidden_layer);	//Скрытый слой.
	auto output_layer_2(output_layer);	//Выходной слой.

	float obj_x, obj_y;//Координаты объекта.

	for (size_t i = 0; i < object_xs.size(); ++i)//Для каждого положения объекта
	{
		obj_x = object_xs[i];
		obj_y = object_ys[i];

		float x, y;//Координаты цели.

		//надо перебрать все положения цели.
		for (size_t j=0; j<test_xs.size(); ++j)
		{
			x = test_xs[j];
			y = test_ys[j];
			cout << "Target X is: " << x << ", Y is " << y << ". ";

			while (obj_x != x)//Движение будет идти, пока объект не достигнет цели.
			{
				//Нормализация входа.
				//float signal = normalize(x - obj_x, MINIMAL_SIGNAL, MAXIMAL_SIGNAL, TARGET_RANGE_MINIMUM, TARGET_RANGE_MAXIMUM);

				float x_signal = x - obj_x;
				float y_signal = y - obj_y;
				cout << "X_signal is " << x_signal << ", Y_signal is "<<y_signal<<".\n\n";

				//Создание векторов данных.
				vector<float> data_x(2);//Для иксов.
				if (x_signal < 0)
				{
					data_x[0] = 0.99f;
					data_x[1] = 0.01f;
				}
				else if (x_signal > 0)
				{
					data_x[0] = 0.01f;
					data_x[1] = 0.99f;
				}
				else
				{
					data_x[0] = 0.01f;
					data_x[1] = 0.01f;
				}

				vector<float> data_y(2);//Для игреков.
				if (y_signal < 0)
				{
					data_y[0] = 0.99f;
					data_y[1] = 0.01f;
				}
				else if (x_signal > 0)
				{
					data_y[0] = 0.01f;
					data_y[1] = 0.99f;
				}
				else
				{
					data_y[0] = 0.01f;
					data_y[1] = 0.01f;
				}


				//Инициализация входного слоя.
				for (size_t neuron_N = 0; neuron_N < NUM_OF_INPUT_NEURONS; neuron_N++)
				{
					input_layer[neuron_N].set_signal(data_x[neuron_N]);
				}
				

				//Прямой ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
				{
					hidden_layer[neuron_number].process_sigma(input_layer);
				}

				//Прямой ход выходного слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_OUTPUT_NEURONS; neuron_number++)
				{
					output_layer[neuron_number].process_sigma(hidden_layer);
				}

				//Оглашение результатов. Сигнал первого выходного нейрона соответствует намерению сети двигаться влево, а второго -- вправо.
				cout << "Left signal is: " << setw(10) << output_layer[0].signal() << ". Right signal is: " << setw(10) << output_layer[1].signal() << ".\n\n";

				//Если уровень сигнала достаточно высок, то объект передвинется.
				auto output = output_layer[0].signal();
				if (output > 0.9f)
				{
					obj_x--;//Влево.
					cout << "To the left! " << obj_x << "  ";
				}
				output = output_layer[1].signal();
				if (output > 0.9f)
				{
					obj_x++;//Вправо.
					cout << "To the right! " << obj_x << "  ";
				}


				

			}//while (obj_x != x)

			cout << "\n\n/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
			cout << "\nTESTING\n\n" << "Any key for continue." << endl;
			cin.get();

		}//надо перебрать все положения цели. for (float x : target_xs)

	}//for (float obj_x : object_xs)//Для каждого положения объекта

	return 0;
}

//Функция для приведения входного сигнала к нужному диапазону.
float normalize(float current_signal, float minimal_signal, float maximal_signal, float target_range_minimum, float target_range_maximum)
{
	return ((current_signal - minimal_signal) / (maximal_signal - minimal_signal)) * (target_range_maximum - target_range_minimum) + target_range_minimum;
}
