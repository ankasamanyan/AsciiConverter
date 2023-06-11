#ifndef ASCIIART_HPP
	#define ASCIIART_HPP
#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class AsciiConverter
{
	private:
		std::string _values;
		size_t		_columns;
		size_t		_rows;
		size_t		_colourCount;
		size_t		_charsPerPixel;
	public:
		AsciiConverter();
		AsciiConverter(std::string stringy);
		AsciiConverter(const AsciiConverter	 &copy);
		AsciiConverter	&operator<<(const AsciiConverter &copy);
		~AsciiConverter();
	/* member finctions */

	private:
		void	set_values(int line);

};

#endif