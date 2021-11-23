#include "startingMenu.h"
#include <iostream>

StartingMenu::StartingMenu()
{
    dxMenuText = new TextDX();     // DirectX fonts
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
void StartingMenu::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
    if (!mainCharaTexture.initialize(graphics, Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
    if (!mainChara.initialize(graphics, 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

    mainChara.setY(100);
    mainChara.setX(40);
    mainChara.setScale(0.5, 0.5);
    graphics->setBackColor(graphicsNS::WHITE);

    // initialize DirectX fonts
    // 15 pixel high Arial
    if (dxMenuText->initialize(graphics, 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));
    if (dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
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
void StartingMenu::update()
{
    if (input->wasKeyPressed(VK_RETURN)) 
    {
        if (mainChara.getY() == 100) {
            y = 100;
        }
        else if (mainChara.getY() == 130) {
            y = 130;
        }
        else if (mainChara.getY() == 160) {
            y = 160;
        }
    }
    if (input->wasKeyPressed(CURSOR_DOWN_KEY) && mainChara.getY() != 160)               // if move up
    {
        mainChara.setY(mainChara.getY() +  30);
        graphics->spriteBegin();
        dxMenuText->setFontColor(graphicsNS::BLACK);
        dxMenuText->print("Start", 600, 600);
        graphics->spriteEnd();
    }
    if (input->wasKeyPressed(CURSOR_UP_KEY) && mainChara.getY() != 100)               // if move up
    {
        mainChara.setY(mainChara.getY() -  30);
    }
    if (input->wasKeyPressed(VK_LEFT)) {

    }
    mainChara.update(frameTime);
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
    const int BUF_SIZE = 100;
    static char buffer[BUF_SIZE];
    graphics->spriteBegin();
    mainChara.draw(TRANSCOLOR);
    dxMenuText->setFontColor(graphicsNS::BLACK);
    dxMenuText->print("Start", 60, yValues[0]);
    dxMenuText->print("Options", 60, yValues[1]);
    dxMenuText->print("Quit", 60, yValues[2]);
    dxFont.setFontColor(gameNS::FONT_COLOR);
    sprintf_s(buffer, "You have selected: %d", (int)y);
    dxFont.print(buffer, 200, 200);
    graphics->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void StartingMenu::releaseAll()
{
    mainCharaTexture.onLostDevice();
    dxMenuText->onLostDevice();
    Game::releaseAll();
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
    Game::resetAll();
    return;
}