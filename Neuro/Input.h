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

	//��������.
	void train(int d, bool y, float n, bool x);
};