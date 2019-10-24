// Neuro.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Input.h"
#include "Neuron.h"

using namespace std;

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<bool> & v);

//Функция для вывода содержимого вектора.
void display(vector<bool> & v);

//Функция, в которой выполняется повторяющаяся работа.
void process(vector<bool> & v, int d, float n, Neuron & N1);

int main()
{
	vector<bool> data(25); //Вектор, в котором будут храниться входные данные для нейрона.

	Neuron N1(25, 1.0); //Нейрон с 25 входами и пределом чувствительности 1.

	int d; //Маркер желаемого результата.

	float n = 0.1; //Коэффициент скорости обучения.

	char buf; //Буфер для управляющего символа.
	cout << "Any char for run. 0 for exit.\n";
	while (cin>>buf && buf != '0')
	{
		cin.ignore(1000, '\n');
		

		ifstream fin("Samples\\K.txt"); //Файловый поток для считывания данных.
		d = 1; //Для этого варианта нейрон должен активироваться.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Второй пример.

		fin.open("Samples\\E.txt"); //Файловый поток для считывания данных.
		d = 0; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Третий пример.

		fin.open("Samples\\Y.txt"); //Файловый поток для считывания данных.
		d = 0; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);


		//Четвертый пример.

		fin.open("Samples\\R.txt"); //Файловый поток для считывания данных.
		d = 0; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Пятый пример.


		fin.open("Samples\\U.txt"); //Файловый поток для считывания данных.
		d = 0; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		//Шестой пример.

		fin.open("Samples\\S.txt"); //Файловый поток для считывания данных.
		d = 0; //Для этого варианта нейрон должен оставаться пассивным.

		//Чтение.
		reading(fin, data);

		fin.close();

		//Основная работа по обучению и демонстрации.
		process(data, d, n, N1);

		cout << "Type 0 for exit. Else one more run: ";
	}


	

	return 0;
}


//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<bool>& v)
{
	char buf;
	//Данные из файла транслируются в вектор.
	for (int i = 0; i < 25;)
	{
		ifs.get(buf);
		if (buf == '1')
		{
			v[i] = true;
			++i;
		}
		else if (buf == '0')
		{
			v[i] = false;
			++i;
		}
	}
}

//Функция для вывода содержимого вектора.
void display(vector<bool>& v)
{
	int i = 0;
	cout << endl;
	for (bool e : v)
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
void process(vector<bool>& data, int d, float n, Neuron & N1)
{
	//Показ для демонстрации правильности считывания.
	display(data);

	//Демонстрация весов до обучения.
	cout << "\nWeights BEFORE training:\n";
	N1.display(5);

	//Обработка данных.
	N1.process(data);

	//Демонстрация полученного результата.
	cout << "\nSignal is: " << N1.signal() << ". ";

	if (N1.signal() == d)
	{
		cout << "Right!!\n";
	}
	else
	{
		cout << "Wrong!!\n";
	}

	//Обучение.
	N1.train(d, n, data);

	//Веса после обучения.
	cout << "\nWeights AFTER training:\n";
	N1.display(5);
}
