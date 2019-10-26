// Neuro.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Input.h"
#include "Neuron.h"

using namespace std;

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<float>> & samp, vector<float> & answ);

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<float> & v);

//Функция для вывода содержимого вектора.
void display(const vector<float> & v);

//Функция, в которой выполняется повторяющаяся работа.
void process(vector<float> & v, float d, float n, Neuron & N1);

int main()
{
	//Подготовка вектора обучающих примеров.

	vector < vector<float>> samples; //Вектор примеров.
	vector<float> answers;//Вектор ответов.
	preparation(samples, answers);


	Neuron N1(26, 1.0); //Нейрон с 26 входами и пределом чувствительности 1. Последний 26 вход для смещения.

	float n = 2.0f; //Коэффициент скорости обучения.

	char buf; //Буфер для управляющего символа.
	cout << "Any char for run. 0 for exit.\n";
	while (cin>>buf && buf != '0')
	{
		cin.ignore(1000, '\n');
		
		//Цикл обучения.
		for (int i = 0; i < samples.size(); ++i)
		{
			process(samples[i], answers[i], n, N1);
		}
		
		cout <<"\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
				 \nType 0 for exit. Else one more run: ";
	}


	

	return 0;
}

//Функция для подготовки обучающей выборки.
void preparation(vector<vector<float>>& samp, vector<float>& answ)
{
	vector<float> data(26); //Вектор, в котором будет храниться одиночный пример.
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

	answ = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
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
	v[25] = 1;//Тут как-бы входной нейрон смещения.
}

//Функция для вывода содержимого вектора.
void display( const vector<float>& v)
{
	int i = 0;
	cout << endl;
	for (const float e : v)
	{
		if (e == 0)
		{
			cout << ' ' << ' ';
		}
		else
		{
			cout << e << ' ';
		}
		
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

}
