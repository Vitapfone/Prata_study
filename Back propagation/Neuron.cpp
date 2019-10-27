
#include "pch.h"
//#define _USE_MATH_DEFINES //��� ���������� ��������.

#include "Neuron.h"



using namespace std;





//������� ��� ������ �� ����� ���� �����.
void Neuron::display(int width) const
{
	int i = 0;
	for (const Input & e : dendrits)
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
void Neuron::process_sigma(std::vector<Neuron>& previous_layer)
{
	//�������� �� ��, ��� �� ���� ����� ������ ����������� �������.
	if (previous_layer.size() != (dendrits.size()-1))
	{
		cout << "Error! Wrong input size!!" << endl;
		exit(1);
	}

	//������������ �������� �� �����.
	float sum = 0.0;

	size_t i;
	for ( i = 0; i < dendrits.size()-1; i++)
	{
		sum += dendrits[i].weighing_sigma(previous_layer[i].signal());
	}
	//��������� ������������ ������ ��������.
	sum = sum + dendrits[i].weighing_sigma(1.0);

	//���������� ������������� �������. ���������� ��������� �������.
	y = activation_sigma(sum);
}

//������� ��� �������� �������.
void Neuron::train(int d, float n, std::vector<bool>& input)
// d - �������� ����� �������, n - ����������� �������� ��������, � input - ��� �� ������� ������.
{
	//���������� ������.
	delta = d - y;

	for (size_t i = 0; i < dendrits.size(); i++)
	{
		
		//������ ���� �������� ���� ������� �����������.
		dendrits[i].train(delta, n, input[i]);
	}
}

//�������� � ���������� ������������� ��������.
void Neuron::train_sigma(float d, float n, std::vector<Neuron> & previous_layer)
{
	//���������� ������.
	delta = (d - y)*y*(1 - y);

	size_t i;
	for (i = 0; i < dendrits.size()-1; i++)
	{
		//������ ���� �������� ���� ������� �����������.
		dendrits[i].train_sigma(delta, n, previous_layer[i].signal());
	}
	//���� ������������� ������� ��������.
	dendrits[i].train_sigma(delta, n, 1.0);
}

void Neuron::train_hidden_sigma (const vector<Neuron> & next_layer, float n, int number_of_neuron, const vector<Neuron> & previous_layer)
{
	// ��� num -- ����� ������� ����� ������� � ����� ����. ����� ��� ����������� ����������� ������ ����� ������� ���������� ���� ��� ���������� ������.

	//���������� ������.
	float sum = 0.0f;
	for (size_t i = 0; i < next_layer.size(); ++i)
	{
		sum += next_layer[i].get_delta() * next_layer[i].get_weight(number_of_neuron);
	}
	delta = y * (1 - y)*sum;

	size_t i;
	for ( i = 0; i < dendrits.size()-1; i++)
	{
		//������ ���� �������� ���� ������� �����������.
		dendrits[i].train_sigma(delta, n, previous_layer[i].signal());
	}
	//�������� ����� ��������.
	dendrits[i].train_sigma(delta, n, 1.0);
}

//������� ��� ������ �������.
float Neuron::signal() const
{
	return y;
}

//������ ������������ ������� �����������.
 float Neuron::get_weight(int i) const
{
	return dendrits[i].get_weight();
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
