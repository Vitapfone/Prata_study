// Back propagation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

using namespace std;

//Функция для чтения данных из файла.
void reading(ifstream & ifs, vector<float> & v);

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<float>> & samp, vector<vector<float>> & answ);

int main()
{
	//Подготовка вектора обучающих примеров.

	vector < vector<float>> samples; //Вектор примеров.
	vector < vector<float>> answers; //Вектор ответов.
	preparation(samples, answers);
}

//Функция для подготовки обучающей выборки.
void preparation(vector < vector<float>> & samp, vector<vector<float>> & answ)
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