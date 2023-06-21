#ifndef ASCIIART_HPP
	#define ASCIIART_HPP
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>

typedef struct RGB 
{
    int r;
    int g;
    int b;
} RGB;

class AsciiConverter
{
	private:
		std::string 						_name;
		std::string							_values;
		size_t								_columns;
		size_t								_rows;
		size_t								_colourCount;
		size_t								_charsPerPixel;
		std::map<std::string, std::string>	_myMap;

	public:
		AsciiConverter(std::string stringy);
		AsciiConverter(const AsciiConverter	 &copy);
		AsciiConverter	&operator=(const AsciiConverter &copy);
		~AsciiConverter();
		/* member finctions */

	private:
		AsciiConverter();
		int		setValues();
		int 	hexToInt(const std::string& hex);
		void	convert(std::ifstream &inputFile);
		void	fillTheMap(std::ifstream &inputFile);
};
struct RGB	colorConverter(int hexValue);

#endif