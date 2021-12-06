#include "startingMenu.h"
#include <iostream>

StartingMenu::StartingMenu(SceneManager* manager)
{
    dxManager = manager;
    dxMenuText = new TextDX();     // DirectX fonts
    menuList.push_back({ "Start", 60, 100 });
    menuList.push_back({ "Option", 60, 130 });
    menuList.push_back({ "Quit", 60, 160 });
}

StartingMenu::~StartingMenu()
{
    releaseAll();
    SAFE_DELETE(dxMenuText);
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void StartingMenu::initialize()
{
    if (!mainCharaTexture.initialize(dxManager->getGraphics(), Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
    if (!cursor.initialize(dxManager->getGraphics(), 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

    cursor.setX(menuList.at(menuIndex).x - 20);
    cursor.setY(menuList.at(menuIndex).y);
    cursor.setScale(0.5, 0.5);
    dxManager->getGraphics()->setBackColor(graphicsNS::WHITE);

    // initialize DirectX fonts
    // 15 pixel high Arial
    if (dxMenuText->initialize(dxManager->getGraphics(), 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
    if (dxFont.initialize(dxManager->getGraphics(), gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));



    reset();            // reset all game variables
    return;
}


//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void StartingMenu::reset()
{
    return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void StartingMenu::update(float frameTime)
{
    if (dxManager->getInput()->wasKeyPressed(VK_RETURN)) 
    {
        if (cursor.getY() == 100) {
            dxManager->switchScene("Overworld");
        }
        else if (cursor.getY() == 130) {
            dxManager->switchScene("Battle");
        }
        else if (cursor.getY() == 160) {
             PostQuitMessage(0);
        }
    }
    if (dxManager->getInput()->wasKeyPressed(CURSOR_DOWN_KEY) && cursor.getY() != 160)               // if move up
    {
        cursor.setY(cursor.getY() +  30);
    }
    if (dxManager->getInput()->wasKeyPressed(CURSOR_UP_KEY) && cursor.getY() != 100)               // if move up
    {
        cursor.setY(cursor.getY() -  30);
    }
    if (dxManager->getInput()->wasKeyPressed(VK_ESCAPE)) {
        dxManager->switchScene("PauseMenu");
    }
    cursor.update(frameTime);
}

void StartingMenu::ai()
{
}

void StartingMenu::collisions()
{
}

//=============================================================================
// render game items
//=============================================================================
void StartingMenu::render()
{
    dxManager->getGraphics()->spriteBegin();
    cursor.draw(TRANSCOLOR);
    dxMenuText->setFontColor(graphicsNS::BLACK);
    for(auto option: menuList) {
        dxMenuText->print(option.option, option.x, option.y);
    }
    dxFont.setFontColor(gameNS::FONT_COLOR);
    dxManager->getGraphics()->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void StartingMenu::releaseAll()
{
    mainCharaTexture.onLostDevice();
    dxMenuText->onLostDevice();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void StartingMenu::resetAll()
{
    mainCharaTexture.onResetDevice();
    dxMenuText->onResetDevice();
    return;
}