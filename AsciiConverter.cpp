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
	std::ofstream outfile("ascii.sh");
	std::string line;
  	struct RGB rgbColor;

	if (inputFile.is_open()) 
	{
		while (std::getline(inputFile, line) && line.compare("};")) 
		{
			size_t  ind = 1;
		    std::string colour;
			if (outfile.is_open())
			{
				outfile << "echo -e \"";
			    for (size_t i = 0; i < _columns;i++)
			    {
			        colour = (_myMap.find(line.substr(ind, _charsPerPixel)))->second;

					rgbColor = colorConverter(hexToInt(colour));
					std::string stringy =  "\033[48;2;";
					stringy.append(std::to_string(rgbColor.r)).append(";");
					stringy.append(std::to_string(rgbColor.g)).append(";");
					stringy.append(std::to_string(rgbColor.b)).append("m").append("  ");
					// std::cout << stringy;

						outfile << stringy;
						if (i == _columns - 1)
							outfile << "\033[0m\"\n";
			        ind += _charsPerPixel;
				}
			}
		}
			outfile.close();
	}
}

 struct RGB colorConverter(int hexValue)
{
	struct RGB rgbColor;

	rgbColor.r = ((hexValue >> 16) & 0xFF);  // Extract the RR byte
	rgbColor.g = ((hexValue >> 8) & 0xFF);   // Extract the GG byte
	rgbColor.b = ((hexValue) & 0xFF);        // Extract the BB byte

	return rgbColor; 
}
