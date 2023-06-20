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
	_values = _values.substr(_values.find(' ') + 1, _values.size());
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
			key = line.substr(1, _charsPerPixel);
			value = "0x" + line.substr(_charsPerPixel + 5, 6);
			_myMap.insert(std::make_pair(key, value));
		}
	}
}

int AsciiConverter::hexToInt(const std::string &hex) 
{
    return std::stoi(hex, nullptr, 16);
}

void	AsciiConverter::convert(std::ifstream &inputFile)
{
	std::string line;
  	struct RGB rgbColor;

	if (inputFile.is_open()) 
	{
		while (std::getline(inputFile, line) && line.compare("};")) 
		{
			size_t  ind = 1;
		    std::string colour;
		    for (size_t i = 0; i < _columns;i++)
		    {
		        colour = (_myMap.find(line.substr(ind, _charsPerPixel)))->second;

				rgbColor = colorConverter(hexToInt(colour));
				std::string stringy =  "\033[48;2;";
				stringy.append(std::to_string(rgbColor.r)).append(";").append(std::to_string(rgbColor.g)).append(";").append(std::to_string(rgbColor.b)).append("m").append(" ");
				std::cout << stringy;
				if (i == _columns - 1)
					std::cout << RESET_LINE;
		        ind += _charsPerPixel;
			}
		}
	}
}

// static int	get_colour(struct RGB colour)
// {
// 	int	trgb;

// 	trgb = colour.r << 16 | colour.g << 8 | colour.b;
// 	return (trgb);
// }

 struct RGB colorConverter(int hexValue)
{
  struct RGB rgbColor;

  rgbColor.r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
//   std::cout << RED << "RED: " << rgbColor.r << RESET_LINE;
  rgbColor.g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
//   std::cout << GREEN << "GREEN: " << rgbColor.g << RESET_LINE;
  rgbColor.b = ((hexValue) & 0xFF);        // Extract the BB byte
//   std::cout << BLUE << "BLUE: " << rgbColor.b << RESET_LINE;

  return rgbColor; 
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