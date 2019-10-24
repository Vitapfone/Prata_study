#pragma once

#include "pch.h"
#include "Input.h"

//����� ��� ������ �������� �������.

class Neuron
{
	std::vector<Input> dendrits; //��� ����� �������.

	float tetha = 1; //������ ����������������.

	bool y = 0; //�������� ������ (���������) �������.

public:

	//�����������. ������ ������ ���������� ������.
	Neuron(int num, float th) : dendrits(num), tetha(th) {}

	//������� ��� ������ �� ����� ���� �����.
	void display(int width);
	
	//������� �������. ��������� ��������� �������. ��������� ������ �������� � ������ ��������.
	void process(std::vector<bool> & input);

	//������� ��� �������� �������.
	void train(int d, float n, std::vector<bool> & input);

	//������� ��� ������ �������.
	bool signal();

private:

	//������� ���������.
	bool activation(float sum);
};

