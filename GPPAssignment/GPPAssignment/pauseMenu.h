//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
#ifndef _PAUSEMENU_H             // prevent multiple definitions if this 
#define _PAUSEMENU_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "TextureManager.h"
#include "Image.h"
#include "graphics.h"
#include "Scene.h"
#include "sceneManager.h"
#include "menuOption.h"
#include <vector>
#include <iostream>
#include <fstream>

//===================
// MENU CLASS
//===================
class PauseMenu : public Scene
{
protected:
    SceneManager* dxManager;
    TextDX  dxFont;                 // DirectX font for fps
    TextDX* dxMenuText;
    TextureManager cursorTexture;

    std::vector<MenuOption> menuList;
    std::vector<MenuOption> subList;

    bool subMenuOn;
    Image cursor;

    int menuIndex = 0;
    int subIndex;
public:
    // Constructor
    PauseMenu(SceneManager* manager);

    // Destructor
    virtual ~PauseMenu();

    void initialize();
    void reset();
    void update(float frameTime);
    void optionSelected(std::string option);
    void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
};
#endif
