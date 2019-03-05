#include "pch.h"
#include "Inner_stream.h"

//�������� ��� ������ ������������ ���� ������.
const Inner_frame & Inner_stream::get_ro_frame(size_t num) const
{
	//����������� � ���, ��� num ������ ��������� � ����� ����, �.�. ����, ����� ���� � ������� ������� ��� ������ �����.

	size_t len = data_.size();

	assert(num >= 0 && num < len);

	return data_[len - 1 - num];
}

//�������� ������������ ���� ��� ���������� ��������.
Inner_frame & Inner_stream::get_frame(size_t num)
{
	//����������� � ���, ��� num ������ ��������� � ����� ����, �.�. ����, ����� ���� � ������� ������� ��� ������ �����.

	return const_cast<Inner_frame &> ((this)->get_ro_frame(num));
}

//����������� ���� ����� ��� ���������� ����������.
void Inner_stream::prepare_for_input()
{
	//�������������� ���� ����� � ������ ������, �������� ��� ���������.
	for (auto &e : input_frame_)
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
	//��������� ����������� ���� ����� � ����.
	data_.push_back(input_frame_);
	
	if (data_.size() > max_size_)//���� ������ ���� ��������� ��������, �� ������� ���� ���� �� ������, ��� ��������� ����� ������ ������. 
	{
		data_.pop_front();
	}

	//����������� ���� ����� ��� ���������� ����������.
	prepare_for_input();
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

//���������� ����� ����������� ������.
//void Inner_stream::play(unsigned dur)
//{
//	Inner_frame frame_copy;//����� �����, ����� �� ���������� ������� ������� �����(������ ��� �������� ��������� � �������) � ��� �����.
//	for (const auto & e : data_)
//	{
//		frame_copy = e;
//		print_frame(frame_copy);//������������ �����.
//
//		Sleep(dur);//��������. Windows.h
//		system("cls");//������� ����� �������.
//	}
//}

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
