#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Warning.h"

//Консольный вывод всей информации.
void Warning::what() const
{
	std::cout <<'\n'<< message
			<< "\nIn location (" << loc.x << ", " << loc.y << ").\n"
			<< "Importance " << importance << ".\n\n";
}

