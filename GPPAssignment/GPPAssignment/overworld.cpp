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
    //Initialize the world map
    initializeWorld();

    //initialize the Characters
    initializeCharacters();

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
    //Checking for controls
    controls(frameTime);
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
    dxManager->getGraphics()->spriteBegin();

    //Draw the world map
    worldMap.draw(TRANSCOLOR);

    //Draw Main Character
    playerChara.draw();

    //renderCharacters();
    dxManager->getGraphics()->spriteEnd();
}

//=============================================================================
// The dxManager->getGraphics() device was lost.
// Release all reserved video memory so dxManager->getGraphics() device may be reset.
//=============================================================================
void Overworld::releaseAll()
{
    worldMapTexture.onLostDevice();
    mainCharaTexture.onLostDevice();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void Overworld::resetAll()
{
    worldMapTexture.onResetDevice();
    mainCharaTexture.onResetDevice();
    return;
}

//Initialize the world and set default position
void Overworld::initializeWorld()
{
    //initializing World map Texture
    if (!worldMapTexture.initialize(dxManager->getGraphics(), OVERWORLD_IMAGE))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize World Map initialize"));

    //initializing World Map
    if (!worldMap.initialize(dxManager->getGraphics(), 0, 0, 0, &worldMapTexture))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize World Map"));

    //Scaling Up world
    worldMap.setScale(3, 3);

    //Setting Default Position of the world
    worldMap.setX(-worldMap.getWidth() / 2 + GAME_WIDTH / 2);
    worldMap.setY(-worldMap.getHeight() / 2 + GAME_HEIGHT / 2);
}


//Initialize Characters and set MC at Center
void Overworld::initializeCharacters() 
{
    //initializing World map Texture
    if (!mainCharaTexture.initialize(dxManager->getGraphics(), MAINCHARA_IMAGE))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Main Character texture"));

    //initializing World Map
    if (!playerChara.initialize(dxManager, 0, 0, 0, &mainCharaTexture, "Ayame","Hero",100,true))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Main Character"));

    //Setting Scale
    playerChara.setScale(1.5, 1.5);

    //Setting Default Position of the world
    playerChara.setX(GAME_WIDTH / 2 - playerChara.getImagePtr()->getWidth() / 2);
    playerChara.setY(GAME_HEIGHT / 2 - playerChara.getImagePtr()->getHeight() / 2);

    characterList.push_back(playerChara);
}

//Movement Controls
void Overworld::controls(float frameTime) {
    if (dxManager->getInput()->isKeyDown(NAVI_RIGHT_KEY))
    {
        worldMap.setX(worldMap.getX() - MOVEMENTSPEED * frameTime);
    }
    if (dxManager->getInput()->isKeyDown(NAVI_LEFT_KEY))
    {
        worldMap.setX(worldMap.getX() + MOVEMENTSPEED * frameTime);
    }
    if (dxManager->getInput()->isKeyDown(NAVI_DOWN_KEY))
    {
        worldMap.setY(worldMap.getY() - MOVEMENTSPEED * frameTime);
    }
    if (dxManager->getInput()->isKeyDown(NAVI_UP_KEY))
    {
        worldMap.setY(worldMap.getY() + MOVEMENTSPEED * frameTime);
    }
}