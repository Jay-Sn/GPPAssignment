#include "pfantasy.h"
using namespace std;
PFantasy::PFantasy() {}

PFantasy::~PFantasy()
{
	releaseAll();			//call onLostDevice() for every graphics item
}

//Initialize the game
void PFantasy::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	if (dxFont.initialize(graphics, 15, true, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	if (!mainCharaTexture.initialize(graphics, MAINCHARA_IMAGE))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");
	if (!placeholderRectTexture.initialize(graphics, PLACEHOLDERRECT))throw(gameErrorNS::FATAL_ERROR, "Error initiating placeholder rect");

	if (!mainChara.initialize(graphics,0,0,0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

	if (!healthBar.initialize(graphics, HPBAR_WIDTH, HPBAR_HEIGHT, 1, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating healthBar");
	if (!eHealthBar.initialize(graphics, HPBAR_WIDTH, HPBAR_HEIGHT, 1, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating eHealthBar");

	if (!enemyNameSection.initialize(graphics,0,0,0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating enemyNameSection");
	if (!abilitySection.initialize(graphics,0,0,0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating abilitySection");
	if (!infoSection.initialize(graphics,0,0,0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");
	if (!floor.initialize(graphics,0,0,0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");
	floor.setY(GAME_HEIGHT/2);
	floor.setX(-200);
	mainChara.setY(GAME_HEIGHT / 2 - mainChara.getHeight());
	mainChara.setX(GAME_WIDTH * 0.75f - mainChara.getWidth() / 2);
	floor.setScale(10, 10);
	//display Sections
	enemyNameSection.setScaleY(1.25);
	enemyNameSection.setX(0);
	enemyNameSection.setY(GAME_HEIGHT - enemyNameSection.getHeight());

	abilitySection.setScaleY(1.25);
	abilitySection.setX(enemyNameSection.getWidth());
	abilitySection.setY(GAME_HEIGHT - enemyNameSection.getHeight());

	infoSection.setScale(2,1.25);
	infoSection.setX(GAME_WIDTH - infoSection.getWidth());
	infoSection.setY(GAME_HEIGHT - infoSection.getHeight());

	//display Information
	//healthBar.setScale(0.75, 0.1);
	healthBar.setCurrentFrame(1);
	healthBar.setX(infoSection.getX() + 0.0625 * infoSection.getWidth());
	healthBar.setY(infoSection.getY() + 0.25 * infoSection.getHeight());

	//eHealthBar.setScale(0.75, 0.1);
	eHealthBar.setCurrentFrame(1);
	eHealthBar.setX(enemyNameSection.getX() + 0.125 * enemyNameSection.getWidth());
	eHealthBar.setY(enemyNameSection.getY() + 0.25 * enemyNameSection.getHeight());

	mainChara.setScale(2,2);
	
	return;
}

//Update all game items
void PFantasy::update() {
	if (input->wasKeyPressed(NAVI_LEFT_KEY)) {
		deductHealth(true, 50);
	}
	if (input->wasKeyPressed(NAVI_UP_KEY)) {
		deductHealth(true, -50);
	}
	if (input->wasKeyPressed(NAVI_RIGHT_KEY)) {
		deductHealth(false,50);
	}
	if (input->wasKeyPressed(NAVI_DOWN_KEY)) {
		deductHealth(false, -50);
	}
	updateHealth();
}

void PFantasy::updateHealth() {

	//Player Health
	if (CURRENT_HEALTH <= 0 && healthBar.getScaleX() > 0)
		healthBar.setScaleX(healthBar.getScaleX() - 0.1 * frameTime);
	else if (CURRENT_HEALTH > 0 && healthBar.getScaleX() > (CURRENT_HEALTH / FULL_HEALTH)) {
		healthBar.setScaleX(healthBar.getScaleX() - 0.1 * frameTime);
	}

	if (CURRENT_HEALTH> FULL_HEALTH && healthBar.getScaleX() <= 1) {
		healthBar.setScaleX(healthBar.getScaleX() + 0.1 * frameTime);
	}
	else if (CURRENT_HEALTH <= FULL_HEALTH && healthBar.getScaleX() <= CURRENT_HEALTH/FULL_HEALTH) {
		healthBar.setScaleX(healthBar.getScaleX() + 0.1 * frameTime);
	}

	//Enemy Health
	if (ECURRENT_HEALTH <= 0 && eHealthBar.getScaleX() > 0)
		eHealthBar.setScaleX(eHealthBar.getScaleX() - 0.1 * frameTime);
	else if (ECURRENT_HEALTH > 0 && eHealthBar.getScaleX() > (ECURRENT_HEALTH / EFULL_HEALTH)) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() - 0.1 * frameTime);
	}

	if (ECURRENT_HEALTH > EFULL_HEALTH && eHealthBar.getScaleX() <= 1) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() + 0.1 * frameTime);
	}
	else if (ECURRENT_HEALTH <= EFULL_HEALTH && healthBar.getScaleX() <= ECURRENT_HEALTH / EFULL_HEALTH) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() + 0.1 * frameTime);
	}
}

void PFantasy::deductHealth(bool e, float hp) {
	if (e) CURRENT_HEALTH -= hp;
	else ECURRENT_HEALTH -= hp;
}
//Artificial Intelligence
void PFantasy::ai() {}

//Handle collisions
void PFantasy::collisions() {}

//Render game items
void PFantasy::render() {
	graphics->spriteBegin();

	floor.draw(graphicsNS::TEAL);
	mainChara.draw(TRANSCOLOR);
	enemyNameSection.draw(TRANSCOLOR);
	abilitySection.draw(TRANSCOLOR);
	infoSection.draw(TRANSCOLOR);

	healthBar.draw(graphicsNS::RED);
	eHealthBar.draw(graphicsNS::RED);
	dxFont.setFontColor(graphicsNS::WHITE);
	//std::string health = CURRENT_HEALTH + " / " + FULL_HEALTH;
	sprintf_s(buffer,20, "%d / %d", (int)CURRENT_HEALTH, (int)FULL_HEALTH);
	dxFont.print(buffer, healthBar.getX() + HPBAR_WIDTH/2 - dxFont.getWidth(buffer, dxFont.getFont()) / 2, healthBar.getY() + dxFont.getHeight(buffer,dxFont.getFont())/2);
	sprintf_s(ebuffer, 20, "%d / %d", (int)ECURRENT_HEALTH, (int)EFULL_HEALTH);
	dxFont.print(ebuffer, eHealthBar.getX() + HPBAR_WIDTH/2 - dxFont.getWidth(ebuffer, dxFont.getFont())/2, eHealthBar.getY() + dxFont.getHeight(ebuffer, dxFont.getFont())/2);
	graphics->spriteEnd();
}

//The graphics device was lost
//Release all reserved video memory to be resetted
void PFantasy::releaseAll() {
	mainCharaTexture.onLostDevice();
	placeholderRectTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//The graphics device has been reset.
//Recreate all reserved video memory to reset graphics device
void PFantasy::resetAll() {
	mainCharaTexture.onResetDevice();
	placeholderRectTexture.onResetDevice();
	Game::resetAll();
	return;
}

