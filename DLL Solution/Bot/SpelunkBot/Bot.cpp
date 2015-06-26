// SpelunkBot.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Bot.h"
#include "Helper.h"
#include "Map.h"
#include "Movement.h"

int counter = 0;


double MyBot()
{
	// movement: single click turns
	// pixels moved: 0 0 2 3 3 ... 3 3 | 2 1 1 1 1 0 0
	printf("%3.0f (%f)\n", _playerPositionX, _playerPositionXNode);
	switch (counter){
		case 0:
			moveRight();
			break;
		case 1:
			moveRight();
			break;
		case 2:
			moveRight();
			break;
		case 3:
			moveRight();
			break;
		case 4:
			moveNot();
			break;
		case 5:
			moveRight();
			break;
		case 6:
			moveRight();
			break;
		case 7:
			moveRight();
			break;
		case 8:
			moveRight();
			break;
		case 9:
			moveNot();
			break;
		case 10:
			moveNot();
			break;
		case 11:
			moveNot();
			break;
		case 12:
			moveNot();
			break;
		case 13:
			//jump();
			moveRight();
			break;
		case 14:
			moveRight();
			break;
		case 15:
			moveRight();
			break;
		case 16:
			//jump();
			moveNot();
			break;
		case 17:
			moveNot();
			break;
		case 18:
			moveNot();
			break;
		default:
			break;
	}
	
	counter++;

	/*updateMap();
	printMap();
	findTarget();
	move();
	*/

	/*if (exitFound){
		printf("finding exit\n");
		if (_playerPositionXNode < (GetNextPathXPos(_playerPositionXNode, _playerPositionYNode, NODE_COORDS)))
		{
			_goRight = true;
			_goLeft = false;
		}
		else
		{
			_goLeft = true;
			_goRight = false;
		}
	}
	else{
		printf("exploring\n");
		for (int y = 0; y < Y_NODES; y++)
		{
			if (map[0][y] == spEmptyNode){
				_goLeft = true;
				break;
			}
		}
		if (!_goLeft){
			_goRight = true;
		}
	}*/

	
	
	return 0;
}

