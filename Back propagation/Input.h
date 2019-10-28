#pragma once

//��� ������ ��������� �����, �������������� ���� ���� �������.

class Input
{
	float w; //������� ����������� ������� ��� ����� �����.
	

public:

	//�����������
	Input();

	//������
	float get_weight() const { return w; } 

	//����������� ����������� �������.
	float weighing(float x) { return w * x; }
	//����������� ��� ���������� ������� ���������.
	float weighing_sigma(float x) { return w * x; }

	//��������.
	void train(float delta, float n, float x);
	//�������� ��� ���������� ������� ���������.
	void train_sigma(float delta, float n, float x);
	//�������� ���

};