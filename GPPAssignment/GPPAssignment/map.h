#ifndef _MAP_H             // prevent multiple definitions if this 
#define _MAP_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "TextureManager.h"
#include "Image.h"
#include "character.h"

using namespace std;

class Map : public Game
{
protected:
    TextDX  dxFont;                 // DirectX font for fps
    
    TextureManager mainCharaTexture;
    TextDX  infoFonts;
    TextDX* dxMenuText;

    Character mainChara;

    int yValues[3] = { 100, 130, 160 }; // Y values for menu
    std::string optionSelected;
    int y; // y values

    int animateIndex = 5;
    int index = 0;
    int direction = -1;
public:
    // Constructor
    Map();

    // Destructor
    virtual ~Map();

    void initialize(HWND hwnd);

    //Override virtual in from Game
    void reset();
    void update();
    void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
    
    void checkMouse();

    void intializeUI();
    void renderUI();
    void intializeCharacters();
    void renderCharacters();
};
#endif // !_MAP_H