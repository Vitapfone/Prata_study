#include "pch.h"
#include "Warning.h"

//���������� ����� ���� ����������.
void Warning::what() const
{
	std::cout	<<'\n'<< message_
				<< "\nIn location (" << loc_.x_ << ", " << loc_.y_ << ").\n"
				<< "Importance " << importance_ << ".\n\n";
}

