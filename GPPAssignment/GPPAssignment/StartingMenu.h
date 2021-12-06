#ifndef _STARTINGMENU_H             // prevent multiple definitions if this 
#define _STARTINGMENU_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "TextureManager.h"
#include "Image.h"
#include "graphics.h"
#include "Scene.h"
#include "SceneManager.h"
#include "menuOption.h"
#include <vector>

//===================
// MENU CLASS
//===================
class StartingMenu: public Scene
{
protected:
    SceneManager* dxManager;
    TextDX  dxFont;                 // DirectX font for fps
    TextDX* dxMenuText;
    TextureManager cursorTexture;

    int menuIndex = 0;
    std::vector<MenuOption> menuList;

    Image cursor;
public:
    // Constructor
    StartingMenu(SceneManager* manager);

    // Destructor
    virtual ~StartingMenu();

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
