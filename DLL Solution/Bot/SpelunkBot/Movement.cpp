#include "stdafx.h"
#include "Bot.h"

#define STANDING = 10
#define RUNNING = 11
#define DUCKING = 12
#define LOOKING_UP = 13
#define CLIMBING = 14
#define JUMPING = 15
#define FALLING = 16
#define DYING = 17
#define LEFT = 18
#define RIGHT = 19
#define ON_GROUND = 20
#define IN_AIR = 21
#define ON_LADDER = 22
#define HANGING = 23
#define DUCKTOHANG = 24

int maxVal(int a, int b){
	if (a > b)
		return a;
	return b;
}

bool turnedLeft=true;
int turnCounter=0, slowCounter=5;
int speedingUp[] = { 0, 0, 2, 3 };
int slowingDown[] = { 2, 1, 1, 1, 1, 0 };
int jumpSpeed = 3;
int lastAction = 0;
//0 0 2 3 3 ... 3 3 | 2 1 1 1 1 0 0
// state = FALLING ;          // the character state, must be one of the following: STANDING, RUNNING, DUCKING, LOOKING_UP, CLIMBING, JUMPING, or FALLING
// characterCreateEvent - sets states and variables for player
// oKeyConfig > Draw - writes shit on screen
// gameStepEvent -> moves objects in the scene
/*
if (state == HANGING)
{
	global.isPlayerHanging = true;
}
*/

//colisions: collision_rectangle(x-8, y-8, x+8, y+8, oRock, 0, 0)
void moveLeft(){
	_goLeft = true;
	if (!turnedLeft){
		turnedLeft = true;
		turnCounter = 0;
		printf("Expected to move %d\n", -maxVal(speedingUp[turnCounter], slowingDown[slowCounter]));
		slowCounter = 5;
	}
	else{
		if (_jump){
			printf("Expected to move 3\n");
		}
		else{
			if (slowCounter != 0){
				printf("Expected to move %d\n", -maxVal(speedingUp[turnCounter], slowingDown[slowCounter]));
			}
			else{
				printf("Expected to move %d\n", -speedingUp[turnCounter]);
			}
		}
		
		slowCounter = 0;
	}
	turnCounter = turnCounter < sizeof(speedingUp) ? turnCounter + 1 : turnCounter;
}

void moveRight(){
	_goRight = true;
	if (turnedLeft){
		turnedLeft = false;
		turnCounter = 0;
		printf("Expected to move %d\n", maxVal(speedingUp[turnCounter], slowingDown[slowCounter]));
		slowCounter = 5;
	}
	else{
		if (_jump){
			printf("Expected to move 3\n");
		}
		else{
			if (slowCounter != 0){
				printf("Expected to move %d\n", maxVal(speedingUp[turnCounter], slowingDown[slowCounter]));
			}
			else{
				printf("Expected to move %d\n", speedingUp[turnCounter]);
			}
		}
		slowCounter = 0;
	}
	turnCounter = turnCounter < sizeof(speedingUp) ? turnCounter + 1 : turnCounter;
}

void moveNot(){
	turnCounter = 0;
	printf("Expected to move %d\n", slowingDown[slowCounter]);
	slowCounter = slowCounter < sizeof(slowingDown) ? slowCounter + 1 : slowCounter;
}

void jump(){
	_jump = true;
}

static double hangCountMax, kLeftPushedSteps, kRightPushedSteps, cantJump;
static boolean kLeft, kLeftPressed, kLeftReleased;
static boolean kRight, kRightPressed, kRightReleased;
static boolean kUp, kDown;
static boolean kJump, kJumpPressed, kJumpReleased, kJumped, jumpButtonReleased;
static boolean kAttack, kAttackPressed, kAttackReleased;
static boolean kItemPressed, stunned, dead, whipping, swimming, holdItem;
static double x, y, xPrev, yPrev, state, runHeld, xVel, xAcc, yVel, yAcc, climbAcc, upYPrev,
departLadderXVel, departLadderYVel, yAccLimit, looking, xAccLimit, statePrevPrev, statePrev;
static double facing, pushTimer, runAcc, ladderTimer;
static double CLIMBING, HANGING, DUCKING, ON_GROUND, LEFT, RIGHT, FALLING, STANDING, JUMPING,
IN_AIR, RUNNING, UP, DOWN, LOOKING_UP, LOOKING_DOWN, DUCKTOHANG;
static boolean colSolidLeft, colSolidRight, colLeft, colRight, colTop, colBot,
colLadder, colPlatBot, colPlat, colWaterTop, colIceBot, runKey, ladder, colPointLadder;
static double jumpTime, gravityIntensity, jumps, grav, hangCount, initialJumpAcc,
gravNorm, jetpackFuel, fallTimer, jumpTimeTotal;
static double xFric, yFric, frictionClimbingX, frictionClimbingY, xVelLimit, yVelLimit,
frictionRunningFastX, frictionRunningFastY, image_speed, frictionRunningX, frictionRunningY;
static double slopeChangeInY, slopeYPrev, slopeChangeInX, slopeXPrev, maxSlope, yPrevHigh, maxDownSlope;
static int xVelInteger, yVelInteger;
static double runAnimSpeed, climbAnimSpeed, image_index;

