#include "pauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(SceneManager* manager)
{
    dxManager = manager;
    dxMenuText = new TextDX();     // DirectX fonts
}

PauseMenu::~PauseMenu()
{
    releaseAll();
    SAFE_DELETE(dxMenuText);
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void PauseMenu::initialize()
{
    if (!mainCharaTexture.initialize(dxManager->getGraphics(), Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
    if (!cursor.initialize(dxManager->getGraphics(), 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

    cursor.setY(100);
    cursor.setX(40);
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
void PauseMenu::reset()
{
    return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void PauseMenu::update(float frameTime)
{
    if (dxManager->getInput()->wasKeyPressed(VK_RETURN))
    {
        if (cursor.getY() == 100) {
            dxManager->switchScene("Overworld");
        }
        else if (cursor.getY() == 130) {
            dxManager->switchScene("Battle");
        }
        else if (cursor.getY() == 190) {
            dxManager->switchScene("Title");
        }
        else if (cursor.getY() == 220) {
            PostQuitMessage(0);
        }
    }
    if (dxManager->getInput()->wasKeyPressed(CURSOR_DOWN_KEY) && cursor.getY() != 220)               // if move up
    {
        cursor.setY(cursor.getY() + 30);
    }
    if (dxManager->getInput()->wasKeyPressed(CURSOR_UP_KEY) && cursor.getY() != 100)               // if move up
    {
        cursor.setY(cursor.getY() - 30);
    }
    if (dxManager->getInput()->wasKeyPressed(VK_LEFT)) {

    }
    cursor.update(frameTime);
}

void PauseMenu::ai()
{
}

void PauseMenu::collisions()
{
}

//=============================================================================
// render game items
//=============================================================================
void PauseMenu::render()
{
    const int BUF_SIZE = 100;
    static char buffer[BUF_SIZE];
    dxManager->getGraphics()->spriteBegin();
    cursor.draw(TRANSCOLOR);
    dxMenuText->setFontColor(graphicsNS::BLACK);
    dxMenuText->print("Back", 60, menuStartY);
    dxMenuText->print("Stats", 60, menuStartY + 30);
    dxMenuText->print("Save", 60, menuStartY + 60);
    dxMenuText->print("Return to Title", 60, menuStartY + 90);
    dxMenuText->print("Exit Game", 60, menuStartY + 120);
    dxFont.setFontColor(gameNS::FONT_COLOR);
    sprintf_s(buffer, "You have selected: %d", (int)debugY);
    dxFont.print(buffer, 200, 200);
    dxManager->getGraphics()->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void PauseMenu::releaseAll()
{
    mainCharaTexture.onLostDevice();
    dxMenuText->onLostDevice();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void PauseMenu::resetAll()
{
    mainCharaTexture.onResetDevice();
    dxMenuText->onResetDevice();
    return;
}