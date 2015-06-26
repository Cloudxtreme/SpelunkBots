// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SPELUNKBOT_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SPELUNKBOT_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SPELUNKBOT_EXPORTS
#define SPELUNKBOT_API extern "C" __declspec(dllexport)
#else
#define SPELUNKBOT_API extern "C" __declspec(dllimport)
#endif

#pragma region Function Declarations

/*
	All DLL functions to be called from Game Maker need to return a string or a double.

	Use these functions to convert values are required.
*/
double ConvertBoolToDouble(bool valToConvert);
char* ConvertBoolToChar(bool valToConvert);

/*
	ResetBotVariables is used to reset any bot variables e.g. _goLeft or _goRight
*/
void ResetBotVariables(void);

/*
	Initialise is used to setup any variables when a bot enters a room.

	Add any additional variable initialisation here.
*/
SPELUNKBOT_API double Initialise(void);
/*
	Update is used to update the bot position and chose which bot function to use.
*/
SPELUNKBOT_API double Update(double botSelector, double botXPos, double botYPos);
/*
	Getter functions for variables.

	Add additional functions as required.
*/
SPELUNKBOT_API double GetHasGoal(void);
SPELUNKBOT_API double GetIsInAir(void);
SPELUNKBOT_API double GetIsJetpacking(void);
SPELUNKBOT_API double GetItemGoal(void);
SPELUNKBOT_API double GetPathCount(void);
SPELUNKBOT_API double GetTempID(void);
SPELUNKBOT_API double GetFogGoal(void);
SPELUNKBOT_API double GetEndGoal(void);
SPELUNKBOT_API double GetWaitTimer(void);
SPELUNKBOT_API double GetHeadingRight(void);
SPELUNKBOT_API double GetHeadingLeft(void);
SPELUNKBOT_API double GetGoRight(void);
SPELUNKBOT_API double GetGoLeft(void);
SPELUNKBOT_API double GetJump(void);
SPELUNKBOT_API double GetTargetX(void);
SPELUNKBOT_API double GetTargetY(void);
SPELUNKBOT_API double GetAttack(void);

SPELUNKBOT_API double GetDuck(void);
SPELUNKBOT_API double GetLookUp(void);
SPELUNKBOT_API double GetPayP(void);
SPELUNKBOT_API double GetRunning(void);

// Functions that perform different bot behaviours should be placed here
double BasicBotExampleOne(void);
double MyBot(void);

#pragma endregion

#pragma region Variables

extern double _pathCount;
extern double _tempID;
extern double _waitTimer;
extern double _targetX;
extern double _targetY;
extern double _playerPositionX;
extern double _playerPositionY;
extern double _playerPositionXNode;
extern double _playerPositionYNode;
extern bool _hasGoal;
extern bool _spIsInAir;
extern bool _spIsJetpacking;
extern bool _itemGoal;
extern bool _fogGoal;
extern bool _endGoal;
extern bool _headingRight;
extern bool _headingLeft;
extern bool _goRight;
extern bool _goLeft;
extern bool _jump;
extern bool _attack;

extern bool _duck;
extern bool _lookup;
extern bool _payp;
extern bool _sprint;

#pragma endregion

#pragma region API Imports

extern HMODULE spelunkbots_hModule;// = LoadLibrary(TEXT("spelunkbots.dll"));