void processMovement(){
	checkKeys();
}

void checkKeys() {
	/*
	This script should be placed in the step event f|| the platform character.
	It updates the keys used by the character, moves all of the solids, moves the
	character, sets the sprite index, && sets the animation speed f|| the sprite.
	*/
	hangCountMax = 3;

	//////////////////////////////////////
	// KEYS
	//////////////////////////////////////

	if (kLeft) {
		kLeftPushedSteps += 1;
	}
	else {
		kLeftPushedSteps = 0;
	}

	if (kRight) {
		kRightPushedSteps += 1;
	}
	else {
		kRightPushedSteps = 0;
	}

	//left right up down jump attack item

	if (cantJump > 0 ) { // || (global.isTunnelMan && sprite_index == sTunnelAttackL && !holdItem)
		kJump = 0;
		kJumpPressed = 0;
		kJumpReleased = 0;
		cantJump -= 1;
	}

	xPrev = x;
	yPrev = y;

	if (stunned || dead) {
		kLeft = false;
		kLeftPressed = false;
		kLeftReleased = false;
		kRight = false;
		kRightPressed = false;
		kRightReleased = false;
		kUp = false;
		kDown = false;
		kJump = false;
		kJumpPressed = false;
		kJumpReleased = false;
		kAttack = false;
		kAttackPressed = false;
		kAttackReleased = false;
		kItemPressed = false;
	}
}

void collisions() {
	//////////////////////////////////////////
	// Collisions
	//////////////////////////////////////////
	colSolidLeft = false;
	colSolidRight = false;
	colLeft = false;
	colRight = false;
	colTop = false;
	colBot = false;
	colLadder = false;
	colPlatBot = false;
	colPlat = false;
	colWaterTop = false;
	colIceBot = false;
	runKey = false;

	if (isCollisionMoveableSolidLeft(1)) {
		colSolidLeft = true;
	}
	if (isCollisionMoveableSolidRight(1)) {
		colSolidRight = true;
	}
	if (isCollisionLeft(1)) {
		colLeft = true;
	}
	if (isCollisionRight(1)) {
		colRight = true;
	}
	if (isCollisionTop(1)) {
		colTop = true;
	}
	if (isCollisionBottom(1)) {
		colBot = true;
	}
	if (isCollisionLadder()) {
		colLadder = true;
	}
	if (isCollisionPlatformBottom(1)) {
		colPlatBot = true;
	}
	if (isCollisionPlatform()) {
		colPlat = true;
	}
	if (isCollisionWaterTop(1)) {
		colWaterTop = true;
	}
	if (collision_point(x, y + 8, oIce, 0, 0)) {
		colIceBot = true;
	}
}

