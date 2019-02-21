#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

using Inner_frame = vector<vector<char>>;

class Inner_stream
{
	size_t				height		= 0;	//������ �����.
	size_t				width		= 0;	//������ �����.
	size_t				max_size	= 0;	//������������ ������ ���� � ����� ������.
	Inner_frame			input_frame;		//���� ������, � ������� ����� ��������� ������ �� �������� ������ (����� ������ ����������).
	deque<Inner_frame>	data;				//����, � ������� ����� ��������������� ��������� ����� � �������, ������� ������ ���� ���������.
	
public:

//������������

	Inner_stream(size_t w, size_t h, size_t l) : height(h), width(w), input_frame(Inner_frame(height, vector<char>(width, ' '))), max_size(l) {}


//���������

	//��������� �����������.
	Inner_stream(const Inner_stream & other) = delete;
	//��������� ������������.
	Inner_stream & operator=(const Inner_stream & other) = delete;


//������

//�������

	//�������� ������������ ������ ������.
	const size_t get_max_size() const { return max_size; }

	//�������� ������� ������ ������.
	const size_t get_size() const { return data.size(); }

	//�������� ��� ���������� ���� �����. �� ������ ������, � ����� ������ ������� �����.
	Inner_frame & Input_frame (){ return input_frame; }

	//�������� ��� ������ ������������ ���� ������.
	const Inner_frame & get_ro_frame(size_t num) const;
	//�������� ������������ ���� ��� ���������� ��������.
	Inner_frame & get_frame(size_t num);

//�������

	//���������� ����� ����. ������ ������.
	void set_max_size(size_t new_size) { max_size = new_size; }


//������

	//������ ����� ������ � �����. ������� ������.
	void process();

	//���������� ����� ����������� ������.
	//void play(unsigned dur);

private:

	//����������� ���� ����� ��� ���������� ����������.
	void prepare_for_input();
};

//��������� ������� ��� ��������� �����. Inner_stream.h
void print_frame(Inner_frame & fr);

//��������������� �-� ��� ��������� ����� � �������. ���� ����� ������� �������.  Inner_stream.h
void make_borders(Inner_frame &);