typedef double(__cdecl *UpdatePlayerVariablesPROC)(char *name, char *value, double type);
typedef double(__cdecl * DisplayPlayerVariablesPROC)();
typedef double(__cdecl *SetScreenXYWHPROC)(double x, double y, double w, double h);
typedef double(__cdecl *SetCoolGlassesPROC)(double d);
typedef double(__cdecl *SetUdjatEyePROC)(double d);
typedef double(__cdecl *ResetFogForNewLevelPROC)();
typedef double(__cdecl *TerrainWasDestroyedPROC)(double x, double y);
typedef double(__cdecl *SpiderWebCreatedPROC)(double x, double y);
typedef double(__cdecl *IsCollectableInNodePROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *IsNodePassablePROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *IsEnemyInNodePROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *GetNextPathYPosPROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *GetNextPathXPosPROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *CalculatePathFromXYtoXYPROC)(double x1, double y1, double x2, double y2, double usingPixelCoords);
typedef double(__cdecl *SaveLevelLayoutToFilePROC)();
typedef double(__cdecl *SaveSpiderwebsToFilePROC)();
typedef double(__cdecl *SaveDynamicObjectFilesDebugPROC)();
typedef double(__cdecl *GetIDOfCollectableInNodePROC)(double type, double x, double y, double usingPixelCoords);
typedef double(__cdecl *GetIDOfEnemyInNodePROC)(double type, double x, double y, double usingPixelCoords);
typedef double(__cdecl *NumberOfEnemyTypeInNodePROC)(double type, double x, double y, double usingPixelCoords);
typedef double(__cdecl *NumberOfWebsInNodePROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *RemoveEnemyWithIDPROC)(double id);
typedef double(__cdecl *UpdateEnemyAtNodePROC)(double x, double y, double id);
typedef double(__cdecl *NodeContainsEnemyPROC)(double x, double y, double type, double id);
typedef double(__cdecl *ResetEnemiesPROC)();
typedef double(__cdecl *NumberOfCollectableTypeInNodePROC)(double type, double x, double y, double usingPixelCoords);
typedef double(__cdecl *RemoveCollectableWithIDPROC)(double id);
typedef double(__cdecl *UpdateCollectableAtNodePROC)(double x, double y, double id);
typedef double(__cdecl *NodeContainsCollectablePROC)(double x, double y, double type, double id);
typedef double(__cdecl *ResetCollectablesPROC)();
typedef double(__cdecl *GetNodeContainsBatPROC)(double x, double y, double usingPixelCOords);
typedef double(__cdecl *NodeContainsBatPROC)(double x, double y);
typedef double(__cdecl *GetNodeContainsPushBlockPROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *NodeContainsPushBlockPROC)(double x, double y);
typedef double(__cdecl *ClearDynamicObjectsPROC)();
typedef bool(__cdecl *IsClearPathToExitPROC)();
typedef double(__cdecl *GetFogStatePROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *GetNodeStatePROC)(double x, double y, double usingPixelCoords);
typedef double(__cdecl *ClearFogFromSquarePROC)(double x, double y);
typedef double(__cdecl *SetMapCoordPROC)(double x, double y, double state);
typedef double(__cdecl *FillShopkeeperAreaPROC)(double x, double y);
typedef double(__cdecl *SpringPadAtPositionPROC)(double x, double y);
typedef double(__cdecl *GetLiquidValuePROC)(double x, double y);
typedef double(__cdecl *TerrainIsEmptyPROC)(double x, double y);
typedef double(__cdecl *TerrainIsTreeBranchLeafPROC)(double x, double y);
typedef double(__cdecl *TerrainIsTreePROC)(double x, double y);
typedef double(__cdecl *TerrainIsGameEntrancePROC)(double x, double y);
typedef double(__cdecl *TerrainIsLavaPROC)(double x, double y);
typedef double(__cdecl *TerrainIsSwimWaterPROC)(double x, double y);
typedef double(__cdecl *TerrainIsSpearTrapPROC)(double x, double y);
typedef double(__cdecl *TerrainIsSpikePROC)(double x, double y);
typedef double(__cdecl *TerrainIsIcePROC)(double x, double y);
typedef double(__cdecl *TerrainIsShopKeeperAreaPROC)(double x, double y);
typedef double(__cdecl *TerrainIsArrowTrapLeftPROC)(double x, double y);
typedef double(__cdecl *TerrainIsArrowTrapRightPROC)(double x, double y);
typedef double(__cdecl *TerrainIsAltarPROC)(double x, double y);
typedef double(__cdecl *TerrainIsStartPROC)(double x, double y);
typedef double(__cdecl *TerrainIsGoalPROC)(double x, double y);
typedef double(__cdecl *TerrainIsLadderPROC)(double x, double y);
typedef double(__cdecl *DestroyFogPROC)(double x, double y);
typedef double(__cdecl *SpiderWebWasRemovedPROC)(double x, double y);

