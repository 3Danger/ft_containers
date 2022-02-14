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
	struct foreground
	{
		const char *black = "30";
		const char *red = "31";
		const char *green = "32";
		const char *yellow = "33";
		const char *blue = "34";
		const char *magenta = "35";
		const char *cyan = "36";
		const char *white = "37";
		const char *reset = "0";
	};
	struct background
	{
		const char *black = "40";
		const char *red = "41";
		const char *green = "42";
		const char *yellow = "43";
		const char *blue = "44";
		const char *magenta = "45";
		const char *cyan = "46";
		const char *white = "47";
		const char *reset = "0";
	};
	template <typename T>
	static std::string findCol(T && t, eColor col)
	{
		switch (col)
		{
			case BLACK: return t.black;
			case RED: return t.red;
			case GREEN: return t.green;
			case YELLOW: return t.yellow;
			case BLUE: return t.blue;
			case MAGENTA: return t.magenta;
			case CYAN: return t.cyan;
			case WHITE:	return t.white;
			case RESET:	return t.reset;
		}
	}
	std::string static getColor(eColor fg = RESET, eColor bg = RESET)
	{
		if (bg == RESET)
			return std::string("\033[") + \
			findCol(CC::foreground(), fg) + "m";
		return std::string("\033[") + \
		findCol(CC::foreground(), fg) + ";" + \
		findCol(CC::background(), bg) + "m";
	}
};

using CC::getColor;
using CC::eColor;

