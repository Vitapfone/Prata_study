#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

using Inner_frame = vector<vector<char>>;

class Inner_stream
{
	size_t				height_		= 0;	//������ �����.
	size_t				width_		= 0;	//������ �����.
	size_t				max_size_	= 0;	//������������ ������ ���� � ����� ������.
	Inner_frame			input_frame_;		//���� ������, � ������� ����� ��������� ������ �� �������� ������ (����� ������ ����������).
	deque<Inner_frame>	data_;				//����, � ������� ����� ��������������� ��������� ����� � �������, ������� ������ ���� ���������.
	
public:

//������������

	Inner_stream(size_t w, size_t h, size_t l) : height_(h), width_(w), input_frame_(Inner_frame(height_, vector<char>(width_, ' '))), max_size_(l) {}


//���������

	//��������� �����������.
	Inner_stream(const Inner_stream & other) = delete;
	//��������� ������������.
	Inner_stream & operator=(const Inner_stream & other) = delete;


//������

//�������

	//�������� ������������ ������ ������.
	const size_t get_max_size() const { return max_size_; }

	//�������� ������� ������ ������.
	const size_t get_size() const { return data_.size(); }

	//�������� ��� ���������� ���� �����. �� ������ ������, � ����� ������ ������� �����.
	Inner_frame & Input_frame (){ return input_frame_; }

	//�������� ��� ������ ������������ ���� ������.
	const Inner_frame & get_ro_frame(size_t num) const;
	//�������� ������������ ���� ��� ���������� ��������.
	Inner_frame & get_frame(size_t num);

//�������

	//���������� ����� ����. ������ ������.
	void set_max_size(size_t new_size) { max_size_ = new_size; }


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