extern UpdatePlayerVariablesPROC UpdatePlayerVariables;
extern DisplayPlayerVariablesPROC DisplayPlayerVariables;
extern SetScreenXYWHPROC SetScreenXYWH;
extern SetCoolGlassesPROC SetCoolGlasses;// = (SetCoolGlassesPROC)GetProcAddress(spelunkbots_hModule, "SetCoolGlasses");
extern SetUdjatEyePROC SetUdjatEye;// = (SetUdjatEyePROC)GetProcAddress(spelunkbots_hModule, "SetUdjatEye");
extern ResetFogForNewLevelPROC ResetFogForNewLevel;// = (ResetFogForNewLevelPROC)GetProcAddress(spelunkbots_hModule, "ResetFogForNewLevel");
extern TerrainWasDestroyedPROC TerrainWasDestroyed;// = (TerrainWasDestroyedPROC)GetProcAddress(spelunkbots_hModule, "TerrainWasDestroyed");
extern SpiderWebCreatedPROC SpiderWebCreated;// = (SpiderWebCreatedPROC)GetProcAddress(spelunkbots_hModule, "SpiderWebCreated");
extern SpiderWebWasRemovedPROC SpiderWebWasRemoved;// = (SpiderWebWasRemovedPROC)GetProcAddress(spelunkbots_hModule, "SpiderWebWasRemoved");
extern DestroyFogPROC DestroyFog;// = (DestroyFogPROC)GetProcAddress(spelunkbots_hModule, "DestroyFog");
extern TerrainIsLadderPROC TerrainIsLadder;// = (TerrainIsLadderPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsLadder");
extern TerrainIsGoalPROC TerrainIsGoal;// = (TerrainIsGoalPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsGoal");
extern TerrainIsStartPROC TerrainIsStart;// = (TerrainIsStartPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsStart");
extern TerrainIsAltarPROC TerrainIsAltar;// = (TerrainIsAltarPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsAltar");
extern TerrainIsArrowTrapRightPROC TerrainIsArrowTrapRight;// = (TerrainIsArrowTrapRightPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsArrowTrapRight");
extern TerrainIsArrowTrapLeftPROC TerrainIsArrowTrapLeft;// = (TerrainIsArrowTrapLeftPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsArrowTrapLeft");
extern TerrainIsShopKeeperAreaPROC TerrainIsShopKeeperArea;// = (TerrainIsShopKeeperAreaPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsShopKeeperArea");
extern TerrainIsIcePROC TerrainIsIce;// = (TerrainIsIcePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsIce");
extern TerrainIsSpikePROC TerrainIsSpike;// = (TerrainIsSpikePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsSpike");
extern TerrainIsSpearTrapPROC TerrainIsSpearTrap;// = (TerrainIsSpearTrapPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsSpearTrap");
extern TerrainIsSwimWaterPROC TerrainIsSwimWater;// = (TerrainIsSwimWaterPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsSwimWater");
extern TerrainIsLavaPROC TerrainIsLava;// = (TerrainIsLavaPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsLava");
extern TerrainIsGameEntrancePROC TerrainIsGameEntrance;// = (TerrainIsGameEntrancePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsGameEntrance");
extern TerrainIsTreePROC TerrainIsTree;// = (TerrainIsTreePROC)GetProcAddress(spelunkbots_hModule, "TerrainIsTree");
extern TerrainIsTreeBranchLeafPROC TerrainIsTreeBranchLeaf;// = (TerrainIsTreeBranchLeafPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsTreeBranchLeaf");
extern TerrainIsEmptyPROC TerrainIsEmpty;// = (TerrainIsEmptyPROC)GetProcAddress(spelunkbots_hModule, "TerrainIsEmpty");
extern GetLiquidValuePROC GetLiquidValue;// = (GetLiquidValuePROC)GetProcAddress(spelunkbots_hModule, "GetLiquidValue");
extern SpringPadAtPositionPROC SpringPadAtPosition;// = (SpringPadAtPositionPROC)GetProcAddress(spelunkbots_hModule, "SpringPadAtPosition");
extern FillShopkeeperAreaPROC FillShopkeeperArea;// = (FillShopkeeperAreaPROC)GetProcAddress(spelunkbots_hModule, "FillShopkeeperArea");
extern SetMapCoordPROC SetMapCoord;// = (SetMapCoordPROC)GetProcAddress(spelunkbots_hModule, "SetMapCoord");
extern ClearFogFromSquarePROC ClearFogFromSquare;// = (ClearFogFromSquarePROC)GetProcAddress(spelunkbots_hModule, "ClearFogFromSquare");
extern GetNodeStatePROC GetNodeState;// = (GetNodeStatePROC)GetProcAddress(spelunkbots_hModule, "GetNodeState");
extern GetFogStatePROC GetFogState;// = (GetFogStatePROC)GetProcAddress(spelunkbots_hModule, "GetFogState");
extern IsClearPathToExitPROC IsClearPathToExit;// = (IsClearPathToExitPROC)GetProcAddress(spelunkbots_hModule, "IsClearPathToExit");
extern ClearDynamicObjectsPROC ClearDynamicObjects;// = (ClearDynamicObjectsPROC)GetProcAddress(spelunkbots_hModule, "ClearDynamicObjects");
extern NodeContainsPushBlockPROC NodeContainsPushBlock;// = (NodeContainsPushBlockPROC)GetProcAddress(spelunkbots_hModule, "NodeContainsPushBlock");
extern GetNodeContainsPushBlockPROC GetNodeContainsPushBlock;// = (GetNodeContainsPushBlockPROC)GetProcAddress(spelunkbots_hModule, "GetNodeContainsPushBlock");
extern NodeContainsBatPROC NodeContainsBat;// = (NodeContainsBatPROC)GetProcAddress(spelunkbots_hModule, "NodeContainsBat");
extern GetNodeContainsBatPROC GetNodeContainsBat;// = (GetNodeContainsBatPROC)GetProcAddress(spelunkbots_hModule, "GetNodeContainsBat");
extern ResetCollectablesPROC ResetCollectables;// = (ResetCollectablesPROC)GetProcAddress(spelunkbots_hModule, "ResetCollectables");
extern NodeContainsCollectablePROC NodeContainsCollectable;// = (NodeContainsCollectablePROC)GetProcAddress(spelunkbots_hModule, "NodeContainsCollectable");
extern UpdateCollectableAtNodePROC UpdateCollectableAtNode;// = (UpdateCollectableAtNodePROC)GetProcAddress(spelunkbots_hModule, "UpdateCollectableAtNode");
extern RemoveCollectableWithIDPROC RemoveCollectableWithID;// = (RemoveCollectableWithIDPROC)GetProcAddress(spelunkbots_hModule, "RemoveCollectableWithID");
extern NumberOfCollectableTypeInNodePROC NumberOfCollectableTypeInNode;// = (NumberOfCollectableTypeInNodePROC)GetProcAddress(spelunkbots_hModule, "NumberOfCollectableTypeInNode");
extern ResetEnemiesPROC ResetEnemies;// = (ResetEnemiesPROC)GetProcAddress(spelunkbots_hModule, "SetScResetEnemiesreenXYWH");
extern NodeContainsEnemyPROC NodeContainsEnemy;// = (NodeContainsEnemyPROC)GetProcAddress(spelunkbots_hModule, "NodeContainsEnemy");
extern UpdateEnemyAtNodePROC UpdateEnemyAtNode;// = (UpdateEnemyAtNodePROC)GetProcAddress(spelunkbots_hModule, "UpdateEnemyAtNode");
extern RemoveEnemyWithIDPROC RemoveEnemyWithID;// = (RemoveEnemyWithIDPROC)GetProcAddress(spelunkbots_hModule, "RemoveEnemyWithID");
extern NumberOfWebsInNodePROC NumberOfWebsInNode;// = (NumberOfWebsInNodePROC)GetProcAddress(spelunkbots_hModule, "NumberOfWebsInNode");
extern NumberOfEnemyTypeInNodePROC NumberOfEnemyTypeInNode;// = (NumberOfEnemyTypeInNodePROC)GetProcAddress(spelunkbots_hModule, "NumberOfEnemyTypeInNode");
extern GetIDOfEnemyInNodePROC GetIDOfEnemyInNode;// = (GetIDOfEnemyInNodePROC)GetProcAddress(spelunkbots_hModule, "GetIDOfEnemyInNode");
extern GetIDOfCollectableInNodePROC GetIDOfCollectableInNode;// = (GetIDOfCollectableInNodePROC)GetProcAddress(spelunkbots_hModule, "GetIDOfCollectableInNode");
extern SaveDynamicObjectFilesDebugPROC SaveDynamicObjectFilesDebug;// = (SaveDynamicObjectFilesDebugPROC)GetProcAddress(spelunkbots_hModule, "SaveDynamicObjectFilesDebug");
extern SaveSpiderwebsToFilePROC SaveSpiderwebsToFile;// = (SaveSpiderwebsToFilePROC)GetProcAddress(spelunkbots_hModule, "SaveSpiderwebsToFile");
extern SaveLevelLayoutToFilePROC SaveLevelLayoutToFile;// = (SaveLevelLayoutToFilePROC)GetProcAddress(spelunkbots_hModule, "SetScrSaveLevelLayoutToFileeenXYWH");
extern CalculatePathFromXYtoXYPROC CalculatePathFromXYtoXY;// = (CalculatePathFromXYtoXYPROC)GetProcAddress(spelunkbots_hModule, "CalculatePathFromXYtoXY");
extern GetNextPathXPosPROC GetNextPathXPos;// = (GetNextPathXPosPROC)GetProcAddress(spelunkbots_hModule, "GetNextPathXPos");
extern GetNextPathYPosPROC GetNextPathYPos;// = (GetNextPathYPosPROC)GetProcAddress(spelunkbots_hModule, "GetNextPathYPos");
extern IsEnemyInNodePROC IsEnemyInNode;// = (IsEnemyInNodePROC)GetProcAddress(spelunkbots_hModule, "IsEnemyInNode");
extern IsCollectableInNodePROC IsCollectableInNode;// = (IsCollectableInNodePROC)GetProcAddress(spelunkbots_hModule, "IsCollectableInNode");
extern IsNodePassablePROC IsNodePassable;// = (IsNodePassablePROC)GetProcAddress(spelunkbots_hModule, "IsNodePassable");

#pragma endregion