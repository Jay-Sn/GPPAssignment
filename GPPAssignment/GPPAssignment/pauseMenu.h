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
#include "SceneManager.h"
#include <iostream>
#include <list>

//===================
// MENU CLASS
//===================
class PauseMenu : public Scene
{
protected:
    SceneManager* dxManager;
    TextDX  dxFont;                 // DirectX font for fps
    TextDX* dxMenuText;
    TextureManager mainCharaTexture;

    int menuX = 60;
    int menuStartY = 100; // Increment by 30
    int subX = 100;
    int subStartY = 100;
    std::list<std::string> subMenu;
    bool subMenuOn;
    Image cursor;

    std::string optionSelected;
    int debugY; // y values for debugging purposes; is now a placeholder

    int animateIndex = 5;
    int index = 0;
    int direction = -1;
public:
    // Constructor
    PauseMenu(SceneManager* manager);

    // Destructor
    virtual ~PauseMenu();

    void initialize();
    void reset();
    void update(float frameTime);
    void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
};
#endif#pragma once
