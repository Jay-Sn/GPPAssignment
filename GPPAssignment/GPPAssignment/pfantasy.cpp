#include "pfantasy.h"
#include <time.h>


using namespace std;
PFantasy::PFantasy(SceneManager* manager) {
	dxManager = manager;
	selectionY = 0;
	attackPhase = 1;
}

PFantasy::~PFantasy()
{
	releaseAll();			//call onLostDevice() for every dxManager->getGraphics() item

}

//Initialize the game
void PFantasy::initialize()
{
	srand(time(NULL));
	intializeUI();
	intializeCharacters();
	reset();
	return;
}

// Reset
void PFantasy::reset()
{
	return;
}

//Update all game items
void PFantasy::update(float frameTime) {
	
	updateHealth(frameTime);
	if (attackPhase == 1) {
		checkMouse();
	}
	else {
		enemyAction();
	}
}

void PFantasy::updateHealth(float frameTime) {
	//Player Health
	if (healthBar.test() == round(mainChara.getCurrentHealth() / mainChara.getMaxHealth() * 100) && eHealthBar.test() == round(enemyChara.getCurrentHealth() / enemyChara.getMaxHealth() * 100)) {
		animationDone = true;
	}
	//else if ((mainChara.getCurrentHealth()<0 && healthBar.test() == 0) || (enemyChara.getCurrentHealth() < 0 && eHealthBar.test() == 0)) {
	//	//End Game Here
	//	animationDone = true;
	//}
	else {
		animationDone = false;
	}

	if (mainChara.getCurrentHealth() <= 0 && healthBar.getScaleX() >= 0)
		healthBar.setScaleX(healthBar.getScaleX() - 0.1 * frameTime);
	else if (mainChara.getCurrentHealth() >= 0 && healthBar.getScaleX() >= (mainChara.getCurrentHealth() / mainChara.getMaxHealth())) {
		healthBar.setScaleX(healthBar.getScaleX() - 0.1 * frameTime);
	}

	if (mainChara.getCurrentHealth() >= mainChara.getMaxHealth() && healthBar.getScaleX() <= 1) {
		healthBar.setScaleX(healthBar.getScaleX() + 0.1 * frameTime);
	}
	else if (mainChara.getCurrentHealth() <= mainChara.getMaxHealth() && healthBar.getScaleX() <= mainChara.getCurrentHealth() / mainChara.getMaxHealth()) {
		healthBar.setScaleX(healthBar.getScaleX() + 0.1 * frameTime);
	}

	//Enemy Health
	if (enemyChara.getCurrentHealth() <= 0 && eHealthBar.getScaleX() > 0)
		eHealthBar.setScaleX(eHealthBar.getScaleX() - 0.1 * frameTime);
	else if (enemyChara.getCurrentHealth() >= 0 && eHealthBar.getScaleX() >= (enemyChara.getCurrentHealth() / enemyChara.getMaxHealth())) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() - 0.1 * frameTime);
	}

	if (enemyChara.getCurrentHealth() >= enemyChara.getMaxHealth() && eHealthBar.getScaleX() <= 1) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() + 0.1 * frameTime);
	}
	else if (enemyChara.getCurrentHealth() <= enemyChara.getMaxHealth() && eHealthBar.getScaleX() <= enemyChara.getCurrentHealth() / enemyChara.getMaxHealth()) {
		eHealthBar.setScaleX(eHealthBar.getScaleX() + 0.1 * frameTime);
	}
}

void PFantasy::deductHealth(bool enemy, float hp) {
	if (enemy) {
		enemyChara.deductHealth(hp);
	}
	else {
		mainChara.deductHealth(hp);
	}
	animationDone = false;
}

//Artificial Intelligence
void PFantasy::ai() {}

//Phase alternator
void PFantasy::changePhase() {
	attackPhase *= -1;
}

void PFantasy::enemyAction() {
	//if not blocked
	if (attackPhase == -1 && animationDone) {
		deductHealth(false, rand() % 50 + 1);
		changePhase();
	}
}

