#pragma once

#include "pch.h"
#include "Input.h"

//����� ��� ������ �������� �������.

class Neuron
{
	std::vector<Input> dendrits; //��� ����� �������.

	float tetha = 1; //������ ����������������.

	float y = 0; //�������� ������ (���������) �������.

	float delta = 0.0; //������ �������.

public:

	//�����������. ������ ������ ���������� ������.
	Neuron(int num, float th) : dendrits(num), tetha(th) {}

	//������� ��� ������ �� ����� ���� �����.
	void display(int width);
	
	//������� �������. ��������� ��������� �������. ��������� ������ �������� � ������ ��������.
	void process(std::vector<bool> & input);
	//�� �� ��� ���������� ������� ���������.
	void process_sigma(std::vector<float> & input);

	//������� ��� �������� �������.
	void train(int d, float n, std::vector<bool> & input);
	//�������� � ���������� ������������� ��������.
	void train_sigma(float d, float n, std::vector<float> & input);

	//������� ��� ������ �������.
	float signal();

	//������� ��� ������ ������.
	float get_delta() { return delta; }

	//������ ������������ ������� �����������.
	float get_weight(int i);

private:

	//������� ���������.
	bool activation(float sum);
	//���������� ���������.
	float activation_sigma(float sum);
};

