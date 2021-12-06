#include "startingMenu.h"
#include <iostream>

StartingMenu::StartingMenu(SceneManager* manager)
{
    dxManager = manager;
    dxMenuText = new TextDX();

    // This menu list has the following functions: Start, Options, Quit
    menuList.push_back({ "Start", 60, 100 });
    menuList.push_back({ "Options", 60, 130 });
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
    // Initializing Cursor
    if (!cursorTexture.initialize(dxManager->getGraphics(), Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
    if (!cursor.initialize(dxManager->getGraphics(), 0, 0, 0, &cursorTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

    // Cursor settings on initialize
    cursor.setX(menuList.front().x - 20);
    cursor.setY(menuList.front().y);
    cursor.setScale(0.5, 0.5);

    // Set background colour: White
    dxManager->getGraphics()->setBackColor(graphicsNS::WHITE);

    // initialize DirectX fonts
    // 15 pixel high Arial
    if (dxMenuText->initialize(dxManager->getGraphics(), 15, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

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
    // When enter is pressed, check for which string it's currently at
    if (dxManager->getInput()->wasKeyPressed(VK_RETURN)) 
    {
        optionSelected(menuList.at(menuIndex).option);
    }
    // Move down
    if (dxManager->getInput()->wasKeyPressed(CURSOR_DOWN_KEY) && menuIndex != (menuList.size() - 1))
    {
        menuIndex++; // Increases menu index to tell where the location of the cursor is
        cursor.setX(menuList.at(menuIndex).x - 20);
        cursor.setY(menuList.at(menuIndex).y);
    }
    // Move up
    if (dxManager->getInput()->wasKeyPressed(CURSOR_UP_KEY) && menuIndex != 0)
    {
        menuIndex--; // Decreases menu index to tell where the location of the cursor is
        cursor.setX(menuList.at(menuIndex).x - 20);
        cursor.setY(menuList.at(menuIndex).y);
    }
    cursor.update(frameTime);
}


//====================================================
// Check string of current option
// Return the function
// ===================================================
// *Switch case doesn't work because C++ doesn't allow strings in switch cases.
void StartingMenu::optionSelected(std::string option) {
    // Start -> Overworld
    if (option == "Start")
    {
        dxManager->switchScene("Overworld");
    }
    // Option -> Whatever options we have
    else if (option == "Options")
    {
        dxManager->switchScene("PauseMenu");
        // dxManager->switchScene("Battle");
    }
    // Quit -> Quit the game
    else if (option == "Quit")
    {
        PostQuitMessage(0);
    }
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
    for(auto option: menuList) 
    {
        dxMenuText->print(option.option, option.x, option.y);
    }
    dxManager->getGraphics()->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void StartingMenu::releaseAll()
{
    cursorTexture.onLostDevice();
    dxMenuText->onLostDevice();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void StartingMenu::resetAll()
{
    cursorTexture.onResetDevice();
    dxMenuText->onResetDevice();
    return;
}