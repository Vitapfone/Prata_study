#pragma once

using namespace My_names;


template<size_t W, size_t H>
class Outer_stream
{

	using Frame = array<array<char, W>, H>;

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
	const size_t get_max_size() const { return max_size; }

	//�������� ������� ������ ������.
	const size_t get_size() const { return data.size(); }

	//�������� ��� ���������� ���� �����. �� ������ ������, � ����� ������ ������� �����.
	Frame & Input_frame() { return input_frame; }

	//�������� ��� ������ ������������ ���� ������.
	const Frame  & get_frame(size_t num) const;

//�������

	//���������� ����� ����. ������ ������.
	void set_max_size(size_t new_size) { max_size = new_size; }

//������

	//���������� ����� ����� �����.
	void print_input() const;

	//���������� ����� ����������� ������.
	void play(unsigned dur) const;

	//������ ����� ������ � �����. ������� ������.
	void process();

	
private:

	//���������� ��������� ����.
	void print_frame(Frame fr) const;

	//����������� ���� �����.
	void prepare_for_input();
};

//����������� ���� �����.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::prepare_for_input()
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

//�����������.
template<size_t W, size_t H>
Outer_stream<W, H>::Outer_stream(size_t ms) : max_size(ms)
{
	//�������������� ���� �����.
	prepare_for_input();

	//���� ��������� ������.
}


//���������� ��������� ����.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::print_frame(Frame fr) const
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
const typename Outer_stream<W, H>::Frame & Outer_stream<W, H>::get_frame(size_t num) const
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

//���������� ����� ����� �����.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::print_input() const
{
	print_frame(input_frame);
}


//���������� ����� ����������� ������. �������� -- �������� ����� �� ������.
template<size_t W, size_t H>
void Outer_stream<W, H>::play(unsigned dur) const
{
	int i = 0;//������� ���������� ������.
	
	for (auto & e : data)//������������ ��� �����.
	{
		print_frame(e);

		cout << ++i << endl;

		Sleep(dur);//��������. Windows.h
		system("cls");//������� ����� �������.
	}
}

//������ ����� ������ � �����. ������� ������.
template<size_t W, size_t H>
void Outer_stream<W, H>::process()
{
	//cout << "Processing...\n";
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


