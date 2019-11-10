// Neural movement.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Обучение нейросети для управления движением к цели некоего объекта.

#include "pch.h"
#include "Neuron.h"
#include <SFML/Graphics.hpp>

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

//Настройки графики.
constexpr size_t WINDOW_WIDTH = 600;
constexpr size_t WINDOW_HEIGHT = 600;
constexpr int WINDOW_X = 50;
constexpr int WINDOW_Y = 50;
constexpr float SCALE = 10;
constexpr float SLEEP_TIME = 0.05f;

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



//ТЕСТИРОВАНИЕ СЕТИ. ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "\nTESTING\n\n" << "Any key for continue." << endl;
	cin.get();
	cin.ignore(1000, '\n');

	//Графика для наглядности.

	//Создание окна
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Neural movement");
	window.setPosition(sf::Vector2i(WINDOW_X, WINDOW_Y));

	//Включение вертикальной синхронизации.
	window.setVerticalSyncEnabled(true);

	//Кружок будет представлять наш объект.
	sf::CircleShape object(10.0f, 10);
	object.setFillColor(sf::Color::White);
	//Красный кружок будет целью.
	sf::CircleShape target(10.0f, 10);
	target.setFillColor(sf::Color::Red);

	//Создание второй сети для движения по игреку. Она будет копией уже обученной сети.
	auto input_layer_2(input_layer);	//Входной слой.
	auto hidden_layer_2(hidden_layer);	//Скрытый слой.
	auto output_layer_2(output_layer);	//Выходной слой.

	float obj_x, obj_y;//Координаты объекта.


		for (size_t i = 0; i < object_xs.size() && window.isOpen(); ++i)//Для каждого положения объекта
		{
			obj_x = object_xs[i];
			obj_y = object_ys[i];

			//Установление координат для видимого объекта.
			object.setPosition(obj_x * SCALE, WINDOW_HEIGHT - obj_y * SCALE - object.getRadius() * 2);//Манипуляции с координатами нужны для правильного отображения в окне и связаны с тем,
			//что СФМЛ считает координаты от левого верхнего угла, а также с тем, что координатами объекта считаются координаты левого верхнего угла описанного вокруг него прямоугольника.

			float x, y;//Координаты цели.




			//надо перебрать все положения цели.
			for (size_t j = 0; j < test_xs.size() && window.isOpen(); ++j)
			{
				x = test_xs[j];
				y = test_ys[j];

				//Установление координат для цели.
				target.setPosition(x * SCALE, WINDOW_HEIGHT - y * SCALE - target.getRadius() * 2);

				cout << "\nTarget X is: " << x << ", Y is " << y << ". ";


				while (((obj_x != x) || (obj_y != y)) && window.isOpen())//Движение будет идти, пока объект не достигнет цели.
				{

					//Проверка на событие закрытия окна.
					sf::Event event;
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
							window.close();
					}

					//Работа с графикой.
					//Задержка кадра для лучшего восприятия.
					sf::sleep(sf::seconds(SLEEP_TIME));
					window.clear(sf::Color::Black);
					window.draw(object);
					window.draw(target);
					window.display();
					


					float x_signal = x - obj_x;
					float y_signal = y - obj_y;
					cout << "X_signal is " << x_signal << ", Y_signal is " << y_signal << ".\n\n";

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
					else if (y_signal > 0)
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

					for (size_t neuron_N = 0; neuron_N < NUM_OF_INPUT_NEURONS; neuron_N++)
					{
						input_layer_2[neuron_N].set_signal(data_y[neuron_N]);
					}

					//Прямой ход скрытого слоя.
					for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
					{
						hidden_layer[neuron_number].process_sigma(input_layer);
					}

					for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
					{
						hidden_layer_2[neuron_number].process_sigma(input_layer_2);
					}

					//Прямой ход выходного слоя.
					for (size_t neuron_number = 0; neuron_number < NUM_OF_OUTPUT_NEURONS; neuron_number++)
					{
						output_layer[neuron_number].process_sigma(hidden_layer);
					}

					for (size_t neuron_number = 0; neuron_number < NUM_OF_OUTPUT_NEURONS; neuron_number++)
					{
						output_layer_2[neuron_number].process_sigma(hidden_layer_2);
					}

					//Оглашение результатов. Сигнал первого выходного нейрона соответствует намерению сети двигаться влево, а второго -- вправо.
					cout << "Left signal is: " << setw(10) << output_layer[0].signal() << ". Right signal is: " << setw(10) << output_layer[1].signal() << ".\n";
					//Для второй сети сигнал первого выходного нейрона соответствует движению вниз, а второго -- вверх.
					cout << "Down signal is: " << setw(10) << output_layer_2[0].signal() << ". Up signal is: " << setw(10) << output_layer_2[1].signal() << ".\n\n";


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
					output = output_layer_2[0].signal();
					if (output > 0.9f)
					{
						obj_y--;//Вниз.
						cout << "To the bottom! " << obj_y << "  ";
					}
					output = output_layer_2[1].signal();
					if (output > 0.9f)
					{
						obj_y++;//Вверх.
						cout << "To the top! " << obj_y << "  ";
					}

					object.setPosition(obj_x * SCALE, WINDOW_HEIGHT - obj_y * SCALE - object.getRadius() * 2);

				}//while (obj_x != x)

				if (window.isOpen())
				{
					cout << "\n\n/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
					cout << "\nTESTING\n\n" << "Any key for continue." << endl;
					//cin.get();
					//cin.ignore(1000, '\n');
				}
				//Проверка на событие закрытия окна при ожидании команды на следующий вариант положения цели. Чтобы продолжить тестирование надо ввести любой символ при
				//активном графическом окне.
				bool flag = true;
				while (flag)
				{
					sf::Event event;
					while (window.pollEvent(event))
					{
						if (event.type == sf::Event::Closed)
						{
							window.close();
							flag = false;
						}
							
						if (event.type == sf::Event::KeyPressed)
						{
							flag = false;
						}
					}
				}
				
				

			}//надо перебрать все положения цели. for (float x : target_xs)

		}//for (float obj_x : object_xs)//Для каждого положения объекта

	

	return 0;
}

//Функция для приведения входного сигнала к нужному диапазону.
float normalize(float current_signal, float minimal_signal, float maximal_signal, float target_range_minimum, float target_range_maximum)
{
	return ((current_signal - minimal_signal) / (maximal_signal - minimal_signal)) * (target_range_maximum - target_range_minimum) + target_range_minimum;
}
