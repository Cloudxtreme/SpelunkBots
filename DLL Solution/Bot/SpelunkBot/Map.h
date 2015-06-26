#include "Helper.h"
#include "Cell.h"
#include <vector>

extern double map[X_NODES][Y_NODES];
extern boolean exitFound;

void updateMap();
void printMap();
void findTarget();
void move();

std::vector<Cell> getNeighbors(Cell);

// uses StarSearch algorithm to get the best path from "start" to "goal"
Cell StarSearchExplorer(Cell, Cell);

int getDistance(Cell a, Cell b);
int findBestOption(std::vector<Cell> options, Cell goal);