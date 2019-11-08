// Back propagation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Neuron.h"

using namespace std;

//Функция для безопасного цифрового ввода.
size_t only_digits_input();

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<float> & v);

//Функция для подготовки обучающей и тестовой выборок.
void preparation(vector < vector<float>> & samp, vector<vector<float>> & answ, vector<vector<float>> & test);


constexpr int NUM_OF_HIDDEN_NEURONS = 12;		//Количество нейронов скрытого слоя.
constexpr int GENERAL_SPEED_MULT = 1;//Общий множитель для скорости обучения.
constexpr float HIDDEN_SPEED = 0.04 * GENERAL_SPEED_MULT;	//Коэффициент скорости обучения скрытого слоя. Зависит от количества входов, т.е. нейронов входного слоя/размерности входного вектора.
constexpr float OUTPUT_SPEED = (1.0 / NUM_OF_HIDDEN_NEURONS)*GENERAL_SPEED_MULT; //Скорость обуения для выходного слоя. Зависит от кол-ва нейронов скрытого.

int main()
{
	//Подготовка вектора обучающих примеров.
	vector < vector<float>> samples; //Вектор для данных примеров.
	vector < vector<float>> answers; //Вектор ответов.
	vector<vector<float>> tests; //Вектор для тестовых образов.
	preparation(samples, answers, tests);

	//Создание входного слоя.
	vector<Neuron> input_layer(25);//25 входных нейронов.
	
	//Создание скрытого слоя.
	vector<Neuron> hidden_layer;
	for (size_t i = 0; i < NUM_OF_HIDDEN_NEURONS; ++i) //Слой содержит NUM нейронов.
	{
		int size = input_layer.size() + 1;//Каждый нейрон имеет на 1 вход больше, чем размер предыдущего слоя. Последний вход всегда для смещения.
		Neuron N(size);
		hidden_layer.push_back(N);
	}

	//Создание выходного слоя.
	vector<Neuron> output_layer;
	for (size_t i = 0; i < 6; ++i) //Слой содержит 6 нейронов.
	{
		Neuron N(NUM_OF_HIDDEN_NEURONS+1);//Каждый нейрон имеет на 1 вход больше, чем размер предыдущего слоя. Последний вход всегда для смещения.
		output_layer.push_back(N);
	}


	//Обучающий цикл.

	size_t num_of_epochs; //Количество нужных эпох обучения.
	size_t count = 0; //Счетчик прошедших эпох.

	cout << "Enter number of epochs. 0 for exit.\n";
	num_of_epochs = only_digits_input();

	while (num_of_epochs != 0)
	{
		for (size_t e = 0; e < num_of_epochs; ++e)
		{
			//Нейросети надо показывать 6 разных букв.
			for (size_t i = 0; i < 6; ++i)
			{
				//Инициализация входного слоя.
				for (size_t neuron_N = 0; neuron_N < 25; neuron_N++)
				{
					input_layer[neuron_N].set_signal(samples[i][neuron_N]);
				}

				//Прямой ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
				{
					hidden_layer[neuron_number].process_sigma(input_layer);
					//hidden_layer[neuron_number].process(samples[i]);
				}

				//Прямой ход выходного слоя.
				for (size_t neuron_number = 0; neuron_number < 6; neuron_number++)
				{
					output_layer[neuron_number].process_sigma(hidden_layer);
					//output_layer[neuron_number].process(hidden_layer);
				}

				//Оглашение результатов.
				switch (i)
				{
				case 0:
					cout << "\n\nVariant K:\n";
					break;
				case 1:
					cout << "Variant E:\n";
					break;
				case 2:
					cout << "Variant Y:\n";
					break;
				case 3:
					cout << "Variant R:\n";
					break;
				case 4:
					cout << "Variant U:\n";
					break;
				case 5:
					cout << "Variant S:\n";
					break;
				default:
					break;
				}

				cout << setprecision(3);
				for (const Neuron & e : output_layer)
				{
					cout << setw(10) << e.signal() << ' ';
				}
				cout << endl;

				//Далее начинается обучение.
				//Обратный ход выходного слоя.
				for (size_t neuron_number = 0; neuron_number < 6; neuron_number++)
				{
					output_layer[neuron_number].train_sigma(answers[i][neuron_number], OUTPUT_SPEED, hidden_layer);
					//output_layer[neuron_number].train(answers[i][neuron_number], OUTPUT_SPEED, hidden_layer);
				}

				//Обратный ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
				{
					hidden_layer[neuron_number].train_hidden_sigma(output_layer, HIDDEN_SPEED, neuron_number, input_layer);
					//hidden_layer[neuron_number].train_hidden(output_layer, HIDDEN_SPEED, neuron_number, samples[i]);
				}
			}

			++count;
			cout << "\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
				 \nEpoch " << count << endl;
		}

		
		cout << "GENERAL_SPEED_MULT = " << GENERAL_SPEED_MULT << "  HIDDEN_SPEED = " << HIDDEN_SPEED << "  OUTPUT_SPEED = " << OUTPUT_SPEED << endl;
		cout << "Enter number of epochs. 0 for exit.\n";
		num_of_epochs = only_digits_input();
	}
	
	/*for (const Neuron & e : output_layer)
	{
		e.display(10);
	}*/

	//Проверка обобщающей способности сети.
	cout << "\nTESTING\n\n";

	float sum_k = 0.0f;
	float sum_u = 0.0f;

	for (size_t i = 0; i < tests.size(); i++)
	{
		//Инициализация входного слоя.
		for (size_t neuron_N = 0; neuron_N < 25; neuron_N++)
		{
			input_layer[neuron_N].set_signal(tests[i][neuron_N]);
		}
		//Прямой ход скрытого слоя.
		for (size_t neuron_number = 0; neuron_number < NUM_OF_HIDDEN_NEURONS; neuron_number++)
		{
			hidden_layer[neuron_number].process_sigma(input_layer);
		}
		//Прямой ход выходного слоя.
		for (size_t neuron_number = 0; neuron_number < 6; neuron_number++)
		{
			output_layer[neuron_number].process_sigma(hidden_layer);
		}

		//Вывод сигналов выходного слоя.
		cout << setprecision(3);
		
		int j = 0;
		for (const Neuron & e : output_layer)
		{
			//Суммирование отдельных сигналов для вычисления их средних значений.
			if (j == 0 && i<=5)
			{
				sum_k += e.signal();
			}
			else if (j == 4 && i>5)
			{
				sum_u += e.signal();
			}
			++j;
			
			cout << setw(10) << e.signal() << ' ';
		}
		if (i == 5 || i==11)
		{
			cout << endl;
		}
		cout << endl;

		
	}

	cout << "K generalization is: " << (sum_k / 6) << ". U generalization is: " << (sum_u / 6) << ".\n";

	return 0;
}

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<float>> & samp, vector<vector<float>> & answ, vector<vector<float>> & test)
{
	vector<float> data(25); //Вектор входных нейронов, в котором будут храниться данные одиночного примера.
	ifstream fin("Samples\\K.txt"); //Файловый поток для считывания данных.
	
	//Чтение.
	reading(fin, data);
	fin.close();
	samp.push_back(data);
	fin.open("Samples\\E.txt");
	reading(fin, data);
	fin.close();
	samp.push_back(data);
	fin.open("Samples\\Y.txt");
	reading(fin, data);
	fin.close();
	samp.push_back(data);
	fin.open("Samples\\R.txt");
	reading(fin, data);
	fin.close();
	samp.push_back(data);
	fin.open("Samples\\U.txt");
	reading(fin, data);
	fin.close();
	samp.push_back(data);
	fin.open("Samples\\S.txt");
	reading(fin, data);
	fin.close();
	samp.push_back(data);

	vector<float> an = { 0.99f, 0.01f, 0.01f, 0.01f, 0.01f, 0.01f };
	answ.push_back(an);
	an = { 0.01f, 0.99f, 0.01f, 0.01f, 0.01f, 0.01f };
	answ.push_back(an);
	an = { 0.01f, 0.01f, 0.99f, 0.01f, 0.01f, 0.01f };
	answ.push_back(an);
	an = { 0.01f, 0.01f, 0.01f, 0.99f, 0.01f, 0.01f };
	answ.push_back(an);
	an = { 0.01f, 0.01f, 0.01f, 0.01f, 0.99f, 0.01f };
	answ.push_back(an);
	an = { 0.01f, 0.01f, 0.01f, 0.01f, 0.01f, 0.99f };
	answ.push_back(an);

	
	//Заполнение вектора тестов.
	
	fin.open("Tests\\K1.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\K2.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\K3.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\K4.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\K5.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\K6.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);

	fin.open("Tests\\U1.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\U2.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\U3.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\U4.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\U5.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
	fin.open("Tests\\U6.txt");
	reading(fin, data);
	fin.close();
	test.push_back(data);
}


//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<float>& v)
{
	char buf;
	//Данные из файла транслируются в вектор.
	for (int i = 0; i < 25;)
	{
		ifs.get(buf);
		if (buf == '1')
		{
			v[i] = 0.99f;
			++i;
		}
 		else if (buf == '0')
		{
			v[i] = 0.01f;
			++i;
		}
	}
	
}

//Обработка цифрового ввода.
size_t only_digits_input()
{
	size_t ln;

	while (!(cin >> ln))
	{
		cout << "Only digits!\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return ln;
}