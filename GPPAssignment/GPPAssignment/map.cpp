#include "map.h"
#include <iostream>
using namespace std;

Map::Map() {
    
}

Map::~Map()
{
    releaseAll();
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void Map::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
    intializeUI();
    intializeCharacters();

    return;
}

void Map::reset()
{
}

//=============================================================================
// move character
// frameTime is used to regulate the speed of movement
//=============================================================================
void Map::update()
{
    if (input->isKeyDown(CURSOR_DOWN_KEY))  // if move down
    {
        playerChara.setY(playerChara.getY() + 30 * frameTime);
    }
    if (input->isKeyDown(CURSOR_UP_KEY))    // if move up
    {
        playerChara.setY(playerChara.getY() - 30 * frameTime);
    }
    if (input->isKeyDown(CURSOR_RIGHT_KEY)) // if move right
    {
        playerChara.setX(playerChara.getX() + 30 * frameTime);
    }
    if (input->isKeyDown(CURSOR_LEFT_KEY)) // if move left
    {
        playerChara.setX(playerChara.getX() - 30 * frameTime);
    }
    //playerChara.update(frameTime);
}

void Map::ai()
{
}

void Map::collisions()
{
}

//=============================================================================
// render game items
//=============================================================================
void Map::render()
{
    const int BUF_SIZE = 100;
    static char buffer[BUF_SIZE];
    graphics->spriteBegin();
    renderCharacters();
    renderUI();
    graphics->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Map::releaseAll()
{
    mainCharaTexture.onLostDevice();
    // dxMenuText->onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void Map::resetAll()
{
    mainCharaTexture.onResetDevice();
    // dxMenuText->onResetDevice();
    Game::resetAll();
    return;
}

void Map::checkMouse()
{
}

void Map::intializeUI()
{
}

void Map::renderUI()
{
}

void Map::intializeCharacters()
{
    //initialize character textures
    if (!mainCharaTexture.initialize(graphics, PLAYERCHARA_IMAGE))throw(gameErrorNS::FATAL_ERROR, "Error initiating Player Character");
    if (!playerChara.initialize(graphics, 0,0,0,&mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Player Character");
}

void Map::renderCharacters()
{
    playerChara.draw(TRANSCOLOR);
}
