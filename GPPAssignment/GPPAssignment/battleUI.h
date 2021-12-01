#ifndef _BATTLEUI_H
#define _BATTLEUI_H_
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <map>
#include <vector>

#include "image.h"
#include "texturemanager.h"
#include "game.h"
#include "character.h"
#include "constants.h"

class BattleUI : public Image
{
public:
	float yValues[3] = { 550, 600, 650 }; // Y values for menu

	TextureManager UITexture;
	TextureManager SelectionArrowTexture;

	Image selectionArrow;

	TextDX  hpFonts;
	TextDX  selectionFonts;
	TextDX  infoFonts;

	BattleUI();
	~BattleUI();

	bool initialize(Game* gameptr, std::vector<Character> listOfCharacters );
	
	void healthBarSetup(Game* gameptr, std::vector<Character> listOfCharacters);

	void update(Game* gameptr);

	void draw();

	void setHpPosYEnemy();
	void setHpPosYTeam();

	bool updateHpBars(Character character, float frameTime);

	bool animationDone = true;

	int selectionY = 0;

private:
	std::vector<Character> listOfCharactersInPlay;

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

};
#endif // !_BATTLEUI_H