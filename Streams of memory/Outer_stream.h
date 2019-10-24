#pragma once
#include "pch.h"
#include "My_names.h"

using namespace My_names;

//��������� ������� ����� ������.
template<size_t W, size_t H>
using Outer_frame = array<array<char, W>, H>;

template<size_t W, size_t H>
class Outer_stream
{
	Outer_frame<W, H>			input_frame_;	//���� ������, � ������� ����� ��������� ������ ������� ���������� �������� ����.
	deque<Outer_frame<W, H>>	data_;			//����, � ������� ����� ��������������� ��������� ����� � ������� �� ������� ������.
	size_t						max_size_;		//������������ ������ ���� � ����� ������.

public:

//������������

	explicit Outer_stream(size_t max_sz = 100);

	~Outer_stream() {}

//���������

	//��������� �����������.
	Outer_stream(const Outer_stream & other) = delete;
	//��������� ������������.
	Outer_stream & operator=(const Outer_stream & other) = delete;

//������

//�������

	//�������� ������������ ������ ������.
	const size_t get_max_size() const { return max_size_; }

	//�������� ������� ������ ������.
	const size_t get_size() const { return data_.size(); }

	//�������� ��� ���������� ���� �����. �� ������ ������, � ����� ������ ������� �����.
	Outer_frame<W, H> & Input_frame() { return input_frame_; }

	//�������� ��� ������ ������������ ���� ������.
	const Outer_frame<W, H>  & get_ro_frame(size_t num) const;

//�������

	//���������� ����� ����. ������ ������.
	void set_max_size(size_t new_size) { max_size_ = new_size; }

//������

	//���������� ����� ����� �����.
	void print_input() const;

	//���������� ����� ����������� ������.
	//void play(unsigned dur) const;

	//������ ����� ������ � �����. ������� ������.
	void process();

	
private:

	//���������� ��������� ����.
	void print_frame(const Outer_frame<W, H> & fr) const;

	//����������� ���� �����.
	void prepare_for_input();
};

//����������� ���� �����.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::prepare_for_input()
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

//�����������.
template<size_t W, size_t H>
#pragma warning(suppress: 26495)
Outer_stream<W, H>::Outer_stream(size_t max_sz) : max_size_(max_sz)
{
	//�������������� ���� �����.
	prepare_for_input();

	//���� ��������� ������.
}


//���������� ��������� ����.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::print_frame(const Outer_frame<W, H> & fr) const
{
	for (size_t i = 0; i < H; ++i)//� ������ ������
	{

		for (size_t j = 0; j < W; ++j)//������������ ��� �������.
		{

			//����� ��� ��� ��������� ������� ������.
			if (i == 0 || i == H - 1)
			{
				cout << '=';
			}
			else if (j == 0 || j == W - 1)
			{
				cout << '!';
			}
			else
			{
				cout << fr[i][j];
			}
		}
		cout << endl;
	}
}


//�������� ��� ������ ������������ ���� ������.
template<size_t W, size_t H>
const Outer_frame<W, H> & Outer_stream<W, H>::get_ro_frame(size_t num) const
{
	//����������� � ���, ��� num ������ ��������� � ����� ����, �.�. ����, ����� ���� � ������� ������� ��� ������ �����.

	size_t len = data_.size();

	assert(num >= 0 && num < len);

	return data_[len - 1 - num];
}

//���������� ����� ����� �����.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::print_input() const
{
	print_frame(input_frame_);
}


//���������� ����� ����������� ������. �������� -- �������� ����� �� ������.
//template<size_t W, size_t H>
//void Outer_stream<W, H>::play(unsigned dur) const
//{
//	int i = 0;//������� ���������� ������.
//	
//	for (auto & e : data_)//������������ ��� �����.
//	{
//		print_frame(e);
//
//		cout << ++i << endl;
//
//		Sleep(dur);//��������. Windows.h
//		system("cls");//������� ����� �������.
//	}
//}

//������ ����� ������ � �����. ������� ������.
template<size_t W, size_t H>
void Outer_stream<W, H>::process()
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


