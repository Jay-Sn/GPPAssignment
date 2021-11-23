#include "pfantasy.h"
using namespace std;
PFantasy::PFantasy() {


}

PFantasy::~PFantasy()
{
	releaseAll();			//call onLostDevice() for every graphics item

}

//Initialize the game
void PFantasy::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError
	intializeUI();
	intializeCharacters();

	return;
}

//Update all game items
void PFantasy::update() {
	checkMouse();
	//updateHealth();
}

void PFantasy::updateHealth() {
	//Player Health
	if (mainChara.getCurrentHealth() <= 0 && healthBar.getScaleX() > 0)
		healthBar.setScaleX(healthBar.getScaleX() - 0.1 * MIN_FRAME_RATE);
	else if (mainChara.getCurrentHealth() > 0 && healthBar.getScaleX() > (mainChara.getCurrentHealth() / mainChara.getMaxHealth())) {
		healthBar.setScaleX(healthBar.getScaleX() - 0.1 * MIN_FRAME_RATE);
	}

	if (mainChara.getCurrentHealth() > mainChara.getMaxHealth() && healthBar.getScaleX() <= 1) {
		healthBar.setScaleX(healthBar.getScaleX() + 0.1 * MIN_FRAME_RATE);
	}
	else if (mainChara.getCurrentHealth() <= mainChara.getMaxHealth() && healthBar.getScaleX() <= mainChara.getCurrentHealth() / mainChara.getMaxHealth()) {
		healthBar.setScaleX(healthBar.getScaleX() + 0.1 * MIN_FRAME_RATE);
	}

	//Enemy Health
	if (enemyChara.getCurrentHealth() <= 0 && healthBar.getScaleX() > 0)
		eHealthBar.setScaleX(eHealthBar.getScaleX() - 0.1 * MIN_FRAME_RATE);
	else if (enemyChara.getCurrentHealth() > 0 && healthBar.getScaleX() > (enemyChara.getCurrentHealth() / enemyChara.getMaxHealth())) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() - 0.1 * MIN_FRAME_RATE);
	}

	if (enemyChara.getCurrentHealth() > enemyChara.getMaxHealth() && healthBar.getScaleX() <= 1) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() + 0.1 * MIN_FRAME_RATE);
	}
	else if (enemyChara.getCurrentHealth() <= enemyChara.getMaxHealth() && healthBar.getScaleX() <= enemyChara.getCurrentHealth() / enemyChara.getMaxHealth()) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() + 0.1 * MIN_FRAME_RATE);
	}
}

void PFantasy::deductHealth(bool enemy, float hp) {
	if (enemy) {
		enemyChara.deductHealth(hp);
	}
	else {
		mainChara.deductHealth(hp);
	}
}

//Artificial Intelligence
void PFantasy::ai() {}

//Handle collisions
void PFantasy::collisions() {}

