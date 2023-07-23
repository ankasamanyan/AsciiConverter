#include "AsciiConverter.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		Utils::printMsg("Give the xpm file as argument", ORANGE);
		return -1;
	}
	if (argv[1])
		AsciiConverter atrsie(argv[1]);
	return 0;
}
