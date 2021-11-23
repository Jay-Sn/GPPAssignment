#ifndef _PFANTASY_H
#define _PFANTASY_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "TextureManager.h"
#include "Image.h"
#include "character.h"
#include "textDX.h"
#include "pfantasy.h"

using namespace std;

class PFantasy : public Game
{
private:
	//Variables
	float yValues[3] = { 550, 600, 650 }; // Y values for menu

	TextureManager mainCharaTexture;
	TextureManager placeholderRectTexture;

	TextDX  infoFonts;
	TextDX  selectionFonts;

	TextDX* dxMenuText;

	Character mainChara;
	Character enemyChara;

	Image eHealthBar;
	Image healthBar;

	Image enemyNameSection;
	Image abilitySection;
	Image infoSection;

	Image floor;
	Image selectionBlock;
	int selectionY;

public:
	PFantasy();					//Constructor
	virtual ~PFantasy();		//Destructor

	void initialize(HWND hwnd);

	//Override virtual in from Game
	void update();
	void ai();
	void collisions();
	void checkMouse();
	void render();
	void releaseAll();
	void resetAll();
	void deductHealth(bool e, float hp);
	void updateHealth();
	void intializeUI();
	void renderUI();
	void intializeCharacters();
	void renderCharacters();
};
#endif // !_PFANTASY_H