void PFantasy::checkMouse() {
	if (input->wasKeyPressed(NAVI_DOWN_KEY) && input->getMouseX() >= abilitySection.getX() && input->getMouseX() <= abilitySection.getX() + abilitySection.getWidth()) {
		if (input->getMouseY() >= abilitySection.getY() && input->getMouseY() <= abilitySection.getY() + abilitySection.getHeight()) {
			deductHealth(false, 10);
		}
	}
}
//Render game items
void PFantasy::render() {
	graphics->spriteBegin();

	floor.draw(graphicsNS::TEAL);

	renderCharacters();
	renderUI();

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

void PFantasy::intializeUI() {

	if (infoFonts.initialize(graphics, 10, true, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	if (!placeholderRectTexture.initialize(graphics, PLACEHOLDERRECT))throw(gameErrorNS::FATAL_ERROR, "Error initiating placeholder rect");
	if (!floor.initialize(graphics, 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");

	//CharacterInformation UI
	if (!healthBar.initialize(graphics, HPBAR_WIDTH, HPBAR_HEIGHT, 1, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating healthBar");
	if (!eHealthBar.initialize(graphics, HPBAR_WIDTH, HPBAR_HEIGHT, 1, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating eHealthBar");

	//Quad UI
	if (!enemyNameSection.initialize(graphics, 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating enemyNameSection");
	if (!abilitySection.initialize(graphics, 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating abilitySection");
	if (!infoSection.initialize(graphics, 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");
	
	//Floor Stuff (To Be removed)
	floor.setY(GAME_HEIGHT / 2);
	floor.setX(-200);
	floor.setScale(10, 10);

	//Display Sections
	enemyNameSection.setScaleY(1.25);
	enemyNameSection.setX(0);
	enemyNameSection.setY(GAME_HEIGHT - enemyNameSection.getHeight());

	abilitySection.setScaleY(1.25);
	abilitySection.setX(enemyNameSection.getWidth());
	abilitySection.setY(GAME_HEIGHT - abilitySection.getHeight());

	infoSection.setScale(2, 1.25);
	infoSection.setX(GAME_WIDTH - infoSection.getWidth());
	infoSection.setY(GAME_HEIGHT - infoSection.getHeight());

	//display Information
	healthBar.setCurrentFrame(1);
	healthBar.setX(infoSection.getX() + 0.0625 * infoSection.getWidth());
	healthBar.setY(infoSection.getY() + 0.25 * infoSection.getHeight());

	eHealthBar.setCurrentFrame(1);
	eHealthBar.setX(enemyNameSection.getX() + 0.125 * enemyNameSection.getWidth());
	eHealthBar.setY(enemyNameSection.getY() + 0.25 * enemyNameSection.getHeight());

}

void PFantasy::renderUI() {

	//Section Draw
	enemyNameSection.draw(TRANSCOLOR);
	abilitySection.draw(TRANSCOLOR);
	infoSection.draw(TRANSCOLOR);

	infoFonts.setFontColor(graphicsNS::WHITE);

	//Enemy Information
	eHealthBar.draw(graphicsNS::RED);
	infoFonts.print(
		enemyChara.getHealthString(), 
		eHealthBar.getX() + HPBAR_WIDTH/2 - infoFonts.getWidth(enemyChara.getHealthString(),infoFonts.getFont()) / 2,
		eHealthBar.getY() + HPBAR_HEIGHT / 2 - infoFonts.getHeight(enemyChara.getHealthString(), infoFonts.getFont()) / 2
	);

	//MainCharacter Information
	healthBar.draw(graphicsNS::RED);
	infoFonts.print(
		mainChara.getHealthString(),
		healthBar.getX() + HPBAR_WIDTH / 2 - infoFonts.getWidth(mainChara.getHealthString(), infoFonts.getFont()) / 2,
		healthBar.getY() + HPBAR_HEIGHT /2 - infoFonts.getHeight(mainChara.getHealthString(), infoFonts.getFont()) / 2
	);
}

void PFantasy::intializeCharacters() {
	//initialize character textures
	if (!mainCharaTexture.initialize(graphics, MAINCHARA_IMAGE))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

	//initialize character objects
	if (!mainChara.getImagePtr()->initialize(graphics, 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error assigning main character image");
	mainChara.setValues("Hero", "Hero", 100);

	if (!enemyChara.getImagePtr()->initialize(graphics, 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error assigning enemy character image");
	enemyChara.setValues("Guy", "WoD", 100);

	//Set characters placement cooridinates
	mainChara.setScale(CHARA_SCALE, CHARA_SCALE);
	mainChara.setX(GAME_WIDTH * 0.75f - mainChara.getImagePtr()->getWidth()/2);
	mainChara.setY(GAME_HEIGHT * 0.5f - mainChara.getImagePtr()->getHeight()/3);

	enemyChara.setScale(CHARA_SCALE, CHARA_SCALE);
	enemyChara.setX(GAME_WIDTH * 0.25f - enemyChara.getImagePtr()->getWidth()/2);
	enemyChara.setY(GAME_HEIGHT * 0.5f - mainChara.getImagePtr()->getHeight()/3);
	enemyChara.getImagePtr()->flipHorizontal(true);

}

void PFantasy::renderCharacters() {
	mainChara.getImagePtr()->draw(TRANSCOLOR);
	enemyChara.getImagePtr()->draw(graphicsNS::ARED);
}