public static void leftAndRight() {
	if (checkRun()) {
		runHeld = 100;
		runKey = true;
	}

	if (checkAttack() && !whipping) {
		runHeld += 1;
		runKey = true;
	}

	if (!runKey || (!kLeft && !kRight)) {
		runHeld = 0;
	}

	// allows the character to run left && right
	// if state!=DUCKING && state!=LOOKING_UP && state!=CLIMBING
	if (state != CLIMBING && state != HANGING) {
		if (kLeftReleased && approximatelyZero(xVel)) {
			xAcc -= 0.5;
		}
		if (kRightReleased && approximatelyZero(xVel)) {
			xAcc += 0.5;
		}
		if (kLeft && !kRight) {
			if (colSolidLeft) {
				// xVel = 3;
				if (platformCharacterIs(ON_GROUND) && state != DUCKING) {
					xAcc -= 1;
					pushTimer += 10;

				}
			}
			else if (kLeftPushedSteps > 2 && (facing == LEFT || approximatelyZero(xVel))) {
				xAcc -= runAcc;
			}
			facing = LEFT;
		}

		if (kRight && !kLeft) {
			if (colSolidRight) {
				// xVel = 3;
				if (platformCharacterIs(ON_GROUND) && state != DUCKING) {
					xAcc += 1;
					pushTimer += 10;
					//if (! SS_IsSoundPlaying(global.sndPush)) playSound(global.sndPush);
				}
			}
			else if ((kRightPushedSteps > 2 || colSolidLeft) && (facing == RIGHT || approximatelyZero(xVel))) {
				xAcc += runAcc;
			}
			facing = RIGHT;
			//if (platformCharacterIs(ON_GROUND) && abs(xVel) > 0 && alarm[3] < 1) alarm[3] = floor(16/xVel);
		}
	}
}

public static void ladders() {
	/**
	* ****************************************
	*
	* LADDERS
	*
	******************************************
	*/
	if (state == CLIMBING) {
		if (instance_exists(oCape)) {
			oCape.open = false;
		}
		kJumped = false;
		ladderTimer = 10;
		ladder = collision_point(x, y, oLadder, 0, 0);
		if (ladder) {
			x = ladder.x + 8;
		}

		if (kLeft) {
			facing = LEFT;
		}
		else if (kRight) {
			facing = RIGHT;
		}
		if (kUp) {
			if (collision_point(x, y - 8, oLadder, 0, 0) || collision_point(x, y - 8, oLadderTop, 0, 0)) {
				yAcc -= climbAcc;
				if (alarm[2] < 1) {
					alarm[2] = 8;
				}
			}
		}
		else if (kDown) {
			if (collision_point(x, y + 8, oLadder, 0, 0) || collision_point(x, y + 8, oLadderTop, 0, 0)) {
				yAcc += climbAcc;
				if (alarm[2] < 1) {
					alarm[2] = 8;
				}
			}
			else {
				state = FALLING;
			}
			if (colBot) {
				state = STANDING;
			}
		}

		if (kJumpPressed && !whipping) {
			if (kLeft) {
				xVel = -departLadderXVel;
			}
			else if (kRight) {
				xVel = departLadderXVel;
			}
			else {
				xVel = 0;
			}
			yAcc += departLadderYVel;
			state = JUMPING;
			jumpButtonReleased = false;
			jumpTime = 0;
			ladderTimer = 5;
		}
	}
	else {
		if (ladderTimer > 0) {
			ladderTimer -= 1;
		}
	}

	if (platformCharacterIs(IN_AIR) && state != HANGING) {
		yAcc += gravityIntensity;
	}

	// Player has l&& ed
	if ((colBot || colPlatBot) && platformCharacterIs(IN_AIR) && yVel >= 0) {
		if (!colPlat || colBot) {
			yVel = 0;
			yAcc = 0;
			state = RUNNING;
			jumps = 0;
		}
		//playSound(global.sndL&& );
	}
	if ((colBot || colPlatBot) && !colPlat) {
		yVel = 0;
	}

	// Player has just walked off of the edge of a solid
	if (!colBot && (!colPlatBot || colPlat) && platformCharacterIs(ON_GROUND)) {
		state = FALLING;
		yAcc += grav;
		kJumped = true;
		if (global.hasGloves) {
			hangCount = 5;
		}
	}

	if (colTop) {
		if (dead || stunned) {
			yVel = -yVel * 0.8;
		}
		else if (state == JUMPING) {
			yVel = abs(yVel * 0.3);
		}
	}

	if ((colLeft && facing == LEFT) || (colRight && facing == RIGHT)) {
		if (dead || stunned) {
			xVel = -xVel * 0.5;
		}
		else {
			xVel = 0;
		}
	}
}

