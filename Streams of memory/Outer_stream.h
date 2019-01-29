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

	//�������� ��� ���������� ���� �����. �� ������ ������, � ����� ������ ������� �����.
	Frame & Input_frame() { return input_frame; }

//�������

	//���������� ����� ����. ������ ������.
	void set_max_size(size_t new_size) { max_size = new_size; }

//������

	//���������� ����� ����������� ������.
	void play(unsigned dur) const;

	//������ ����� ������ � �����. ������� ������.
	void process();

private:

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

//���������� ����� ����������� ������. �������� -- �������� ����� �� ������.
template<size_t W, size_t H>
void Outer_stream<W, H>::play(unsigned dur) const
{
	int i = 0;//������� ���������� ������.
	
	for (auto & e : data)//������������ ��� �����.
	{
		//cout << "Frames...\n";
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
					cout << e[i][j];
				}
			}
			cout << endl;
		}
		cout << ++i << endl;

		Sleep(dur);//��������. Windows.h
		system("cls");//������� ����� �������.
	}
}

//������ ����� ������ � �����. ������� ������.
template<size_t W, size_t H>
inline void Outer_stream<W, H>::process()
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


