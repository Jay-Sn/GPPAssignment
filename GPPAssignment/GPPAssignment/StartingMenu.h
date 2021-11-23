#ifndef _STARTINGMENU_H             // prevent multiple definitions if this 
#define _STARTINGMENU_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "TextureManager.h"
#include "Image.h"
#include "graphics.h"
#include "pfantasy.h"

//===================
// MENU CLASS
//===================
class StartingMenu: public Game
{
protected:
    TextDX  dxFont;                 // DirectX font for fps
    TextDX* dxMenuText;
    TextureManager mainCharaTexture;

    Image mainChara;

    int yValues[4] = { 100, 130, 160 }; // Y values for menu
    std::string optionSelected;
    int debugY; // y values for debugging purposes; is now a placeholder

    int animateIndex = 5;
    int index = 0;
    int direction = -1;
public:
    // Constructor
    StartingMenu();

    // Destructor
    virtual ~StartingMenu();

    void initialize(HWND hwnd);
    void reset();
    void update();
    void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
};
#endif