public static void jump() {
	/**
	* ****************************************
	*
	* JUMPING
	*
	******************************************
	*/
	if (kJumpReleased && platformCharacterIs(IN_AIR)) {
		kJumped = true;
	}
	else if (platformCharacterIs(ON_GROUND)) {
		oCape.open = false;
		kJumped = false;
	}

	if (kJumpPressed && collision_point(x, y, oWeb, 0, 0)) {
		obj = instance_place(x, y, oWeb);
		obj.life -= 1;
		yAcc += initialJumpAcc * 2;
		yVel -= 3;
		xAcc += xVel / 2;

		state = JUMPING;
		jumpButtonReleased = false;
		jumpTime = 0;

		grav = gravNorm;
	}
	else if (kJumpPressed && colWaterTop) {
		yAcc += initialJumpAcc * 2;
		yVel -= 3;
		xAcc += xVel / 2;

		state = JUMPING;
		jumpButtonReleased = false;
		jumpTime = 0;

		grav = gravNorm;
	}
	else if (global.hasCape && kJumpPressed && kJumped && platformCharacterIs(IN_AIR)) {
		if (!oCape.open) {
			oCape.open = true;
		}
		else {
			oCape.open = false;
		}
	}
	else if (global.hasJetpack && kJump && kJumped && platformCharacterIs(IN_AIR) && jetpackFuel > 0) {
		yAcc += initialJumpAcc;
		yVel = -1;
		jetpackFuel -= 1;
		if (alarm[10] < 1) {
			alarm[10] = 3;
		}

		state = JUMPING;
		jumpButtonReleased = false;
		jumpTime = 0;

		grav = 0;
	}
	else if (platformCharacterIs(ON_GROUND) && kJumpPressed && fallTimer == 0) {
		if (xVel > 3 || xVel < -3) {
			yAcc += initialJumpAcc * 2;
			xAcc += xVel * 2;
		}
		else {
			yAcc += initialJumpAcc * 2;
			xAcc += xVel / 2;
		}

		if (global.hasJordans) {
			yAcc *= 3;
			yAccLimit = 12;
			grav = 0.5;
		}
		else if (global.hasSpringShoes) {
			yAcc *= 1.5;
		}
		else {
			yAccLimit = 6;
			grav = gravNorm;
		}
		pushTimer = 0;

		// the "state" gets changed to JUMPING later on in the code
		state = FALLING;
		// "variable jumping" states
		jumpButtonReleased = false;
		jumpTime = 0;
	}

	if (jumpTime < jumpTimeTotal) {
		jumpTime += 1;
	}
	//let the character continue to jump
	if (!kJump) {
		jumpButtonReleased = true;
	}
	if (jumpButtonReleased) {
		jumpTime = jumpTimeTotal;
	}

	gravityIntensity = (jumpTime / jumpTimeTotal) * grav;

	if (kUp && platformCharacterIs(ON_GROUND) && !colLadder) {
		looking = UP;
		if (xVel == 0 && xAcc == 0) {
			state = LOOKING_UP;
		}
	}
	else {
		looking = 0;
	}

	if (!kUp && state == LOOKING_UP) {
		state = STANDING;
	}
}

