#pragma once
#include <string>

namespace CC
{
	typedef enum eeColor
	{
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		RESET
	} eColor;

	std::string getColor(eColor fg = RESET, eColor bg = RESET)
	{
		static char buff[9];
		buff[0] = '\033';
		buff[1] = '[';
		if (fg == RESET)
		{
			buff[2] = '0';
			buff[3] = 'm';
			buff[4] = '\0';
			return buff;
		}
		buff[2] = '3';
		buff[3] = '0' + fg;
		buff[4] = ';';
		buff[5] = '4';
		buff[6] = '0' + bg;
		buff[7] = 'm';
		buff[8] = '\0';
		return buff;
	}
};
using CC::getColor;
using CC::eColor;

