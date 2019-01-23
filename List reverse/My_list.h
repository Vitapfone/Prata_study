#pragma once

using std::cout; using std::endl;

template<typename Item>
class My_list
{
	struct Node//��������� ��� ���� ������.
	{
		Item item; //���������� ����.
		Node* next = nullptr;//��������� �� ��������� ����.

		Node(const Item & it) { item = it; }
		~Node() {/* cout << "Node deleted.\n";*/ }
	};

	Node* front = nullptr;//��������� �� ������ ������.

public:

	My_list() { cout << "Empty My_list created.\n"; }//�������� ������� ������
	~My_list();
	
	void insert(const Item & it);//�������� ������� � ������ �� ������� ������.
	void show()const;//������� ��� ��-�� � �������.
	void reverse();//��������� ������� ��������� �� ��������.
};

//���������� ��������������� ����������� ������, ���������� ��� ���� �����.
template<typename Item>
inline My_list<Item>::~My_list()
{
	if (front != nullptr)
	{
		while (front->next != nullptr)
		{
			Node* temp = front;
			front = front->next;
			delete temp;
		}
		delete front;
	}
	cout << "My list deleted.\n";
}

//�������� ������� � ������ �� ������� ������.
template<typename Item>
inline void My_list<Item>::insert(const Item & it)
{
	Node* temp = new Node(it);
	temp->next = front;
	front = temp;
}

//������� ��� ��-�� � �������.
template<typename Item>
inline void My_list<Item>::show() const
{
	if (front != nullptr)
	{
		Node* temp = front;
		while (temp->next != nullptr)
		{
			cout << temp->item << ' ';
			temp = temp->next;
		}
		cout << temp->item << endl;
	}
	else
	{
		cout << "The list is empty!\n";
	}
}

//��������� ������� ��������� �� ��������.
template<typename Item>
inline void My_list<Item>::reverse()
{
	if (front != nullptr)//���� ������ �� ������.
	{
		if (front->next != nullptr)//������ ������ 1;
		{
			Node* old_front = front;//��������� �� ������ ��� ������ ������� ������ ("������ ������"). �� ��������� ������� ������ ��������� ��-���.
			Node* current = old_front->next;//��������� �� ��-�, ��������� �� ������ �������. ���� ��-� ����� "������������".

			while (current != nullptr)//���� �� ��������� ����� ������.
			{
				old_front->next = current->next;//������ ������ ������ ������� � ��-��� �� �������, ������� ������ ����� ����������.
				current->next = front;//������� ����������� � ����� �������,
				front = current;//� ��� ���������� ��.
				current = old_front->next;//������� ���������� ��-�, �������� ����� ��������� � ������.
			}
		}
		else
		{
			cout << "List size is 1.\n";
			return;
		}
	}
	else
	{
		cout << "The list is empty!\n";
	}
}
