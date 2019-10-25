// Neuro.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Input.h"
#include "Neuron.h"

using namespace std;

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<float> & v);

//Функция для вывода содержимого вектора.
void display(vector<float> & v);

//Функция, в которой выполняется повторяющаяся работа.
void process(vector<float> & v, float d, float n, Neuron & N1);

int main()
{
	vector<float> data(25); //Вектор, в котором будут храниться входные данные для нейрона.

	Neuron N1(25, 1.0); //Нейрон с 25 входами и пределом чувствительности 1.

	float d; //Маркер желаемого результата.

	float n = 1.5f; //Коэффициент скорости обучения.

	char buf; //Буфер для управляющего символа.
	cout << "Any char for run. 0 for exit.\n";
	while (cin>>buf && buf != '0')
	{
		cin.ignore(1000, '\n');
		

		ifstream fin("Samples\\K.txt"); //Файловый поток для считывания данных.
		d = 1.0f; //Для этого варианта нейрон должен активироваться.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Второй пример.

		fin.open("Samples\\E.txt"); //Файловый поток для считывания данных.
		d = 0.0f; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Третий пример.

		fin.open("Samples\\Y.txt"); //Файловый поток для считывания данных.
		d = 0.0f; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);


		//Четвертый пример.

		fin.open("Samples\\R.txt"); //Файловый поток для считывания данных.
		d = 0.0f; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Пятый пример.


		fin.open("Samples\\U.txt"); //Файловый поток для считывания данных.
		d = 0.0f; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Шестой пример.

		fin.open("Samples\\S.txt"); //Файловый поток для считывания данных.
		d = 0.0f; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		cout <<"\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
				 \nType 0 for exit. Else one more run: ";
	}


	

	return 0;
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
			v[i] = 1.0;
			++i;
		}
		else if (buf == '0')
		{
			v[i] = 0.0;
			++i;
		}
	}
}

//Функция для вывода содержимого вектора.
void display(vector<float>& v)
{
	int i = 0;
	cout << endl;
	for (float e : v)
	{
		cout << e << ' ';
		++i;
		if (i % 5 == 0)
		{
			cout << endl;
		}
	}
	cout << endl;
}

//Функция, в которой выполняется повторяющаяся работа.
void process(vector<float>& data, float d, float n, Neuron & N1)
{
	//Показ для демонстрации правильности считывания.
	display(data);

	//Демонстрация весов до обучения.
	cout << "\nWeights BEFORE training:\n";
	N1.display(5);

	//Обработка данных.
	N1.process_sigma(data);

	//Демонстрация полученного результата.
	cout << "\nSignal is: " << N1.signal() << ". ";

	if (d == 1.0f)
	{
		if (N1.signal() >= 0.9*d)
		{
			cout << "Right!!\n";
		}
		else
		{
			cout << "Wrong!!\n";
		}
	}
	else if (d == 0.0f)
	{
		if (N1.signal() <= (d+0.1f))
		{
			cout << "Right!!\n";
		}
		else
		{
			cout << "Wrong!!\n";
		}
	}
	

	//Обучение.
	N1.train_sigma(d, n, data);

	//Веса после обучения.
	cout << "\nWeights AFTER training:\n";
	N1.display(5);
}
