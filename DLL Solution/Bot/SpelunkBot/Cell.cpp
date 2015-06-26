#include "Cell.h"

bool Cell::same(Cell a)
{
	return a.x == x && a.y == y;
}

Cell::Cell(double a, double b){
	x = a;
	y = b;
}

Cell::Cell(){
	x = -1;
	y = -1;
}