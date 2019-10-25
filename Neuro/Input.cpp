#include "pch.h"
#include "Input.h"


using namespace std;

//����� ��� ������������ ���������� �������� �������� ������������.

mt19937 engine(12342); //����� ��������.
uniform_real_distribution<float> dist(-0.99, 1.0);//������������� ��� ����� � ��������� �������.

Input::Input()
{
	//��� �������� ���������� ��������.
	w = dist(engine);
}

//��������. d - �������� ����� �������, n - ����������� �������� ��������, � x -- ������� ������.
void Input::train(int d, bool y, float n, bool x)
{
	w = w + (d - y)*n*x; //������� �������� �������� ������-�������.
}
//�������� ��� ���������� ������� ���������.
void Input::train_sigma(float d, float y, float n, float x)
{
	w = w + (d - y)*y*(1 - y)*x;
}
