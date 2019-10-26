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
void Input::train(float delta, float n, bool x)
{
	w = w + n*delta*x; //������� �������� �������� ������-�������.
}
//�������� ��� ���������� ������� ���������.
void Input::train_sigma(float delta, float n, float x)
{
	w = w + n * delta*x;
}
