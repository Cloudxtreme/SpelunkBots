#include "stdafx.h"
#include "Helper.h"
#include "Bot.h"
#include <vector>
#include "Cell.h"
#include "Map.h"

double map[X_NODES][Y_NODES];
double processedMap[X_NODES][Y_NODES];
boolean exitFound=false, mapChanged=false, unexploredRegion=false;
int tarX, tarY;

void updateMap(){
	//printMap();

	for (int y = 0; y < Y_NODES; y++)
	{
		for (int x = 0; x < X_NODES; x++)
		{
			double nodeFound = GetNodeState(x, y, NODE_COORDS);
			//printf("%2.0f", nodeFound);
			//dont delete known map with unknown info
			//
				map[x][y] = nodeFound;
				if (nodeFound != -1 && nodeFound != map[x][y]){
					mapChanged = true;
				}
			//}
		}
		//printf("\n");
	}


	if (mapChanged){
		//reset processed map
		for (int y = 0; y < Y_NODES; y++)
		{
			for (int x = 0; x < X_NODES; x++)
			{
				if (map[x][y] != spExit && map[x][y] != spEntrance){
					processedMap[x][y] = map[x][y];
				}
				else{
					processedMap[x][y] = spEmptyNode;
				}
				
			}
		}
		
		for (int y = 0; y < Y_NODES; y++)
		{
			for (int x = 0; x < X_NODES; x++)
			{
				switch ((int)processedMap[x][y]){
					case spArrowTrapRight:
						for (int i = x + 1; i < X_NODES && processedMap[i][y] == spEmptyNode; i++)
						{
							processedMap[i][y] = -2;
						}
						break;
					case spArrowTrapLeft:
						for (int i = x - 1; i >= 0 && processedMap[i][y] == spEmptyNode; i--)
						{
							processedMap[i][y] = -3;
						}
						break;
					default:
						break;
				}
			}
		}
	}
}

void printMap(){
	if (mapChanged){
		for (int y = 0; y < Y_NODES; y++)
		{
			for (int x = 0; x < X_NODES; x++)
			{
				printf("%c", getNodeTypeChar(map[x][y]));
			}
			printf("\n");
		}
		printf("\n");

		for (int y = 0; y < Y_NODES; y++)
		{
			for (int x = 0; x < X_NODES; x++)
			{
				printf("%c", getNodeTypeChar(processedMap[x][y]));
			}
			printf("\n");
		}
		printf("\n");
		mapChanged = false;
	}

}

void findTarget(){
	unexploredRegion = false;
	exitFound = false;
	//check for exit
	for (int y = 0; y < Y_NODES; y++)
	{
		for (int x = 0; x < X_NODES; x++)
		{
			if (map[x][y] == spExit){
				exitFound = true;
				unexploredRegion = false;
				tarX = x;
				tarY = y;
			}
		}
	}

	//check if we explored the target
	if (unexploredRegion && map[tarX][tarY]!=-1){
		unexploredRegion = false;
	}

	// get a new target to explore
	bool breakFors = false;
	if (!exitFound && !unexploredRegion){
		printf("ENTREIIIIIII rofl\n");
		unexploredRegion = true;
		for (int y = 0; y < Y_NODES && !breakFors; y++)
		{
			for (int x = 0; x < X_NODES && !breakFors; x++)
			{
				if (map[x][y] == -1){
					printf("ENTREIIIIIII\n");
					tarX = x;
					tarY = y;
					breakFors = true;
				}
			}
		}
	}
	printf("TARGET: (%d,%d) .. %d,%d\n", tarX, tarY, unexploredRegion, exitFound);
	// as a target, we can also choose an enemy to kill or loot or payshop or w/e
	Cell tar = StarSearchExplorer(Cell(_playerPositionXNode, _playerPositionYNode), Cell(tarX, tarY));
	if (tar.x != -1){
		tarX = (int)tar.x;
		tarY = (int)tar.y;
	}
}

void move(){
	
	//basic....
	int mod;
	if (_playerPositionXNode > tarX+0.5){
		_goLeft = true;
		_goRight = false;
		mod = -1;
	}
	else if (_playerPositionXNode < tarX + 0.5){
		_goRight = true;
		_goLeft = false;
		mod = 1;
	}

	if (map[(int)_playerPositionXNode][(int)_playerPositionYNode] == spExit){
		_lookup = true;
		printf("EXIIIIIIT\n");
	}
	else if (map[(int)_playerPositionXNode+mod][(int)_playerPositionYNode] == spStandardTerrain){
		_jump = true;
	}
}

