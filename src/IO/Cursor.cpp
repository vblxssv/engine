#include "Cursor.h"


Cursor::Cursor()
{
	lastx = lasty = 0;
}

double Cursor::get_lastx()
{
	return lastx;
}

double Cursor::get_lasty()
{
	return lasty;
}

std::pair<double, double> Cursor::get_offset(double new_x, double new_y)
{
	if (first_move) {
		first_move = false;
		return { 0.0, 0.0 };
	}
	return { new_x - lastx, new_y - lasty };
}

void Cursor::update(double new_x, double new_y)
{
	lastx = new_x;
	lasty = new_y;
}






