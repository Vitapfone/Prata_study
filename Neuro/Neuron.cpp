
#include "pch.h"
//#define _USE_MATH_DEFINES //��� ���������� ��������.
#include <cmath>
#include "Neuron.h"



using namespace std;





//������� ��� ������ �� ����� ���� �����.
void Neuron::display(int width)
{
	int i = 0;
	for (Input & e : dendrits)
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

//������� �������. ��������� ��������� �������. ��������� ������ �������� � ������ ��������.
void Neuron::process(std::vector<bool>& input)
{
	//�������� �� ��, ��� �� ���� ����� ������ ����������� �������.
	if (input.size() != dendrits.size())
	{
		cout << "Error! Wrong input size!!" << endl;
		exit(1);
	}

	//������������ �������� �� �����.
	float sum = 0.0;

	for (size_t i = 0; i < dendrits.size(); i++)
	{
		sum += dendrits[i].weighing(input[i]);
	}

	//���������� ������������� �������. ���������� ��������� �������.
	y = activation(sum);
}

//�� �� ��� ���������� ������� ���������.
void Neuron::process_sigma(std::vector<float>& input)
{
	//�������� �� ��, ��� �� ���� ����� ������ ����������� �������.
	if (input.size() != dendrits.size())
	{
		cout << "Error! Wrong input size!!" << endl;
		exit(1);
	}

	//������������ �������� �� �����.
	float sum = 0.0;

	for (size_t i = 0; i < dendrits.size(); i++)
	{
		sum += dendrits[i].weighing_sigma(input[i]);
	}

	//���������� ������������� �������. ���������� ��������� �������.
	y = activation_sigma(sum);
}

//������� ��� �������� �������.
void Neuron::train(int d, float n, std::vector<bool>& input)
// d - �������� ����� �������, n - ����������� �������� ��������, � input - ��� �� ������� ������.
{
	for (size_t i = 0; i < dendrits.size(); i++)
	{
		//������ ���� �������� ���� ������� �����������.
		dendrits[i].train(d, y, n, input[i]);
	}
}

//�������� � ���������� ������������� ��������.
void Neuron::train_sigma(float d, float n, std::vector<float> & input)
{
	for (size_t i = 0; i < dendrits.size(); i++)
	{
		//������ ���� �������� ���� ������� �����������.
		dendrits[i].train_sigma(d, y, n, input[i]);
	}
}

//������� ��� ������ �������.
float Neuron::signal()
{
	return y;
}

//���������� ������� ���������.
bool Neuron::activation(float sum)
{
	if (sum >= tetha)
	{
		return true;
	}
	return false;
}

//���������� ���������.
float Neuron::activation_sigma(float sum)
{
	return 1 / (1 + pow(2.72, -sum));
}
