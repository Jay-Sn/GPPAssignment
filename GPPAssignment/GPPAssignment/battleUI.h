#ifndef _BATTLEUI_H
#define _BATTLEUI_H_
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <map>
#include <vector>

#include "menuOption.h"
#include "image.h"
#include "texturemanager.h"
#include "game.h"
#include "character.h"
#include "constants.h"
#include "input.h"
#include "SceneManager.h"

class BattleUI : public Image
{
public:
	BattleUI();
	~BattleUI();

	bool initialize(Game* gameptr, std::vector<Character>* listOfCharacters );
	
	void healthBarSetup(Game* gameptr);

	void update(Game* gameptr, float frameTime);

	void draw();

	void setHpPosYEnemy();
	void setHpPosYTeam();
	void drawHealthBars();

	bool updateHpBars(Character character, float frameTime);

	//Setup Selection Menu
	void selectionMenuSetup(Game* gameptr);

	void selectionMenuPrint();

	std::string checkSelection(Game* gameptr);

	bool isChecking() { return checking; }
	void StartChecking() { checking = true; }

	bool getGameState() { return gameOver; }
	void setGameState() { gameOver = false; }

	void releaseAll();

	void resetAll();

private:
	float yValues[3] = { 550, 600, 650 }; // Y values for menu

	TextureManager UITexture;
	TextureManager SelectionArrowTexture;

	Image selectionArrow;

	TextDX  hpFont;
	TextDX  selectionFont;
	TextDX  infoFont;

	std::vector<Character>* listOfCharactersInPlay;

	bool gameOver;

	bool checking;

	int checkingIndex;

	std::vector<MenuOption> selectionList;

	int selectionIndex;

	//======================================================
	//					 Health Bars
	//======================================================
	Image actionBar;

	//Health Bars to be used
	Image healthBar1;
	Image healthBar2;
	Image healthBar3;
	Image healthBar4;
	Image healthBar5;
	Image healthBar6;
	Image healthBar7;
	Image healthBar8;

	// Max number of healthBar for each character is 8 (4 v 4)
	std::vector<Image> listOfHealth = {		// Used To store all healthbar
		healthBar1,
		healthBar2,
		healthBar3,
		healthBar4,
		healthBar5,
		healthBar6,
		healthBar7,
		healthBar8
	};

	std::map<string, Image> usedHealthBar;

	std::vector<float> enemyHpPosY;
	std::vector<float> teamHpPosY;

	std::vector<Character> enemyTeam;
	std::vector<Character> friendlyTeam;

};
#endif // !_BATTLEUI_H