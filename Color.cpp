#include "Color.h"

const Color black = { 15, 0, 20, 100 };
const Color white = { 235, 235, 235, 255 };
const Color green = { 34, 217, 51, 255 };
const Color red = { 232, 18, 18, 255 };
const Color orange = { 255, 165, 0, 255 };
const Color yellow = { 237, 234, 4, 255 };
const Color pink = { 234, 26, 120, 255 };
const Color cyan = { 21, 204, 209, 255 };
const Color blue = { 0, 0, 255, 255 };
const Color darkBlue = { 34, 34, 73, 240 };
const Color grey = { 190, 190, 190, 100 };

std::vector<Color>GetCellColors()
{
	return { black, green, red, orange, yellow, pink, cyan, blue };
}