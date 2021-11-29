#ifndef _PFANTASY_H
#define _PFANTASY_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "TextureManager.h"
#include "Image.h"
#include "character.h"
#include "textDX.h"
#include "SceneManager.h"

class BattleScene : public Scene
{
private:
	//Variables
	float yValues[3] = { 550, 600, 650 }; // Y values for menu
	SceneManager* dxManager;

	TextureManager mainCharaTexture;
	TextureManager placeholderRectTexture;

	TextDX  hpFonts;
	TextDX  selectionFonts;
	TextDX  infoFonts;

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

	bool animationDone = true;
	int attackPhase;
	int selectionY;

public:
	BattleScene(SceneManager* manager);					//Constructor
	virtual ~BattleScene();		//Destructor

	void initialize();

	//Override virtual in from Game
	void update(float frameTime);
	void ai();
	void reset();
	void collisions();
	void checkMouse();
	void render();
	void releaseAll();
	void resetAll();
	void deductHealth(bool e, float hp);
	void updateHealth(float frameTime);
	void intializeUI();
	void renderUI();
	void intializeCharacters();
	void renderCharacters();
	void changePhase();
	void enemyAction();
};
#endif // !_PFANTASY_H