std::vector<Cell> getNeighbors(Cell a){
	std::vector<Cell> neighbors(0);

	// cell to the left
	if ((processedMap[(int)a.x - 1][(int)a.y] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y + 1] == spStandardTerrain)
		|| processedMap[(int)a.x - 1][(int)a.y] == -1){
			neighbors.push_back(Cell(a.x - 1, a.y));
	}

	// cell to the right
	if ((processedMap[(int)a.x + 1][(int)a.y] == spEmptyNode && processedMap[(int)a.x + 1][(int)a.y + 1] == spStandardTerrain)
		|| processedMap[(int)a.x + 1][(int)a.y] == -1){
		neighbors.push_back(Cell(a.x + 1, a.y));
	}

	// cells to the left and above
	if (processedMap[(int)a.x - 1][(int)a.y - 1] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y - 1));
	}
	else if (processedMap[(int)a.x - 1][(int)a.y - 2] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y - 1] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y - 2));
	}

	// cells to the left and below
	if (processedMap[(int)a.x - 1][(int)a.y + 1] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y + 1));
	}
	else if (processedMap[(int)a.x - 1][(int)a.y + 2] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y + 1] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y + 2));
	}
	else if (processedMap[(int)a.x - 1][(int)a.y + 3] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y + 2] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y + 3));
	}

	// cells to the right and above
	if (processedMap[(int)a.x - 1][(int)a.y - 1] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y - 1));
	}
	else if (processedMap[(int)a.x - 1][(int)a.y - 2] == spEmptyNode && processedMap[(int)a.x - 1][(int)a.y - 1] == spStandardTerrain){
		neighbors.push_back(Cell(a.x - 1, a.y - 2));
	}

	// cells to the right and below
	if (processedMap[(int)a.x + 1][(int)a.y + 1] == spEmptyNode && processedMap[(int)a.x + 1][(int)a.y] == spStandardTerrain){
		neighbors.push_back(Cell(a.x + 1, a.y + 1));
	}
	else if (processedMap[(int)a.x + 1][(int)a.y + 2] == spEmptyNode && processedMap[(int)a.x + 1][(int)a.y + 1] == spStandardTerrain){
		neighbors.push_back(Cell(a.x + 1, a.y + 2));
	}
	else if (processedMap[(int)a.x + 1][(int)a.y + 3] == spEmptyNode && processedMap[(int)a.x + 1][(int)a.y + 2] == spStandardTerrain){
		neighbors.push_back(Cell(a.x + 1, a.y + 3));
	}

	// above and below
	if (processedMap[(int)a.x][(int)a.y + 1] == -1){ // or ladder
		neighbors.push_back(Cell(a.x + 1, a.y + 1));
	}
	if (processedMap[(int)a.x][(int)a.y - 1] == -1){ // or ladder
		neighbors.push_back(Cell(a.x + 1, a.y - 1));
	}

	printf("neightbors: %d\n", neighbors.size());
	return neighbors;
}

int getDistance(Cell a, Cell b){
	return (int)(std::abs(a.x - b.x) + std::abs(a.y - b.y));
}

int findBestOption(std::vector<Cell> options, Cell goal){
	int best;
	int bestValue = X_NODES + Y_NODES;

	// iterate through the options
	for (unsigned i = 0; i < options.size(); i++) {
		int tempValue = getDistance(options[i], goal);
		if (tempValue < bestValue){
			best = i;
			bestValue = tempValue;
		}
	}
	return best;
}

Cell StarSearchExplorer(Cell start, Cell goal) {
	// cell matrix to trace a path
	Cell origins[X_NODES][Y_NODES];
	
	// front vector, the one analysed to find the best results
	std::vector<Cell> front(0);

	// add neighbors of starting cell to the front vector
	std::vector<Cell> neighbors = getNeighbors(start);
	for (unsigned i = 0; i < neighbors.size(); i++) {
		//printf("adding (%d,%d) (i=%d)\n", (int)neighbors[i].x, (int)neighbors[i].y, i);
		front.push_back(neighbors[i]);
		origins[(int)neighbors[i].x][(int)neighbors[i].y] = start;
	}

	boolean haventFoundTheEnd = true;

	// while we have options
	while (!front.empty()) {
		// get closest cell to target
		int bestIndex = findBestOption(front, goal);
		Cell best = front[bestIndex];
		//printf("best option is (%d,%d)\n", (int)best.x, (int)best.y);
		front.erase(front.begin() + bestIndex);

		// if the closest cell is our goal, end
		if (goal.x == best.x && goal.y == best.y) {
			haventFoundTheEnd = false;
			break;
		}

		// otherwise, add new neighbors to the front vector
		neighbors = getNeighbors(best);
		for (unsigned i = 0; i < neighbors.size(); i++) {
			//printf("adding (%d,%d)\n", (int)neighbors[i].x, (int)neighbors[i].y);
			// if neighbour hasnt been visited yet, visit it
			if (origins[(int)neighbors[i].x][(int)neighbors[i].y].x == -1) {
				front.push_back(neighbors[i]);
				origins[(int)neighbors[i].x][(int)neighbors[i].y] = best;
			}
		}
	}

	// make sure we actually found the target. might be blocked by something
	if (haventFoundTheEnd) {
		return Cell();
	}

	//printf("reversing path\n");
	std::vector<Cell> bestPath(20);

	//Start at the endpoint.
	Cell currentPosition = goal;                                                    
	bestPath.push_back(goal);

	//Until we're back at the start.
	while (start.x != currentPosition.x || start.y != currentPosition.y) {         
		//printf("next point in path (%d,%d)\n", (int)currentPosition.x, (int)currentPosition.y);
		currentPosition = origins[(int)currentPosition.x][(int)currentPosition.y];
		bestPath.push_back(currentPosition);
	}

	printf("desired point (%d,%d)\n", (int)bestPath[bestPath.size()].x, (int)bestPath[bestPath.size()].y);
	return bestPath[bestPath.size()];
}