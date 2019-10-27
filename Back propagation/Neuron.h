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
	Neuron(int num = 1, float th = 1) : dendrits(num), tetha(th) {}

	//������� ��� ������ �� ����� ���� �����.
	void display(int width) const;
	
	//������� �������. ��������� ��������� �������. ��������� ������ �������� � ������ ��������.
	void process(std::vector<bool> & input);
	//�� �� ��� ���������� ������� ���������.
	void process_sigma(std::vector<Neuron> & previous_layer);

	//������� ��� �������� �������.
	void train(int d, float n, std::vector<bool> & input);
	//�������� � ���������� ������������� ��������.
	void train_sigma(float d, float n, std::vector<Neuron> & previous_layer);

	//�������� �������� ������� � ���������� ������������� ��������.
	void train_hidden_sigma(const std::vector<Neuron> & next_layer, float n, int num, const std::vector<Neuron> & previous_layer);

	//������� ��� ������ �������.
	float signal() const ;

	//������� ��� ������ ������.
	float get_delta() const { return delta; } 

	//������ ������������ ������� �����������.
	float get_weight(int i) const;

	//���������� ������. ������������ ��� �������� �������� ����.
	void set_signal(float new_signal) { y = new_signal; }

private:

	//������� ���������.
	bool activation(float sum);
	//���������� ���������.
	float activation_sigma(float sum);
};

