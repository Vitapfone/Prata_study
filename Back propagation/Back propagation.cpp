// Back propagation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Neuron.h"

using namespace std;

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<Neuron> & v);

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<Neuron>> & samp, vector<vector<float>> & answ);

//Функция, вобравшая в себя повторяющиеся действия обучения.
void process(vector < vector<Neuron>> & samp, vector<vector<float>> & answ, float n, vector<Neuron> & hidden, vector<Neuron> & out);

int main()
{
	//Подготовка вектора обучающих примеров.

	vector < vector<Neuron>> samples; //Вектор входных нейронов для записи в них данных примеров.
	vector < vector<float>> answers; //Вектор ответов.
	preparation(samples, answers);

	//Создание скрытого слоя.
	vector<Neuron> hidden_layer;
	for (size_t i = 0; i < 6; ++i) //Слой содержит 6 нейронов.
	{
		Neuron N(26);//Каждый нейрон имеет 26 входов. Последний вход всегда для смещения.
		hidden_layer.push_back(N);
	}

	//Создание выходного слоя.
	vector<Neuron> output_layer;
	for (size_t i = 0; i < 6; ++i) //Слой содержит 6 нейронов.
	{
		Neuron N(7);//Каждый нейрон имеет 7 входов.
		output_layer.push_back(N);
	}

	//Обучающий цикл.

	float n = 2.0f; //Коэффициент скорости обучения.

	char buf; //Буфер для управляющего символа.
	cout << "Any char for run. 0 for exit.\n";
	while (cin >> buf && buf != '0')
	{
		cin.ignore(1000, '\n');

		process(samples, answers, n, hidden_layer, output_layer);
		
		cout << "\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
				 \nType 0 for exit. Else one more run: ";
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

//Функция, вобравшая в себя повторяющиеся действия обучения.
void process(vector<vector<Neuron>>& samp, vector<vector<float>>& answ, float n, vector<Neuron>& hidden, vector<Neuron>& out)
{
	//Нейросети надо показывать 6 разных букв.
	for (size_t i = 0; i < 6; ++i)
	{
		//Прямой ход скрытого слоя.
		for (size_t j = 0; j < 6; j++)
		{
			hidden[j].process_sigma(samp[i]);
		}

		//Прямой ход выходного слоя.
		for (size_t j = 0; j < 6; j++)
		{
			out[j].process_sigma(hidden);
		}

		//Оглашение результатов.
		switch (i)
		{
		case 0:
			cout << "Variant K:\n";
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
		for (const Neuron & e : out)
		{
			cout << setw(7) << e.signal() << ' ';
		}
		cout << endl;

		//Далее начинается обучение.
		//Обратный ход выходного слоя.
		for (size_t j = 0; j < 6; j++)
		{
			out[j].train_sigma(answ[i][j], n, hidden);
		}

		//Обратный ход скрытого слоя.
		for (size_t j = 0; j < 6; j++)
		{
			hidden[j].train_hidden_sigma(out, n, j, samp[i]);
		}
	}
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