//Handle collisions
void PFantasy::collisions() {}

void PFantasy::checkMouse() {
	if (dxManager->getInput()->wasKeyPressed(VK_RETURN) && attackPhase == 1)
	{
		if (animationDone) {
			if (selectionBlock.getY() == yValues[0]) {
				deductHealth(true, rand() % 50 + 1);
			}
			else if (selectionBlock.getY() == yValues[1]) {
				//prevent dmg
			}
			else if (selectionBlock.getY() == yValues[2]) {
				dxManager->switchScene("Menu");
			}

			changePhase();
		}
	}

	if (dxManager->getInput()->wasKeyPressed(CURSOR_DOWN_KEY) && selectionY + 1<3)               // if move up
	{
		selectionY += 1;
		selectionBlock.setY(yValues[selectionY]);
	}
	if (dxManager->getInput()->wasKeyPressed(CURSOR_UP_KEY) && selectionY -1 >=0)               // if move up
	{
		selectionY -= 1;
		selectionBlock.setY(yValues[selectionY]);
		
	}
}

//Render game items
void PFantasy::render() {
	dxManager->getGraphics()->spriteBegin();

	floor.draw(BACKGROUNDCOLOUR);

	renderCharacters();
	renderUI();
	selectionFonts.print("Attack", abilitySection.getCenterX() - selectionFonts.getWidth("Fight", selectionFonts.getFont())/2, abilitySection.getCenterY() - selectionFonts.getHeight("Fight",selectionFonts.getFont()) * 1.5 - 10);
	selectionFonts.print("Block", abilitySection.getCenterX() - selectionFonts.getWidth("Block", selectionFonts.getFont()) / 2, abilitySection.getCenterY() - selectionFonts.getHeight("Block", selectionFonts.getFont()) /2);
	selectionFonts.print("Run", abilitySection.getCenterX() - selectionFonts.getWidth("Fight", selectionFonts.getFont()) / 2, abilitySection.getCenterY() + selectionFonts.getHeight("Run", selectionFonts.getFont()) * 0.5 + 10);
	dxManager->getGraphics()->spriteEnd();
}

int properCast(float fukingNumber) {
	return 1;
}

//The dxManager->getGraphics() device was lost
//Release all reserved video memory to be resetted
void PFantasy::releaseAll() {
	mainCharaTexture.onLostDevice();
	placeholderRectTexture.onLostDevice();
	return;
}

//The dxManager->getGraphics() device has been reset.
//Recreate all reserved video memory to reset dxManager->getGraphics() device
void PFantasy::resetAll() {
	mainCharaTexture.onResetDevice();
	placeholderRectTexture.onResetDevice();
	return;
}

