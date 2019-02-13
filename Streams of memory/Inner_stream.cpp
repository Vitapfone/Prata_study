#include "pch.h"
#include "My_names.h"
#include "Inner_stream.h"

//�������� ��� ������ ������������ ���� ������.
const Inner_frame & Inner_stream::get_frame(size_t num) const
{
	//����������� � ���, ��� num ������ ��������� � ����� ����, �.�. ����, ����� ���� � ������� ������� ��� ������ �����.

	size_t len = data.size();

	if (data.empty())
	{
		throw std::logic_error("Empty stream!\n");
	}
	if (num < 0 || num >= len)
	{
		throw std::out_of_range("Out of range!\n");
	}
	return data[len - 1 - num];
}

//���������� ��� ���������� ��������.
Inner_frame & Inner_stream::get_frame(size_t num)
{
	//����������� � ���, ��� num ������ ��������� � ����� ����, �.�. ����, ����� ���� � ������� ������� ��� ������ �����.

	return const_cast<Inner_frame &> (const_cast<const Inner_stream* >(this)->get_frame(num));
}

//����������� ���� ����� ��� ���������� ����������.
void Inner_stream::prepare_for_input()
{
	//�������������� ���� ����� � ������ ������, �������� ��� ���������.
	for (auto &e : input_frame)
	{
		for (auto &e2 : e)
		{
			e2 = ' ';
		}
	}
}

//������ ����� ������ � �����. ������� ������.
void Inner_stream::process()
{
	data.push_back(input_frame);//��������� ����������� ���� ����� � ����.
	//cout << data.size() << ' ';
	if (data.size() > max_size)//���� ������ ���� ��������� ��������, �� ������� ���� ���� �� ������, ��� ��������� ����� ������ ������. 
	{
		//cout << max_size << endl;
		//cout << "???\n";
		data.pop_front();
	}

	prepare_for_input();//����������� ���� ����� ��� ���������� ����������.
}

//��������������� �-� ��� ��������� ����� � �������. ���� ����� ������� �������. 
void make_borders(Inner_frame & fr)
{
	size_t width = fr[0].size();
	size_t height = fr.size();

	for (int i = 0; i < width; ++i)
	{
		fr[0][i] = '=';
		fr[height - 1][i] = '=';
	}
	for (int j = 0; j < height; ++j)
	{
		fr[j][0] = '!';
		fr[j][width - 1] = '!';
	}
}

////������� ��������� ������ �����.
//void Inner_stream::print_frame(Inner_frame & fr)
//{
//	::print_frame(fr);
//}

//���������� ����� ����������� ������.
void Inner_stream::play(unsigned dur)
{
	Inner_frame frame_copy;//����� �����, ����� �� ���������� ������� ������� �����(������ ��� �������� ��������� � �������) � ��� �����.
	for (const auto & e : data)
	{
		frame_copy = e;
		print_frame(frame_copy);//������������ �����.

		Sleep(dur);//��������. Windows.h
		system("cls");//������� ����� �������.
	}
}

//��������� ������� ��� ��������� �����.
void print_frame(Inner_frame & fr)
{
	make_borders(fr);

	for (const auto &e : fr)// ������� � �������.
	{
		for (const auto &e2 : e)
		{
			cout << e2;
		}
		cout << endl;
	}
	cout << endl;
}
