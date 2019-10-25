#pragma once

//��� ������ ��������� �����, �������������� ���� ���� �������.

class Input
{
	float w; //������� ����������� ������� ��� ����� �����.

public:

	//�����������
	Input();

	//������
	float get_weight() { return w; }

	//����������� ����������� �������.
	float weighing(bool x) { return w * x; }
	//����������� ��� ���������� ������� ���������.
	float weighing_sigma(float x) { return w * x; }

	//��������.
	void train(int d, bool y, float n, bool x);
	//�������� ��� ���������� ������� ���������.
	void train_sigma(float d, float y, float n, float x);

};