public static void hang(){
	/**
	* ****************************************
	*
	* HANGING
	*
	******************************************
	*/
	if (!colTop) {
		if (global.hasGloves && yVel > 0) {
			if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && kRight && colRight
				&& (collision_point(x + 9, y - 5, oSolid, 0, 0) || collision_point(x + 9, y - 6, oSolid, 0, 0))) {
				state = HANGING;
				move_snap(1, 8);
				yVel = 0;
				yAcc = 0;
				grav = 0;
			}
			else if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && kLeft && colLeft
				&& (collision_point(x - 9, y - 5, oSolid, 0, 0) || collision_point(x - 9, y - 6, oSolid, 0, 0))) {
				state = HANGING;
				move_snap(1, 8);
				yVel = 0;
				yAcc = 0;
				grav = 0;
			}
		}
		else if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && kRight && colRight
			&& (collision_point(x + 9, y - 5, oTree, 0, 0) || collision_point(x + 9, y - 6, oTree, 0, 0))) {
			state = HANGING;
			move_snap(1, 8);
			yVel = 0;
			yAcc = 0;
			grav = 0;
		}
		else if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && kLeft && colLeft
			&& (collision_point(x - 9, y - 5, oTree, 0, 0) || collision_point(x - 9, y - 6, oTree, 0, 0))) {
			state = HANGING;
			move_snap(1, 8);
			yVel = 0;
			yAcc = 0;
			grav = 0;
		}
		else if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && kRight && colRight
			&& (collision_point(x + 9, y - 5, oSolid, 0, 0) || collision_point(x + 9, y - 6, oSolid, 0, 0))
			&& !collision_point(x + 9, y - 9, oSolid, 0, 0) && !collision_point(x, y + 9, oSolid, 0, 0)) {
			state = HANGING;
			move_snap(1, 8);
			yVel = 0;
			yAcc = 0;
			grav = 0;
		}
		else if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && kLeft && colLeft
			&& (collision_point(x - 9, y - 5, oSolid, 0, 0) || collision_point(x - 9, y - 6, oSolid, 0, 0))
			&& !collision_point(x - 9, y - 9, oSolid, 0, 0) && !collision_point(x, y + 9, oSolid, 0, 0)) {
			state = HANGING;
			move_snap(1, 8);
			yVel = 0;
			yAcc = 0;
			grav = 0;
		}

		if (hangCount == 0 && y > 16 && !platformCharacterIs(ON_GROUND) && state == FALLING
			&& (collision_point(x, y - 5, oArrow, 0, 0) || collision_point(x, y - 6, oArrow, 0, 0))
			&& !collision_point(x, y - 9, oArrow, 0, 0) && !collision_point(x, y + 9, oArrow, 0, 0)) {
			obj = instance_nearest(x, y - 5, oArrow);
			if (obj.stuck) {
				state = HANGING;
				// move_snap(1, 8);
				yVel = 0;
				yAcc = 0;
				grav = 0;
			}
		}
	}

	if (hangCount > 0) {
		hangCount -= 1;
	}

	if (state == HANGING) {
		if (instance_exists(oCape)) {
			oCape.open = false;
		}
		kJumped = false;

		if (kDown && kJumpPressed) {
			grav = gravNorm;
			state = FALLING;
			yAcc -= grav;
			hangCount = 5;
			if (global.hasGloves) {
				hangCount = 10;
			}
		}
		else if (kJumpPressed) {
			grav = gravNorm;
			if ((facing == RIGHT && kLeft) || (facing == LEFT && kRight)) {
				state = FALLING;
				yAcc -= grav;
			}
			else {
				state = JUMPING;
				yAcc += initialJumpAcc * 2;
				if (facing == RIGHT) {
					x -= 2;
				}
				else {
					x += 2;
				}
			}
			hangCount = hangCountMax;
		}

		if ((facing == LEFT && !isCollisionLeft(2)) || (facing == RIGHT && !isCollisionRight(2)))
		{
			grav = gravNorm;
			state = FALLING;
			yAcc -= grav;
			hangCount = 4;
		}
	}
	else {
		grav = gravNorm;
	}
}

public static void unknown(){
	// pressing down while standing
	if (kDown && platformCharacterIs(ON_GROUND) && !whipping) {
		if (colBot) {
			state = DUCKING;
		}
		else if (colPlatBot){
			// climb down ladder if possible, else jump down
			fallTimer = 0;
			if (!colBot) {
				ladder = false;
				ladder = instance_place(x, y + 16, oLadder);
				if (instance_exists(ladder)) {
					if (abs(x - (ladder.x + 8)) < 4) {
						x = ladder.x + 8;

						xVel = 0;
						yVel = 0;
						xAcc = 0;
						yAcc = 0;
						state = CLIMBING;
					}
				}
				else {
					y += 1;
					state = FALLING;
					yAcc += grav;
				}
			}
			else {
				//the character can't move down because there is a solid in the way
				state = RUNNING;
			}
		}
	}
	if (!kDown && state == DUCKING) {
		state = STANDING;
		xVel = 0;
		xAcc = 0;
	}
	if (xVel == 0 && xAcc == 0 && state == RUNNING) {
		state = STANDING;
	}
	if (xAcc != 0 && state == STANDING) {
		state = RUNNING;
	}
	if (yVel < 0 && platformCharacterIs(IN_AIR) && state != HANGING) {
		state = JUMPING;
	}
	if (yVel > 0 && platformCharacterIs(IN_AIR) && state != HANGING) {
		state = FALLING;
		setCollisionBounds(-5, -6, 5, 8);
	}
	else {
		setCollisionBounds(-5, -8, 5, 8);
	}
}

