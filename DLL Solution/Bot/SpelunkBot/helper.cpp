#include "stdafx.h"

char getNodeTypeChar(double node){
	switch ((int)node){
		case -2:
			return '>';
		case -3:
			return '<';
		case -1:
			return '?';
		case spEmptyNode:
			return ' ';
		case spStandardTerrain:
			return 'X';
		case spLadder:
			return 'H';
		case spEntrance:
			return 'O';
		case spExit:
			return 'Q';
		case spSacAltar:
			return 'N';
		case spArrowTrapRight:
			return 'b';
		case spArrowTrapLeft:
			return 'd'; 
		case spIsInShop: 
			return 'Y'; 
		case spIce: 
			return '_'; 
		case spSpike: 
			return 'W'; 
		case spSpearTrap:
			return 'T';
		default:
			return '+';
	}
}