#ifndef Cell_HEADER
#define Cell_HEADER

class Cell {
public:
	double x, y;

	Cell(double, double);
	Cell();
	bool same(Cell);
};

#endif