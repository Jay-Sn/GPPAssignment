#include "pfantasy.h"

PFantasy::PFantasy() {}

PFantasy::~PFantasy()
{
	releaseAll();			//call onLostDevice() for every graphics item
}

//Initialize the game
void PFantasy::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	return;
}

//Update all game items
void PFantasy::update() {

}

//Artificial Intelligence
void PFantasy::ai() {}

//Handle collisions
void PFantasy::collisions() {}

//Render game items
void PFantasy::render() {
	graphics->spriteBegin();


	graphics->spriteEnd();
}

//The graphics device was lost
//Release all reserved video memory to be resetted
void PFantasy::releaseAll() {

	Game::releaseAll();
	return;
}

//The graphics device has been reset.
//Recreate all reserved video memory to reset graphics device
void PFantasy::resetAll() {

	Game::resetAll();
	return;
}