public static void ladders2(){
	// CLIMB LADDER
	colPointLadder = collision_point(x, y, oLadder, 0, 0) || collision_point(x, y, oLadderTop, 0, 0);

	if ((kUp && platformCharacterIs(IN_AIR) && collision_point(x, y - 8, oLadder, 0, 0) && ladderTimer == 0)
		|| (kUp && colPointLadder && ladderTimer == 0) ||
		(kDown && colPointLadder && ladderTimer == 0 && platformCharacterIs(ON_GROUND) && collision_point(x, y + 9, oLadderTop, 0, 0) && xVel == 0))
	{
		ladder = false;
		ladder = instance_place(x, y - 8, oLadder);
		if (instance_exists(ladder)) {
			if (abs(x - (ladder.x + 8)) < 4) {
				x = ladder.x + 8;
				if (!collision_point(x, y, oLadder, 0, 0) && !collision_point(x, y, oLadderTop, 0, 0)) {
					y = ladder.y + 14;
				}

				xVel = 0;
				yVel = 0;
				xAcc = 0;
				yAcc = 0;
				state = CLIMBING;
			}
		}
	}
}

public static void friction(){
	// Calculate horizontal/vertical friction
	if (state == CLIMBING) {
		xFric = frictionClimbingX;
		yFric = frictionClimbingY;
	}
	else {
		if (runKey && platformCharacterIs(ON_GROUND) && runHeld >= 10) {
			if (kLeft) // run
			{
				xVel -= 0.1;
				xVelLimit = 6;
				xFric = frictionRunningFastX;
			}
			else if (kRight) {
				xVel += 0.1;
				xVelLimit = 6;
				xFric = frictionRunningFastX;
			}
		}
		else if (state == DUCKING) {
			if (xVel < 2 && xVel > -2) {
				xFric = 0.2;
				xVelLimit = 3;
				image_speed = 0.8;
			}
			else if (kLeft && global.downToRun) // run
			{
				xVel -= 0.1;
				xVelLimit = 6;
				xFric = frictionRunningFastX;
			}
			else if (kRight && global.downToRun) {
				xVel += 0.1;
				xVelLimit = 6;
				xFric = frictionRunningFastX;
			}
			else {
				xVel *= 0.8;
				if (xVel < 0.5) {
					xVel = 0;
				}
				xFric = 0.2;
				xVelLimit = 3;
				image_speed = 0.8;
			}
		}
		else {
			//decrease the friction when the character is "flying"
			if (platformCharacterIs(IN_AIR)) {
				if (dead || stunned) {
					xFric = 1.0;
				}
				else {
					xFric = 0.8;
				}
			}
			else {
				xFric = frictionRunningX;
			}
		}

		// Stuck on web || underwater
		if (collision_point(x, y, oWeb, 0, 0)) {
			xFric = 0.2;
			yFric = 0.2;
			fallTimer = 0;
		}
		else if (collision_point(x, y, oWater, -1, -1)) {
			if (instance_exists(oCape)) {
				oCape.open = false;
			}

			if (state == FALLING && yVel > 0) {
				yFric = 0.5;
			}
			else if (!collision_point(x, y - 9, oWater, -1, -1)) {
				yFric = 1;
			}
			else {
				yFric = 0.9;
			}
		}
		else {
			swimming = false;
			yFric = 1;
		}
	}

	if (colIceBot && state != DUCKING && !global.hasSpikeShoes) {
		xFric = 0.98;
		yFric = 1;
	}
}

