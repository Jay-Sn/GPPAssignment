#ifndef _STARTINGMENU_H             // prevent multiple definitions if this 
#define _STARTINGMENU_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "textDX.h"
#include "constants.h"

//===================
//MENU CLASS
//===================
class StartingMenu
{
protected:
    TextDX* dxMenuText;
public:
    // Constructor
    StartingMenu();

    // Destructor
    virtual ~StartingMenu();

    void initialize(HWND hwnd);
    void update();
};
#endif
