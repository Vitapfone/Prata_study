#include "pch.h"
#include "Warning.h"

void Warning::what() const
{
	std::cout <<'\n'<< message
			<< "\nIn location (" << loc.x << ", " << loc.y << ").\n"
			<< "Importance " << importance << ".\n\n";
}

