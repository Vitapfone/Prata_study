#pragma once

using std::cout; using std::endl;

template<typename Item>
class My_list
{
	struct Node//Структура для узла списка.
	{
		Item item; //Содержимое узла.
		Node* next = nullptr;//Указатель на следующий узел.

		Node(const Item & it) { item = it; }
		~Node() {/* cout << "Node deleted.\n";*/ }
	};

	Node* front = nullptr;//Указатель на голову списка.

public:

	My_list() { cout << "Empty My_list created.\n"; }//Создание пустого списка
	~My_list();
	
	void insert(const Item & it);//Добавить элемент в список со стороны головы.
	void show()const;//Вывести все эл-ты в консоль.
	void reverse();//Изменение порядка элементов на обратный.
};

//Деструктор последовательно освобождает память, выделенную для всех узлов.
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

//Добавить элемент в список со стороны головы.
template<typename Item>
inline void My_list<Item>::insert(const Item & it)
{
	Node* temp = new Node(it);
	temp->next = front;
	front = temp;
}

//Вывести все эл-ты в консоль.
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

//Изменение порядка элементов на обратный.
template<typename Item>
inline void My_list<Item>::reverse()
{
	if (front != nullptr)//Если список не пустой.
	{
		if (front->next != nullptr)//Размер больше 1;
		{
			Node* old_front = front;//Указатель на голову при прямом порядке списка ("старая голова"). По окончанию реверса станет последним эл-том.
			Node* current = old_front->next;//Указатель на эл-т, следующий за старой головой. Этот эл-т будет "перемещаться".

			while (current != nullptr)//Пока не достигнут конец списка.
			{
				old_front->next = current->next;//Старая голова теперь связана с эл-том за текущим, который теперь можно перемещать.
				current->next = front;//Текущий связывается с новой головой,
				front = current;//и сам становится ею.
				current = old_front->next;//Текущим становится эл-т, стоявший ранее следующим в списке.
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