void PFantasy::intializeUI() {

	if (hpFonts.initialize(dxManager->getGraphics(), 10, true, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	if (infoFonts.initialize(dxManager->getGraphics(), 30, false, false, gameNS::INFOFONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	if (selectionFonts.initialize(dxManager->getGraphics(), 40, true, false, gameNS::INFOFONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	if (!placeholderRectTexture.initialize(dxManager->getGraphics(), PLACEHOLDERRECT))throw(gameErrorNS::FATAL_ERROR, "Error initiating placeholder rect");
	if (!floor.initialize(dxManager->getGraphics(), 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");

	//CharacterInformation UI
	if (!healthBar.initialize(dxManager->getGraphics(), HPBAR_WIDTH, HPBAR_HEIGHT, 1, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating healthBar");
	if (!eHealthBar.initialize(dxManager->getGraphics(), HPBAR_WIDTH, HPBAR_HEIGHT, 1, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating eHealthBar");

	//Quad UI
	if (!enemyNameSection.initialize(dxManager->getGraphics(), 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating enemyNameSection");
	if (!abilitySection.initialize(dxManager->getGraphics(), 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating abilitySection");
	if (!infoSection.initialize(dxManager->getGraphics(), 0, 0, 0, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");

	if (!selectionBlock.initialize(dxManager->getGraphics(), 10, 10, 6, &placeholderRectTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main infoSection");
	
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
	healthBar.setScale(1, 1);
	healthBar.setX(infoSection.getX() + 0.0625 * infoSection.getWidth());
	healthBar.setY(infoSection.getY() + 0.25 * infoSection.getHeight());

	eHealthBar.setCurrentFrame(1);
	eHealthBar.setScale(1, 1);
	eHealthBar.setX(enemyNameSection.getX() + 0.125 * enemyNameSection.getWidth());
	eHealthBar.setY(enemyNameSection.getY() + 0.25 * enemyNameSection.getHeight());

	selectionBlock.setCurrentFrame(4);
	selectionBlock.setX(abilitySection.getX() +50);
	selectionBlock.setY(yValues[0]);
}

void PFantasy::renderUI() {

	//Section Draw
	enemyNameSection.draw(TRANSCOLOR);
	abilitySection.draw(TRANSCOLOR);
	infoSection.draw(TRANSCOLOR);

	infoFonts.setFontColor(graphicsNS::WHITE);

	//Enemy Information
	eHealthBar.draw(graphicsNS::RED);
	hpFonts.print(
		enemyChara.getHealthString(), 
		eHealthBar.getX() + HPBAR_WIDTH/2 - hpFonts.getWidth(enemyChara.getHealthString(), hpFonts.getFont()) / 2,
		eHealthBar.getY() + HPBAR_HEIGHT / 2 - hpFonts.getHeight(enemyChara.getHealthString(), hpFonts.getFont()) / 2
	);

	infoFonts.print(
		enemyChara.getName(),
		eHealthBar.getX(),
		eHealthBar.getY() - HPBAR_HEIGHT - infoFonts.getHeight(enemyChara.getName(), infoFonts.getFont())/2
	);

	infoFonts.print(
		enemyChara.getClass(),
		eHealthBar.getX() + HPBAR_WIDTH/2 - infoFonts.getWidth(enemyChara.getClass(), infoFonts.getFont()),
		eHealthBar.getY() - HPBAR_HEIGHT - infoFonts.getHeight(enemyChara.getClass(), infoFonts.getFont()) / 2
	);

	//MainCharacter Information
	healthBar.draw(graphicsNS::RED);
	hpFonts.print(
		mainChara.getHealthString(),
		healthBar.getX() + HPBAR_WIDTH / 2 - hpFonts.getWidth(mainChara.getHealthString(), hpFonts.getFont()) / 2,
		healthBar.getY() + HPBAR_HEIGHT /2 - hpFonts.getHeight(mainChara.getHealthString(), hpFonts.getFont()) / 2
	);

	infoFonts.print(
		mainChara.getName(),
		GAME_WIDTH - ((GAME_WIDTH - healthBar.getX() - HPBAR_WIDTH) / 4),
		healthBar.getY() - infoFonts.getHeight(mainChara.getName(),infoFonts.getFont())/2 + HPBAR_HEIGHT / 2
	);

	infoFonts.print(
		mainChara.getClass(),
		GAME_WIDTH - ((GAME_WIDTH - healthBar.getX() - HPBAR_WIDTH) / 4 * 3),
		healthBar.getY() - infoFonts.getHeight(mainChara.getClass(), infoFonts.getFont()) / 2 + HPBAR_HEIGHT / 2
	);
	selectionBlock.draw(graphicsNS::GREEN);
}

void PFantasy::intializeCharacters() {

	//initialize character textures
	if (!mainCharaTexture.initialize(dxManager->getGraphics(), MAINCHARA_IMAGE))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main Character");

	//initialize character objects
	if (!mainChara.getImagePtr()->initialize(dxManager->getGraphics(), 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error assigning main character image");
	mainChara.setValues("Ayame", "Hero", 100);

	if (!enemyChara.getImagePtr()->initialize(dxManager->getGraphics(), 0, 0, 0, &mainCharaTexture))throw(gameErrorNS::FATAL_ERROR, "Error assigning enemy character image");
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