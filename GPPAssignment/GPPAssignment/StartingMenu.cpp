//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
#include "startingMenu.h"
#include <iostream>

StartingMenu::StartingMenu(SceneManager* manager)
{
    dxManager = manager;
    dxMenuText = new TextDX();
    dxTitle = new TextDX();
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
    // Reset menu index to 0 on initialize
    menuIndex = 0;

    // Initializing Cursor
    if (!cursorTexture.initialize(dxManager->getGraphics(), Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating Cursor");
    if (!cursor.initialize(dxManager->getGraphics(), 0, 0, 0, &cursorTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Cursor");

    // Set background colour: White
    dxManager->getGraphics()->setBackColor(graphicsNS::WHITE);

    float textSize = 25; // dxMenuText size
    float titleSize = 100; // dxTitle size
    float originalCursorHeight = cursorTexture.getHeight(); // Original height of cursor
    float originalCursorWidth = cursorTexture.getWidth();   // Original width of cursor
    float scaledCursorHeight = textSize / originalCursorHeight;  // Height of cursor after scaling
    float scaledCursorWidth = textSize / originalCursorWidth;    // Width of cursor after scaling

    // initialize DirectX fonts
    // Option Text
    // Font: Trebuchet MS
    if (dxMenuText->initialize(dxManager->getGraphics(), textSize, true, false, "Trebuchet MS") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    // Title
    // Font: Old English Text MT
    if (dxTitle->initialize(dxManager->getGraphics(), titleSize, true, false, "Old English Text MT") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    std::vector<std::string> optionList = { "Start New Adventure", "Continue", "Options", "Quit" }; // Option list contains these options

    int menuY = GAME_HEIGHT / 2; // Half of game height

    // Add to menuList the options from optionList
    for (int i = 0; i < optionList.size(); i++)
    {
        menuList.push_back({ 
            /*Option = */optionList.at(i),
            /*X = */int(GAME_WIDTH / 2 - dxMenuText->getWidth(optionList.at(i), dxMenuText->getFont()) / 2),
            /*Y = */menuY + 30 * i
            });
    }

    // Cursor settings on initialize
    cursor.setX(menuList.front().x - 30);
    cursor.setY(menuList.front().y);
    cursor.setScale(scaledCursorHeight, scaledCursorWidth);

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
        // cursor.setX(menuList.at(menuIndex).x - 20);
        cursor.setY(menuList.at(menuIndex).y);
    }
    // Move up
    if (dxManager->getInput()->wasKeyPressed(CURSOR_UP_KEY) && menuIndex != 0)
    {
        menuIndex--; // Decreases menu index to tell where the location of the cursor is
        // cursor.setX(menuList.at(menuIndex).x - 20);
        cursor.setY(menuList.at(menuIndex).y);
    }
    cursor.update(frameTime);
}


//====================================================
// Check string of current option
// Return the function
//====================================================
// *Switch case doesn't work because C++ doesn't allow strings in switch cases.
void StartingMenu::optionSelected(std::string option) {
    // Start New Adventure -> Overworld at default position
    if (option == "Start New Adventure")
    {
        dxManager->getState()->resetState();
        dxManager->switchScene("Overworld");
    }
    // Continue -> Overworld at saved position
    else if (option == "Continue")
    {
        // Read file placeholder_save.txt
        std::ifstream file("placeholder_save.txt");
        std::string key, value, type; // key for map key, value for the actual key
        while (file >> key >> value >> type) // Get the key, value and type, where the delim is a space
        { 
            dxManager->getState()->setValueToState(key, { value, type }); // Put to the globalMap
        }
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
    dxTitle->setFontColor(graphicsNS::ORANGE);
    dxTitle->print("PlaceHolder Fantasy?", int(GAME_WIDTH / 2 - dxTitle->getWidth("PlaceHolder Fantasy?", dxTitle->getFont()) / 2), GAME_HEIGHT / 2 - 100);
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
    dxTitle->onLostDevice();
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
    dxTitle->onResetDevice();
    return;
}