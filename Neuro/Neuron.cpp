#include "pch.h"
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

//������� ��� ������ �������.
bool Neuron::signal()
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
