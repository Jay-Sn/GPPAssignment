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

	if (!mainCharaTexture.initialize(graphics, MAINCHARA_IMAGE))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
	if (!mainChara.initialize(graphics,0,0,0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
	
	mainChara.setY(GAME_HEIGHT / 2 - mainChara.getHeight());
	mainChara.setX(GAME_WIDTH * 0.75f - mainChara.getWidth() / 2);

	mainChara.setScale(2);

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

	mainChara.draw(TRANSCOLOR);

	graphics->spriteEnd();
}

//The graphics device was lost
//Release all reserved video memory to be resetted
void PFantasy::releaseAll() {
	mainCharaTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//The graphics device has been reset.
//Recreate all reserved video memory to reset graphics device
void PFantasy::resetAll() {
	mainCharaTexture.onResetDevice();
	Game::resetAll();
	return;
}

