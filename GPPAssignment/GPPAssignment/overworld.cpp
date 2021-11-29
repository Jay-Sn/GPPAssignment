#include "overworld.h"
#include <iostream>
using namespace std;

Overworld::Overworld(SceneManager* manager) {
    dxManager = manager;
}

Overworld::~Overworld()
{
    releaseAll();
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void Overworld::initialize()
{
    intializeCharacters();

    return;
}

void Overworld::reset()
{
}

//=============================================================================
// move character
// frameTime is used to regulate the speed of movement
//=============================================================================
void Overworld::update(float frameTime)
{
    if (dxManager->getInput()->isKeyDown(CURSOR_DOWN_KEY))  // if move down
    {
        playerChara.setY(playerChara.getY() + 30 * frameTime);
    }
    if (dxManager->getInput()->isKeyDown(CURSOR_UP_KEY))    // if move up
    {
        playerChara.setY(playerChara.getY() - 30 * frameTime);
    }
    if (dxManager->getInput()->isKeyDown(CURSOR_RIGHT_KEY)) // if move right
    {
        playerChara.setX(playerChara.getX() + 30 * frameTime);
    }
    if (dxManager->getInput()->isKeyDown(CURSOR_LEFT_KEY)) // if move left
    {
        playerChara.setX(playerChara.getX() - 30 * frameTime);
    }
    //playerChara.update(frameTime);
}

void Overworld::ai()
{
}

void Overworld::collisions()
{
}

//=============================================================================
// render game items
//=============================================================================
void Overworld::render()
{
    const int BUF_SIZE = 100;
    static char buffer[BUF_SIZE];
    dxManager->getGraphics()->spriteBegin();
    renderCharacters();
    dxManager->getGraphics()->spriteEnd();
}

//=============================================================================
// The dxManager->getGraphics() device was lost.
// Release all reserved video memory so dxManager->getGraphics() device may be reset.
//=============================================================================
void Overworld::releaseAll()
{
    mainCharaTexture.onLostDevice();
    // dxMenuText->onLostDevice();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void Overworld::resetAll()
{
    mainCharaTexture.onResetDevice();
    // dxMenuText->onResetDevice();
    return;
}

//void Overworld::checkMouse()
//{
//}
//
//void Overworld::intializeUI()
//{
//}
//
//void Overworld::renderUI()
//{
//}

void Overworld::intializeCharacters()
{
    //initialize character textures
    if (!mainCharaTexture.initialize(dxManager->getGraphics(), PLAYERCHARA_IMAGE))throw(gameErrorNS::FATAL_ERROR, "Error initiating Player Character");
    if (!playerChara.initialize(dxManager->getGraphics(), 0,0,0,&mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Player Character");
}

void Overworld::renderCharacters()
{
    playerChara.draw(TRANSCOLOR);
}
