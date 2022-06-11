#pragma once

#include <string>

enum Color
{
	Red,
	Black
};

enum Mode
{
	Rehash,
	Resize
};

enum State
{
	Actual,
	Deleted,
	Empty
};

const int standartSize = 8;
const double resizeValue = 0.75;