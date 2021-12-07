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
    return;
}

//=============================================================================
// Update to check for game logic
// frameTime is used to regulate the speed of movement
//=============================================================================
void Overworld::update(float frameTime)
{
    //Checking for controls
    controls(frameTime);

    // Goes to pause menu
    if (dxManager->getInput()->wasKeyPressed(VK_ESCAPE)) 
    {
        // Store world coordinates into game state
        dxManager->getState()->setValueToState("WorldX", worldX);
        dxManager->getState()->setValueToState("WorldY", worldY);
        dxManager->switchScene("PauseMenu");
    }

    //UpdatePositions
    setWorldPosition();
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

    //Draw enemy Character
    enemyChara.draw(graphicsNS::RED);

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

    //If map stuff doesn't exist, tell it to go to default
    if ((dxManager->getState()->isFloatExist("WorldX") == false) && (dxManager->getState()->isFloatExist("WorldY") == false))
    {
        dxManager->getState()->setValueToState("WorldX", - worldMap.getWidth() / 2 + GAME_WIDTH / 2);
        dxManager->getState()->setValueToState("WorldY", -worldMap.getHeight() / 2 + GAME_HEIGHT / 2);
    }

    //Setting Default Position of the world
    worldMap.setX(dxManager->getState()->getFloatFromState("WorldX"));
    worldMap.setY(dxManager->getState()->getFloatFromState("WorldY"));

    //Setting world parameters
    worldX = worldMap.getX();
    worldY = worldMap.getY();
}


//=====================================================================================
//              Set Main Character to always be center of the screen
//            Rest of the Characters are set base on WorldX and WorldY
// 
//            E.g. test.setX(WorldX + X), X being the world cooridinate
//=====================================================================================
void Overworld::initializeCharacters() 
{
    //initializing Character Texture
    if (!mainCharaTexture.initialize(dxManager->getGraphics(), MAINCHARA_IMAGE))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Main Character texture"));

    //initializing player character
    if (!playerChara.initialize(dxManager, 0, 0, 0, &mainCharaTexture, "Ayame","Hero",100,true))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Main Character"));

    //Setting Scale
    playerChara.setScale(1.5, 1.5);

    //Setting Default Position of the world
    playerChara.setX(GAME_WIDTH / 2 - playerChara.getImagePtr()->getWidth() / 2);
    playerChara.setY(GAME_HEIGHT / 2 - playerChara.getImagePtr()->getHeight() / 2);

    characterList.push_back(playerChara);

    //initializing enemyCharacter
    if (!enemyChara.initialize(dxManager, 0, 0, 0, &mainCharaTexture, "WoD", "Tank", 100))throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize enemyCharacter"));

    //Getting the right orientationa and scale
    enemyChara.setScale(1.5, 1.5);
    enemyChara.getImagePtr()->flipHorizontal(true);

    //Setting Enemy position
    enemyChara.setX(worldX + GAME_WIDTH / 2);
    enemyChara.setY(worldY + 1840);

}

//=====================================================================================
//                                  Movement Controls
//                              Updates WorldX and WorldY
//=====================================================================================
void Overworld::controls(float frameTime) {

    if (dxManager->getInput()->isKeyDown(NAVI_RIGHT_KEY))
    {
        worldX -= MOVEMENTSPEED * frameTime;
    }

    if (dxManager->getInput()->isKeyDown(NAVI_LEFT_KEY))
    {
        worldX += MOVEMENTSPEED * frameTime;
    }

    if (dxManager->getInput()->isKeyDown(NAVI_DOWN_KEY))
    {
        worldY -= MOVEMENTSPEED * frameTime;
    }

    if (dxManager->getInput()->isKeyDown(NAVI_UP_KEY))
    {
        worldY += MOVEMENTSPEED * frameTime;
    }

    
}

//=====================================================================================
//          worldX : x == windowX : (GameWidth/2 - worldWidth/2) + x
//          worldY : y == windowY : (GameHeight/2 - worldHeight/2) + y
//=====================================================================================
void Overworld::setWorldPosition()
{
    //Setting the world map postition
    worldMap.setX(worldX);
    worldMap.setY(worldY);

    enemyChara.setX(worldX + GAME_WIDTH / 2);
    enemyChara.setY(worldY + 1840);
}