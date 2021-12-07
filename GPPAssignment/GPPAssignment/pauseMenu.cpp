//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
#include "pauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(SceneManager* manager)
{
    dxManager = manager;
    dxMenuText = new TextDX();     // DirectX fonts
    menuList.push_back({ "Back", 60, 100 });
    menuList.push_back({ "Stats", 60, 130 });
    menuList.push_back({ "Save", 60, 160 });
    menuList.push_back({ "Return to Title", 60, 190 });
    menuList.push_back({ "Exit Game", 60, 220 });
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
    if (!cursorTexture.initialize(dxManager->getGraphics(), Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
    if (!cursor.initialize(dxManager->getGraphics(), 0, 0, 0, &cursorTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
    
    cursor.setX(menuList.front().x - 20);
    cursor.setY(menuList.front().y);
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
        optionSelected(menuList.at(menuIndex).option);
    }
    if (dxManager->getInput()->wasKeyPressed(CURSOR_DOWN_KEY) && menuIndex != (menuList.size() - 1))               // if move down
    {
        menuIndex++;
        cursor.setX(menuList.at(menuIndex).x - 20);
        cursor.setY(menuList.at(menuIndex).y);
    }
    if (dxManager->getInput()->wasKeyPressed(CURSOR_UP_KEY) && menuIndex != 0)               // if move up
    {
        menuIndex--;
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
void PauseMenu::optionSelected(std::string option) {
    if (option == "Back")
    {
        dxManager->switchScene("Overworld");
    }
    else if (option == "Stats")
    {

    }
    else if (option == "Save")
    {
        std::ifstream file("placeholder_save.txt");
        if (!file.is_open())
        {
            std::ofstream newFile("placeholder_save.txt");
            newFile << "WorldX " << dxManager->getState()->getFloatFromState("WorldX") << std::endl;
            newFile << "WorldY " << dxManager->getState()->getFloatFromState("WorldY") << std::endl;
            newFile.close();
        }
        else
        {
            std::remove("placeholder_save.txt");
            std::ofstream newFile("placeholder_save.txt");
            newFile << "WorldX " << dxManager->getState()->getFloatFromState("WorldX") << std::endl;
            newFile << "WorldY " << dxManager->getState()->getFloatFromState("WorldY") << std::endl;
            newFile.close();
        }
    }
    else if (option == "Return to Title")
    {
        dxManager->getState()->resetState();
        dxManager->switchScene("Title");
    }
    else if (option == "Exit Game")
    {
        PostQuitMessage(0);
    }
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
    dxManager->getGraphics()->spriteBegin();
    cursor.draw(TRANSCOLOR);
    dxMenuText->setFontColor(graphicsNS::BLACK);
    for (auto option : menuList)
    {
        dxMenuText->print(option.option, option.x, option.y);
    }
    dxFont.setFontColor(gameNS::FONT_COLOR);
    dxManager->getGraphics()->spriteEnd();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void PauseMenu::releaseAll()
{
    cursorTexture.onLostDevice();
    dxMenuText->onLostDevice();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void PauseMenu::resetAll()
{
    cursorTexture.onResetDevice();
    dxMenuText->onResetDevice();
    return;
}