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
			if (line.compare("/* columns rows colors chars-per-pixel */") == 0)
			{
				if (std::getline(inputFile, line))
				{
					_values = line.substr(1, line.size() - 3);
					break;
				}
			}
		}
		_columns = setValues();
		_rows = setValues();
		_colourCount = setValues();
		_charsPerPixel = setValues();
		fillTheMap(inputFile);
		convert(inputFile);
		inputFile.close();
	} 
	else 
	{
		std::cout << PINK << "HALP, THERE IS PROBLEM WITH THE FILE " << RESET_LINE;
	}

	// std::cout << PURPLE << "Columns:          " << GREEN << _columns << RESET_LINE;
	// std::cout << PURPLE << "Rows:             " << GREEN << _rows << RESET_LINE;
	// std::cout << PURPLE << "Colour count:     " << GREEN << _colourCount << RESET_LINE;
	// std::cout << PURPLE << "Chars per pixel:  " << GREEN << _charsPerPixel << RESET_LINE;
}

AsciiConverter::AsciiConverter(const AsciiConverter &copy)
{
	*this = copy;
}

AsciiConverter	&AsciiConverter::operator=(const AsciiConverter &copy)
{
	_columns = copy._columns;
	_rows = copy._rows;
	_colourCount = copy._colourCount;
	_charsPerPixel = copy._charsPerPixel;
	return (*this);
}

AsciiConverter::~AsciiConverter()
{

}

int	AsciiConverter::setValues()
{
	int var = stoi(_values.substr(0, _values.find(' ')));
	_values = _values.substr(_values.find(' ')+1, _values.size());
	return (var);
}

void	AsciiConverter::fillTheMap(std::ifstream &inputFile)
{
	std::string line;
	std::string key;
	std::string value;

	if (inputFile.is_open()) 
	{
		while (std::getline(inputFile, line) && line.compare("/* pixels */")) 
		{
			key = line.substr(1, line.find(' ')-1);
			value = line.substr(_charsPerPixel + 5, line.size() - 8);
			_myMap.insert(std::make_pair(key, value));
		}
	}
}

int AsciiConverter::hexToInt(const std::string& hex) 
{
    return std::stoi(hex, nullptr, 16);
}

void	AsciiConverter::convert(std::ifstream &inputFile)
{
	std::string line;

	if (inputFile.is_open()) 
	{
		while (std::getline(inputFile, line) && line.compare("};")) 
		{
			for (std::string::const_iterator it = line.begin(); it != line.end(); ++it)
			{
					// the rest of the program should be here 
			}
			std::cout << YELLOW << line << RESET_LINE;
			break;
		}
	}

}


// std::ostream &operator<<(std::ostream out, AsciiConverter const &art)
// {

// 	out << PURPLE << "Values:           " << GREEN << art._columns << RESET_LINE;
// 	out << GREEN << std::string(50, '+') << RESET_LINE;
// 	out << PURPLE << "Rows:             " << GREEN << art._rows << RESET_LINE;
// 	out << PURPLE << "Columns:          " << GREEN << art._columns << RESET_LINE;
// 	out << PURPLE << "Colour count:     " << GREEN << art._colourCount << RESET_LINE;
// 	out << PURPLE << "Chars per pixel:  " << GREEN << art._charsPerPixel << RESET_LINE;
// 	return (out);
// }