#pragma once

using namespace My_names;

constexpr size_t WIDTH = 120;//���������, �������� ������ �������� ������������.
constexpr size_t HEIGHT = 60;//���������, �������� ������ �������� ������������.

using Frame = array<array<char, WIDTH>, HEIGHT>;

class Outer_stream
{
	Frame input_frame;//���� ������, � ������� ����� ��������� ������ ������� ���������� �������� ����.
	deque<Frame> data;//����, � ������� ����� ��������������� ��������� ����� � ������� �� ������� ������.
	size_t max_size;//������������ ������ ���� � ����� ������.

public:

//������������

	explicit Outer_stream(size_t ms = 100);
	~Outer_stream() {}

//���������
	//��������� �����������.
	Outer_stream(const Outer_stream & other) = delete;
	//��������� ������������.
	Outer_stream & operator=(const Outer_stream & other) = delete;

//������

//�������

	//�������� ������������ ������ ������.
	size_t get_max_size() const { return max_size; }

	//�������� ��� ���������� ���� �����. �� ������ ������, � ����� ������ ������� �����.
	Frame & Input_frame() { return input_frame; }

//�������

	//���������� ����� ����. ������ ������.
	void set_max_size(size_t new_size) { max_size = new_size; }

//������

	//���������� ����� ����������� ������.
	void play(unsigned dur) const;

};

