#ifndef _PFANTASY_H
#define _PFANTASY_H
#define WIN32_LEAN_AND_MEAN

#include <vector>

#include "game.h"
#include "TextureManager.h"
#include "Image.h"
#include "character.h"
#include "battleUI.h"
#include "textDX.h"
#include "SceneManager.h"

class BattleScene : public Scene
{
private:
	//Variables
	float yValues[3] = { 550, 600, 650 }; // Y values for menu
	SceneManager* dxManager;
	BattleUI battleUI;

	TextureManager mainCharaTexture;
	TextureManager placeholderRectTexture;

	TextDX  hpFonts;
	TextDX  selectionFonts;
	TextDX  infoFonts;

	TextDX* dxMenuText;

	Character mainChara;
	Character enemyChara;

	Character checkCharacterHealth;

	std::vector<Character> characterList;

	Image eHealthBar;
	Image healthBar;

	Image enemyNameSection;
	Image abilitySection;
	Image actionBarinfoSection;

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
	void render();
	void releaseAll();
	void resetAll();

};
#endif // !_PFANTASY_H
