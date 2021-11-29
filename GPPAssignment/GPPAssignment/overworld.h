#ifndef _MAP_H             // prevent multiple definitions if this 
#define _MAP_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textDX.h"
#include "constants.h"
#include "TextureManager.h"
#include "Image.h"
#include "SceneManager.h"

using namespace std;

class Overworld : public Scene
{
protected:
    SceneManager* dxManager;

    //Texture for mainCharacter;
    TextureManager mainCharaTexture;

    //Player Character Image
    Image playerChara;


public:
    // Constructor
    Overworld(SceneManager* manager);

    // Destructor
    virtual ~Overworld();

    //Initialize world
    void initialize();

    //Override virtual in from Game
    void reset();
    void update(float frameTime);
    void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
    
    //If you are using this in the future please rename it to something that is relevant to what it is used for.
    //void checkMouse();

    //void intializeUI();
    //void renderUI();

    void intializeCharacters();
    void renderCharacters();
};
#endif // !_MAP_H