public static void running(){
	// RUNNING
	if (platformCharacterIs(ON_GROUND)) {
		if (state == RUNNING && kLeft && colLeft) {
			pushTimer += 1;
		}
		else if (state == RUNNING && kRight && colRight) {
			pushTimer += 1;
		}
		else {
			pushTimer = 0;
		}

		if (platformCharacterIs(ON_GROUND) && !kJump && !kDown && !runKey) {
			xVelLimit = 3;
		}

		// ledge flip
		if (state == DUCKING && abs(xVel) < 3 && facing == LEFT &&
			collision_point(x, y + 9, oSolid, 0, 0) && !collision_point(x - 1, y + 9, oSolid, 0, 0) && kLeft) {
			state = DUCKTOHANG;

			if (holdItem) {
				holdItem.held = false;
				if (holdItem.type == "Gold Idol") {
					holdItem.y -= 8;
				}
				scrDropItem(-1, -4);
			}

			/*with oMonkey
			{
			// knock off monkeys that grabbed you
			if (status == 7) {
			xVel = -1;
			yVel = -4;
			status = 1;
			vineCounter = 20;
			grabCounter = 60;
			}
			}*/
		}
		else if (state == DUCKING && abs(xVel) < 3 && facing == RIGHT && collision_point(x, y + 9, oSolid, 0, 0)
			&& !collision_point(x + 1, y + 9, oSolid, 0, 0) && kRight) {
			state = DUCKTOHANG;

			if (holdItem) {
				// holdItem.held = false;
				if (holdItem.type == "Gold Idol") {
					holdItem.y -= 8;
				}
				scrDropItem(1, -4);
			}

			/*with oMonkey
			{
			// knock off monkeys that grabbed you
			if (status == 7) {
			xVel = 1;
			yVel = -4;
			status = 1;
			vineCounter = 20;
			grabCounter = 60;
			}
			}*/
		}
	}

	if (state == DUCKTOHANG) {
		x = xPrev;
		y = yPrev;
		xVel = 0;
		yVel = 0;
		xAcc = 0;
		yAcc = 0;
		grav = 0;
	}
}

public static void slowFall(){
	// PARACHUTE AND CAPE
	if (instance_exists(oParachute)) {
		yFric = 0.5;
	}
	if (instance_exists(oCape)) {
		if (oCape.open) {
			yFric = 0.5;
		}
	}

	if (pushTimer > 100) {
		pushTimer = 100;
	}
}

public static void velAndAcc(){
	// limits the acceleration if it is too extreme
	if (xAcc > xAccLimit) {
		xAcc = xAccLimit;
	}
	else if (xAcc < -xAccLimit) {
		xAcc = -xAccLimit;
	}
	if (yAcc > yAccLimit) {
		yAcc = yAccLimit;
	}
	else if (yAcc < -yAccLimit) {
		yAcc = -yAccLimit;
	}

	// applies the acceleration
	xVel += xAcc;
	if (dead || stunned) {
		yVel += 0.6;
	}
	else {
		yVel += yAcc;
	}

	// nullifies the acceleration
	xAcc = 0;
	yAcc = 0;

	// applies the friction to the velocity, now that the velocity has been calculated
	xVel *= xFric;
	yVel *= yFric;
}

public static void ballAndChain(){
	// apply ball && chain
	if (instance_exists(oBall)) {
		if (distance_to_object(oBall) >= 24) {
			if (xVel > 0 && oBall.x < x && abs(oBall.x - x) > 24) {
				xVel = 0;
			}
			if (xVel < 0 && oBall.x > x && abs(oBall.x - x) > 24) {
				xVel = 0;
			}
			if (yVel > 0 && oBall.y < y && abs(oBall.y - y) > 24) {
				if (abs(oBall.x - x) < 1) {
					x = oBall.x;
				}
				else if (oBall.x < x && !kRight) {
					if (xVel > 0) {
						xVel *= -0.25;
					}
					else if (xVel == 0) {
						xVel -= 1;
					}
				}
				else if (oBall.x > x && !kLeft) {
					if (xVel < 0) {
						xVel *= -0.25;
					}
					else if (xVel == 0) {
						xVel += 1;
					}
				}
				yVel = 0;
				fallTimer = 0;
			}
			if (yVel < 0 && oBall.y > y && abs(oBall.y - y) > 24) {
				yVel = 0;
			}
		}
	}
}

