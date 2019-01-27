#include "pch.h"
#include "My_names.h"
#include "Function templates.h"
#include "Outer_stream.h"




Outer_stream::Outer_stream(size_t ms) : max_size(ms)
{
	//�������������� ���� ����� � ������ ������, �������� ��� ���������.
	for (auto &e : input_frame)
	{
		for (auto &e2 : e)
		{
			e2 = ' ';
		}
	}
	//���� ��������� ������.
}


//���������� ����� ����������� ������. �������� -- �������� ����� �� ������.
void Outer_stream::play(unsigned dur) const
{
	for (auto & e : data)//������������ ��� �����.
	{
		for (size_t i = 0; i < HEIGHT;++i)//� ������ ������
		{
			for (size_t j = 0; j < WIDTH; ++j)//������������ ��� �������.
			{
				//����� ��� ��� ��������� ������� ������.
				if (i == 0 || i == HEIGHT - 1)
				{
					cout << '=';
				}
				else if (j == 0 || j == WIDTH - 1)
				{
					cout << '!';
				}
				else
				{
					cout << e[i][j];
				}
			}
			cout << endl;
		}
		cout << endl;

		_sleep(dur);//��������.
		system("cls");//������� ����� �������.
	}
}