#pragma region Setup

 double _pathCount;
 double _tempID;
 double _waitTimer;
 double _targetX;
 double _targetY;
 double _playerPositionX;
 double _playerPositionY;
 double _playerPositionXNode;
 double _playerPositionYNode;
 bool _hasGoal;
 bool _spIsInAir;
 bool _spIsJetpacking;
 bool _itemGoal;
 bool _fogGoal;
 bool _endGoal;
 bool _headingRight;
 bool _headingLeft;
 bool _goRight;
 bool _goLeft;
 bool _jump;
 bool _attack;

 bool _duck;
 bool _lookup;
 bool _payp;
 bool _sprint;

 HMODULE spelunkbots_hModule = LoadLibrary(TEXT("spelunkbots.dll"));

 UpdatePlayerVariablesPROC UpdatePlayerVariables = (UpdatePlayerVariablesPROC)GetProcAddress(spelunkbots_hModule, "UpdatePlayerVariables");
 DisplayPlayerVariablesPROC DisplayPlayerVariables = (DisplayPlayerVariablesPROC)GetProcAddress(spelunkbots_hModule, "DisplayMessages");
 SetScreenXYWHPROC SetScreenXYWH = (SetScreenXYWHPROC)GetProcAddress(spelunkbots_hModule, "SetScreenXYWH");
 SetCoolGlassesPROC SetCoolGlasses = (SetCoolGlassesPROC)GetProcAddress(spelunkbots_hModule, "SetCoolGlasses");
 SetUdjatEyePROC SetUdjatEye = (SetUdjatEyePROC)GetProcAddress(spelunkbots_hModule, "SetUdjatEye");
 ResetFogForNewLevelPROC ResetFogForNewLevel = (ResetFogForNewLevelPROC)GetProcAddress(spelunkbots_hModule, "ResetFogForNewLevel");
 TerrainWasDestroyedPROC TerrainWasDestroyed = (TerrainWasDestroyedPROC)GetProcAddress(spelunkbots_hModule, "TerrainWasDestroyed");
 SpiderWebCreatedPROC SpiderWebCreated = (SpiderWebCreatedPROC)GetProcAddress(spelunkbots_hModule, "SpiderWebCreated");
 SpiderWebWasRemovedPROC SpiderWebWasRemoved = (SpiderWebWasRemovedPROC)GetProcAddress(spelunkbots_hModule, "SpiderWebWasRemoved");
 DestroyFogPROC DestroyFog = (DestroyFogPROC)GetProcAddress(spelunkbots_hModule, "DestroyFog");
 TerrainIsLadderPROC TerrainIsLadder = (TerrainIsLadderPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsLadder");
 TerrainIsGoalPROC TerrainIsGoal = (TerrainIsGoalPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsGoal");
 TerrainIsStartPROC TerrainIsStart = (TerrainIsStartPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsStart");
 TerrainIsAltarPROC TerrainIsAltar = (TerrainIsAltarPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsAltar");
 TerrainIsArrowTrapRightPROC TerrainIsArrowTrapRight = (TerrainIsArrowTrapRightPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsArrowTrapRight");
 TerrainIsArrowTrapLeftPROC TerrainIsArrowTrapLeft = (TerrainIsArrowTrapLeftPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsArrowTrapLeft");
 TerrainIsShopKeeperAreaPROC TerrainIsShopKeeperArea = (TerrainIsShopKeeperAreaPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsShopKeeperArea");
 TerrainIsIcePROC TerrainIsIce = (TerrainIsIcePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsIce");
 TerrainIsSpikePROC TerrainIsSpike = (TerrainIsSpikePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsSpike");
 TerrainIsSpearTrapPROC TerrainIsSpearTrap = (TerrainIsSpearTrapPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsSpearTrap");
 TerrainIsSwimWaterPROC TerrainIsSwimWater = (TerrainIsSwimWaterPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsSwimWater");
 TerrainIsLavaPROC TerrainIsLava = (TerrainIsLavaPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsLava");
 TerrainIsGameEntrancePROC TerrainIsGameEntrance = (TerrainIsGameEntrancePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsGameEntrance");
 TerrainIsTreePROC TerrainIsTree = (TerrainIsTreePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsTree");
 TerrainIsTreeBranchLeafPROC TerrainIsTreeBranchLeaf = (TerrainIsTreeBranchLeafPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsTreeBranchLeaf");
 TerrainIsEmptyPROC TerrainIsEmpty = (TerrainIsEmptyPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsEmpty");
 GetLiquidValuePROC GetLiquidValue = (GetLiquidValuePROC)GetProcAddress(spelunkbots_hModule, "GetLiquidValue");
 SpringPadAtPositionPROC SpringPadAtPosition = (SpringPadAtPositionPROC)GetProcAddress(spelunkbots_hModule, "SpringPadAtPosition");
 FillShopkeeperAreaPROC FillShopkeeperArea = (FillShopkeeperAreaPROC)GetProcAddress(spelunkbots_hModule, "FillShopkeeperArea");
 SetMapCoordPROC SetMapCoord = (SetMapCoordPROC)GetProcAddress(spelunkbots_hModule, "SetMapCoord");
 ClearFogFromSquarePROC ClearFogFromSquare = (ClearFogFromSquarePROC)GetProcAddress(spelunkbots_hModule, "ClearFogFromSquare");
 GetNodeStatePROC GetNodeState = (GetNodeStatePROC)GetProcAddress(spelunkbots_hModule, "GetNodeState");
 GetFogStatePROC GetFogState = (GetFogStatePROC)GetProcAddress(spelunkbots_hModule, "GetFogState");
 IsClearPathToExitPROC IsClearPathToExit = (IsClearPathToExitPROC)GetProcAddress(spelunkbots_hModule, "IsClearPathToExit");
 ClearDynamicObjectsPROC ClearDynamicObjects = (ClearDynamicObjectsPROC)GetProcAddress(spelunkbots_hModule, "ClearDynamicObjects");
 NodeContainsPushBlockPROC NodeContainsPushBlock = (NodeContainsPushBlockPROC)GetProcAddress(spelunkbots_hModule, "NodeContainsPushBlock");
 GetNodeContainsPushBlockPROC GetNodeContainsPushBlock = (GetNodeContainsPushBlockPROC)GetProcAddress(spelunkbots_hModule, "GetNodeContainsPushBlock");
 NodeContainsBatPROC NodeContainsBat = (NodeContainsBatPROC)GetProcAddress(spelunkbots_hModule, "NodeContainsBat");
 GetNodeContainsBatPROC GetNodeContainsBat = (GetNodeContainsBatPROC)GetProcAddress(spelunkbots_hModule, "GetNodeContainsBat");
 ResetCollectablesPROC ResetCollectables = (ResetCollectablesPROC)GetProcAddress(spelunkbots_hModule, "ResetCollectables");
 NodeContainsCollectablePROC NodeContainsCollectable = (NodeContainsCollectablePROC)GetProcAddress(spelunkbots_hModule, "NodeContainsCollectable");
 UpdateCollectableAtNodePROC UpdateCollectableAtNode = (UpdateCollectableAtNodePROC)GetProcAddress(spelunkbots_hModule, "UpdateCollectableAtNode");
 RemoveCollectableWithIDPROC RemoveCollectableWithID = (RemoveCollectableWithIDPROC)GetProcAddress(spelunkbots_hModule, "RemoveCollectableWithID");
 NumberOfCollectableTypeInNodePROC NumberOfCollectableTypeInNode = (NumberOfCollectableTypeInNodePROC)GetProcAddress(spelunkbots_hModule, "NumberOfCollectableTypeInNode");
 ResetEnemiesPROC ResetEnemies = (ResetEnemiesPROC)GetProcAddress(spelunkbots_hModule, "SetScResetEnemiesreenXYWH");
 NodeContainsEnemyPROC NodeContainsEnemy = (NodeContainsEnemyPROC)GetProcAddress(spelunkbots_hModule, "NodeContainsEnemy");
 UpdateEnemyAtNodePROC UpdateEnemyAtNode = (UpdateEnemyAtNodePROC)GetProcAddress(spelunkbots_hModule, "UpdateEnemyAtNode");
 RemoveEnemyWithIDPROC RemoveEnemyWithID = (RemoveEnemyWithIDPROC)GetProcAddress(spelunkbots_hModule, "RemoveEnemyWithID");
 NumberOfWebsInNodePROC NumberOfWebsInNode = (NumberOfWebsInNodePROC)GetProcAddress(spelunkbots_hModule, "NumberOfWebsInNode");
 NumberOfEnemyTypeInNodePROC NumberOfEnemyTypeInNode = (NumberOfEnemyTypeInNodePROC)GetProcAddress(spelunkbots_hModule, "NumberOfEnemyTypeInNode");
 GetIDOfEnemyInNodePROC GetIDOfEnemyInNode = (GetIDOfEnemyInNodePROC)GetProcAddress(spelunkbots_hModule, "GetIDOfEnemyInNode");
 GetIDOfCollectableInNodePROC GetIDOfCollectableInNode = (GetIDOfCollectableInNodePROC)GetProcAddress(spelunkbots_hModule, "GetIDOfCollectableInNode");
 SaveDynamicObjectFilesDebugPROC SaveDynamicObjectFilesDebug = (SaveDynamicObjectFilesDebugPROC)GetProcAddress(spelunkbots_hModule, "SaveDynamicObjectFilesDebug");
 SaveSpiderwebsToFilePROC SaveSpiderwebsToFile = (SaveSpiderwebsToFilePROC)GetProcAddress(spelunkbots_hModule, "SaveSpiderwebsToFile");
 SaveLevelLayoutToFilePROC SaveLevelLayoutToFile = (SaveLevelLayoutToFilePROC)GetProcAddress(spelunkbots_hModule, "SetScrSaveLevelLayoutToFileeenXYWH");
 CalculatePathFromXYtoXYPROC CalculatePathFromXYtoXY = (CalculatePathFromXYtoXYPROC)GetProcAddress(spelunkbots_hModule, "CalculatePathFromXYtoXY");
 GetNextPathXPosPROC GetNextPathXPos = (GetNextPathXPosPROC)GetProcAddress(spelunkbots_hModule, "GetNextPathXPos");
 GetNextPathYPosPROC GetNextPathYPos = (GetNextPathYPosPROC)GetProcAddress(spelunkbots_hModule, "GetNextPathYPos");
 IsEnemyInNodePROC IsEnemyInNode = (IsEnemyInNodePROC)GetProcAddress(spelunkbots_hModule, "IsEnemyInNode");
 IsCollectableInNodePROC IsCollectableInNode = (IsCollectableInNodePROC)GetProcAddress(spelunkbots_hModule, "IsCollectableInNode");
 IsNodePassablePROC IsNodePassable = (IsNodePassablePROC)GetProcAddress(spelunkbots_hModule, "IsNodePassable");

SPELUNKBOT_API double Initialise(void)
{
	_targetX = 0;
	_targetY = 0;
	_pathCount = 0;
	_tempID = 0;
	_waitTimer = 0;
	_playerPositionX = 0;
	_playerPositionY = 0;
	_playerPositionXNode = 0;
	_playerPositionYNode = 0;
	_hasGoal = false;
	_spIsInAir = false;
	_spIsJetpacking = false;
	_itemGoal = false;
	_fogGoal = true;
	_endGoal = false;
	_headingRight = false;
	_headingLeft = false;
	_goRight = false;
	_goLeft = false;
	_jump = false;
	_attack = false;
	_duck = false;
	_lookup = false;
	_sprint = false;
	_payp = false;

	for (int y = 0; y < Y_NODES; y++)
	{
		for (int x = 0; x < X_NODES; x++)
		{
			map[X_NODES][Y_NODES] = -1.0;
		}
	}

	return 1;
}

#pragma endregion

#pragma region Bot Logic

SPELUNKBOT_API double Update(double botSelector, double botXPos, double botYPos)
{
	// Sample bot
	ResetBotVariables();

	// Store bot positions
	_playerPositionX = botXPos * PIXELS_IN_NODES;
	_playerPositionY = botYPos * PIXELS_IN_NODES;
	_playerPositionXNode = botXPos;
	_playerPositionYNode = botYPos;

	// Add additional bots here
	if (botSelector == 1)
	{
		return BasicBotExampleOne();
	} 
	else if (botSelector == 2){
		return MyBot();
	}
	else
	{
		return 0;
	}
}

double BasicBotExampleOne(void)
{

	if (!_hasGoal)
	{
		// If no goal, search for the exit
		for (int y = 0; y < Y_NODES; y++)
		{
			for (int x = 0; x < X_NODES; x++)
			{
				if (GetNodeState(x, y, NODE_COORDS) == spExit)
				{
					_hasGoal = true;
					_itemGoal = true;
					_targetX = x * PIXELS_IN_NODES;
					_targetY = y * PIXELS_IN_NODES;
					CalculatePathFromXYtoXY(_playerPositionX, _playerPositionY, _targetX, _targetY, PIXEL_COORDS);
					std::cout << "FOUND EXIT" << std::endl;
					return 0;
				}
			}
		}
	}
	else
	{
		// If goal, move towards it
		if (_playerPositionXNode < (GetNextPathXPos(_playerPositionXNode, _playerPositionYNode, NODE_COORDS)))
		{
			_goRight = true;
		}
		else
		{
			_goLeft = true;
		}
	}

	return 1;
}

// Reset variables as required each frame
void ResetBotVariables(void)
{
	_headingRight = false;
	_headingLeft = false;
	_goRight = false;
	_goLeft = false;
	_jump = false;
	_attack = false;

	_duck = false;
	_lookup = false;
	_sprint = false;
	_payp = false;
}

#pragma endregion

#pragma region Get functions for GM

double ConvertBoolToDouble(bool valToConvert)
{
	if (valToConvert)
	{
		return 1;
	}
	return 0;
}
char* ConvertBoolToChar(bool valToConvert)
{
	if (valToConvert)
	{
		return "1";
	}
	return "0";
}
SPELUNKBOT_API double GetHasGoal(void)
{
	return ConvertBoolToDouble(_hasGoal);
}
SPELUNKBOT_API double GetIsInAir(void)
{
	return ConvertBoolToDouble(_spIsInAir);
}
SPELUNKBOT_API double GetIsJetpacking(void)
{
	return ConvertBoolToDouble(_spIsJetpacking);
}
SPELUNKBOT_API double GetItemGoal(void)
{
	return ConvertBoolToDouble(_itemGoal);
}
SPELUNKBOT_API double GetPathCount(void)
{
	return _pathCount;
}
SPELUNKBOT_API double GetTempID(void)
{
	return _tempID;
}
SPELUNKBOT_API double GetFogGoal(void)
{
	return ConvertBoolToDouble(_fogGoal);
}
SPELUNKBOT_API double GetEndGoal(void)
{
	return ConvertBoolToDouble(_endGoal);
}
SPELUNKBOT_API double GetWaitTimer(void)
{
	return _waitTimer;
}
SPELUNKBOT_API double GetHeadingRight(void)
{
	return ConvertBoolToDouble(_headingRight);
}
SPELUNKBOT_API double GetHeadingLeft(void)
{
	return ConvertBoolToDouble(_headingLeft);
}
SPELUNKBOT_API double GetGoRight(void)
{
	return ConvertBoolToDouble(_goRight);
}
SPELUNKBOT_API double GetGoLeft(void)
{
	return ConvertBoolToDouble(_goLeft);
}
SPELUNKBOT_API double GetJump(void)
{
	return ConvertBoolToDouble(_jump);
}
SPELUNKBOT_API double GetTargetX(void)
{
	return _targetX;
}
SPELUNKBOT_API double GetTargetY(void)
{
	return _targetY;
}
SPELUNKBOT_API double GetAttack(void)
{
	return ConvertBoolToDouble(_attack);
}

SPELUNKBOT_API double GetDuck(void)
{
	return ConvertBoolToDouble(_duck);
}
SPELUNKBOT_API double GetLookUp(void)
{
	return ConvertBoolToDouble(_lookup);
}
SPELUNKBOT_API double GetPayP(void)
{
	return ConvertBoolToDouble(_payp);
}
SPELUNKBOT_API double GetRunning(void)
{
	return ConvertBoolToDouble(_sprint);
}

// to add new functions, edit initializeDLL and UpdateCppBotVariables in GM, and Bot.h and Bot.cpp in VS
#pragma endregion