public static void main(String[] args) {


	// apply the limits since the velocity may be too extreme
	if (!dead && !stunned) {
		if (xVel > xVelLimit) {
			xVel = xVelLimit;
		}
		else if (xVel < -xVelLimit) {
			xVel = -xVelLimit;
		}
	}
	if (yVel > yVelLimit) {
		yVel = yVelLimit;
	}
	else if (yVel < -yVelLimit) {
		yVel = -yVelLimit;
	}

	// approximates the "active" variables
	if (approximatelyZero(xVel))  {
		xVel = 0;

	}
	if (approximatelyZero(yVel))  {
		yVel = 0;

	}
	if (approximatelyZero(xAcc))  {
		xAcc = 0;

	}
	if (approximatelyZero(yAcc))  {
		yAcc = 0;

	}

	// prepares the character to move up a hill
	// we need to use the "slopeYPrev" variable later to know the "true" y previous value
	// keep this condition the same
	if (maxSlope > 0 && platformCharacterIs(ON_GROUND) && xVel != 0)
	{
		slopeYPrev = y;
		for (y = y; y >= slopeYPrev - maxSlope; y--)
			if (colTop)
				break;
		slopeChangeInY = slopeYPrev - y;
	}
	else {
		slopeChangeInY = 0;

	}

	// moves the character, && balances out the effects caused by other processes
	// keep this condition the same
	if (maxSlope * abs(xVel) > 0 && platformCharacterIs(ON_GROUND))
	{
		// we need to check if we should dampen out the speed as the character runs on upward slopes
		xPrev = x;
		yPrev = slopeYPrev; // we don't want to use y, because y is too high
		yPrevHigh = y; // we'll use the higher previous variable later
		moveTo(xVel, yVel + slopeChangeInY);
		double dist = point_distance(xPrev, yPrev, x, y);
		// overall distance that has been traveled
		// we should have only ran at xVel
		if (dist > abs(xVelInteger))
		{
			// show_message(string(dist)+ " "+string(abs(xVelInteger)))
			double excess = dist - abs(xVelInteger);
			if (xVelInteger < 0) {
				excess *= -1; // move back since the character moved too far

			}
			x = xPrev;
			y = yPrevHigh; // we need the character to be high so the character can move down
			// this time we'll move the correct distance, but we need to shorten out the xVel a little
			// these lines can be changed f|| different types of slowing down when running up hills
			double ratio = abs(xVelInteger) / dist * 0.9; //can be changed
			moveTo(round(xVelInteger * ratio), round(yVelInteger * ratio + slopeChangeInY));
		}
	}
	else {
		// we simply move xVel && yVel while in the air || on a ladder
		moveTo(xVel, yVel);
	}

	// move the character downhill if possible
	// we need to multiply maxDownSlope by the absolute value of xVel since the character normally runs at an xVel larger than 1
	if (!colBot && maxDownSlope > 0 && xVelInteger != 0 && platformCharacterIs(ON_GROUND))
	{
		//the character is floating just above the slope, so move the character down
		upYPrev = y;
		for (y = y; y <= upYPrev + maxDownSlope; y += 1) {
			if (colBot) // we hit a solid below
			{
				upYPrev = y; // I know that this doesn't seem to make sense, because of the name of the variable, but it all works out correctly after we break out of this loop
				break;
			}
		}
		y = upYPrev;
	}

	//sets the previous state && the previously previous state
	statePrevPrev = statePrev;
	statePrev = state;

	//calculates the image_speed based on the character's velocity
	if (state == RUNNING || state == DUCKING || state == LOOKING_UP) {
		if (state == RUNNING || state == LOOKING_UP) {
			image_speed = abs(xVel) * runAnimSpeed + 0.1;
		}
	}

	if (state == CLIMBING) {
		image_speed = sqrt(sqr(abs(xVel)) + sqr(abs(yVel))) * climbAnimSpeed;

	}
	if (xVel >= 4 || xVel <= -4) {
		image_speed = 1;
		if (platformCharacterIs(ON_GROUND)) {
			setCollisionBounds(-8, -8, 8, 8);
		}
		else {
			setCollisionBounds(-5, -8, 5, 8);
		}
	}
	else {
		setCollisionBounds(-5, -8, 5, 8);
	}
	if (whipping) {
		image_speed = 1;
	}
	if (state == DUCKTOHANG) {
		image_index = 0;
		image_speed = 0.8;
	}
	//limit the image_speed at 1 so the animation always looks good
	if (image_speed > 1) {
		image_speed = 1;
	}

}

public static boolean platformCharacterIs(double val){
	return false;
}

public static double abs(double a){
	return 0;
}

public static double sqr(double a){
	return 0;
}

public static double sqrt(double a){
	return 0;
}

public static double round(double a){
	return 0;
}

public static void moveTo(double a, double b){

}

public static void move_snap(double a, double b){

}

public static double point_distance(double a, double b, double c, double d){

}

public static void setCollisionBounds(int a, int b, int c, int d){

}

public static boolean approximatelyZero(double a){
	return false;
}