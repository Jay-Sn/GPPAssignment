#ifndef _PFANTASY_H
#define _PFANTASY_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "TextureManager.h"
#include "Image.h"
#include "textDX.h"
#define GetSizeOf(a)			sizeof(a)/sizeof(*a)
class PFantasy : public Game
{
private:
	//Variables
	TextureManager mainCharaTexture;
	TextureManager placeholderRectTexture;
	TextDX  dxFont;                 // DirectX font for fps
	TextDX* dxMenuText;

	Image healthBar;
	Image eHealthBar;
	Image mainChara;
	Image enemyNameSection;
	Image abilitySection;
	Image infoSection;

	//Player Health
	float FULL_HEALTH = 100;
	float BATTLE_HEALTH = FULL_HEALTH;
	float CURRENT_HEALTH = BATTLE_HEALTH;

	//Enemy Health
	float EFULL_HEALTH = 100;
	float EBATTLE_HEALTH = FULL_HEALTH;
	float ECURRENT_HEALTH = 100;

	int animateIndex = 5;
	int index = 0;
	int direction = -1;

	char buffer[100];
	char ebuffer[100];
public:
	PFantasy();					//Constructor
	virtual ~PFantasy();		//Destructor

	void initialize(HWND hwnd);

	//Override virtual in from Game
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
	void deductHealth(bool e, float hp);
	void updateHealth();
};
#endif // !_SPACEWAR_H
