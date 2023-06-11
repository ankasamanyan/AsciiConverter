#include "AsciiConverter.hpp"

AsciiConverter::AsciiConverter()
{

}

AsciiConverter::AsciiConverter(std::string stringy)
{
	std::ifstream	inputFile(stringy);
	std::string line;

	if (inputFile.is_open()) 
	{
		while (std::getline(inputFile, line)) 
		{
			if (line.compare("/* _columns _rows colors chars-per-pixel */") == 0)
			{
				if (std::getline(inputFile, line))
				{
					_values = line;
					std::cout << PURPLE << "THE LINE: " << GREEN << line << RESET_LINE;
					break;
				}
			}
		}
		inputFile.close();
	} else {
				std::cout << PINK << "HALP, THERE IS PROBLEM WITH THE FILE " << RESET_LINE;

		// Failed to open the file
		// Handle the error here
	}
	_values = line.substr(1, line.size() - 3);

	set_values(_columns);

}

AsciiConverter::AsciiConverter(const AsciiConverter &copy)
{
	_columns = copy._columns;
	_rows = copy._rows;
	_colourCount = copy._colourCount;
	_charsPerPixel = copy._charsPerPixel;
}

// AsciiConverter	&AsciiConverter::operator=(const AsciiConverter copy)
// {
	
// }

AsciiConverter::~AsciiConverter()
{

}

void	AsciiConverter::set_values(int var)
{
		value_array[i] = _values.substr(0, _values.find(' '));
		_values = _values.substr(_values.find(' ')+1, _values.size());
		std::cout << PURPLE << "THE VALUES: " << GREEN << value_array[i] << RESET_LINE;

}

