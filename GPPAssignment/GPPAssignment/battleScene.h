//===========================================================================================
//	Module		: Game Programming
//	Assignment	: Placeholder Fantasy?	
//	Name		: Jason Teo Jun Hao
//	S/N			: S10194978
//	Description	: This header file is for the scene that will be handling the battle
//				  in the game. Here is supposed to make use of the BattleUI and
//				  CharacterBattleManager to deal with battle state / Menu selections
//				  and Displaying of any Images.
//===========================================================================================

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
#include "sceneManager.h"
#include "characterBattleManager.h"

class BattleScene : public Scene
{
private:
	SceneManager* dxManager;
	BattleUI battleUI;
	CharacterBattleManager characterBM;

	TextureManager mainCharaTexture;
	TextureManager placeholderRectTexture;

	TextDX  hpFonts;
	TextDX  selectionFonts;
	TextDX  infoFonts;

	TextDX* dxMenuText;

	Character mainChara;
	Character enemyChara;

	Character checkCharacterHealth;

	std::vector<Character>* characterList;

	Image eHealthBar;
	Image healthBar;

	Image enemyNameSection;
	Image abilitySection;
	Image actionBarinfoSection;

	Image floor;
	Image selectionBlock;

	bool check;
	bool animationDone = true;

	float ifDefend;

	int attackPhase;
	int selectionY;

	std::string optionChosen;
public:
	BattleScene(SceneManager* manager);					//Constructor
	virtual ~BattleScene();								//Destructor

	void initialize();

	//Override virtual in from Game
	void update(float frameTime);
	void ai();
	void reset();
	void collisions();
	void render();

	void checkSelectionChosen(std::string option);

	void turnSystem();

	void releaseAll();
	void resetAll();

};
#endif // !_PFANTASY_H
