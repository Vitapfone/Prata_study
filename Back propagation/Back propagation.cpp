// Back propagation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Neuron.h"

using namespace std;

//Функция для безопасного цифрового ввода.
size_t only_digits_input();

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<Neuron> & v);

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<Neuron>> & samp, vector<vector<float>> & answ);


constexpr int NUM = 25;		//Количество нейронов скрытого слоя.
constexpr int GENERAL_SPEED_MULT = 25;//Общий множитель для скорости обучения.
constexpr float HIDDEN_SPEED = 0.04 * GENERAL_SPEED_MULT;	//Коэффициент скорости обучения скрытого слоя. Зависит от количества входов, т.е. нейронов входного слоя/размерности входного вектора.
constexpr float OUTPUT_SPEED = (1.0 / NUM)*GENERAL_SPEED_MULT; //Скорость обуения для выходного слоя. Зависит от кол-ва нейронов скрытого.

int main()
{
	//Подготовка вектора обучающих примеров.
	vector < vector<Neuron>> samples; //Вектор входных нейронов для записи в них данных примеров.
	vector < vector<float>> answers; //Вектор ответов.
	preparation(samples, answers);


	//Создание скрытого слоя.
	vector<Neuron> hidden_layer;
	for (size_t i = 0; i < NUM; ++i) //Слой содержит 3 нейронов.
	{
		Neuron N(26);//Каждый нейрон имеет 26 входов. Последний вход всегда для смещения.
		hidden_layer.push_back(N);
	}

	//Создание выходного слоя.
	vector<Neuron> output_layer;
	for (size_t i = 0; i < 6; ++i) //Слой содержит 6 нейронов.
	{
		Neuron N(NUM+1);//Каждый нейрон имеет 26 входов.
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
				//Прямой ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM; neuron_number++)
				{
					hidden_layer[neuron_number].process_sigma(samples[i]);
				}

				//Прямой ход выходного слоя.
				for (size_t neuron_number = 0; neuron_number < 6; neuron_number++)
				{
					output_layer[neuron_number].process_sigma(hidden_layer);
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
				}

				//Обратный ход скрытого слоя.
				for (size_t neuron_number = 0; neuron_number < NUM; neuron_number++)
				{
					hidden_layer[neuron_number].train_hidden_sigma(output_layer, HIDDEN_SPEED, neuron_number, samples[i]);
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
	

}

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<Neuron>> & samp, vector<vector<float>> & answ)
{
	vector<Neuron> data(25); //Вектор входных нейронов, в котором будут храниться данные одиночного примера.
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

	vector<float> an = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	answ.push_back(an);
	an = { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	answ.push_back(an);
	an = { 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
	answ.push_back(an);
	an = { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
	answ.push_back(an);
	an = { 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	answ.push_back(an);
	an = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	answ.push_back(an);
}


//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<Neuron>& v)
{
	char buf;
	//Данные из файла транслируются в вектор.
	for (int i = 0; i < 25;)
	{
		ifs.get(buf);
		if (buf == '1')
		{
			v[i].set_signal(1.0);
			++i;
		}
		else if (buf == '0')
		{
			v[i].set_signal(0.0);
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