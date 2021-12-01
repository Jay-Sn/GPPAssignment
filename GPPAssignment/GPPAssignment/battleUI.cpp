#include "battleUI.h"

BattleUI::BattleUI() 
{
}

BattleUI::~BattleUI() {}

bool BattleUI::initialize(Game* gameptr, std::vector<Character> listOfCharacters) 
{
	listOfCharactersInPlay = listOfCharacters;

	if (selectionFonts.initialize(gameptr->getGraphics(), 40, true, false, gameNS::INFOFONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	selectionFonts.setFontColor(graphicsNS::BLACK);

	if (!UITexture.initialize(gameptr->getGraphics(), PLACEHOLDERRECT))throw(gameErrorNS::FATAL_ERROR, "Error initiating placeholder rect");
	
	if (!SelectionArrowTexture.initialize(gameptr->getGraphics(), Cursor))throw(gameErrorNS::FATAL_ERROR, "Error initiating SelectionArrowTexture");
	
	if (!actionBar.initialize(gameptr->getGraphics(), GAME_WIDTH, GAME_HEIGHT/4, 0, &UITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Health Bars"));
	if (!selectionArrow.initialize(gameptr->getGraphics(), 0, 0, 0, &SelectionArrowTexture))throw(gameErrorNS::FATAL_ERROR, "Error initiating Main actionBarinfoSection");

	actionBar.setY(GAME_HEIGHT - actionBar.getHeight());

	selectionArrow.setY(yValues[0] + selectionArrow.getHeight()/2);
	selectionArrow.setX(actionBar.getCenterX() - selectionFonts.getWidth("Fight", selectionFonts.getFont()));

	setHpPosYEnemy();
	setHpPosYTeam();

	selectionArrow.getCenterX() - selectionFonts.getWidth("Fight", selectionFonts.getFont());

	healthBarSetup(gameptr,listOfCharacters);
}

//Setting up health bars
void BattleUI::healthBarSetup(Game* gameptr, std::vector<Character> listOfCharacters)
{
	//Index for rendering the respective healthbar at the right positions
	int teamIndex = 0;
	int enemyIndex = 0;

	for (int i = 0; i < listOfCharacters.size(); i++)
	{
		if (!listOfHealth[i].initialize(gameptr->getGraphics(), HPBAR_WIDTH, HPBAR_HEIGHT, 0, &UITexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Health Bars"));

		if (listOfCharacters[i].getClass() == "WoD")
		{
			listOfHealth[i].setX(ENEMYSECTION - HPBAR_WIDTH / 2);
			listOfHealth[i].setY(enemyHpPosY[enemyIndex]);
			enemyIndex += 1;
		}

		else
		{
			listOfHealth[i].setX(TEAMSECTION - HPBAR_WIDTH / 2);
			listOfHealth[i].setY(teamHpPosY[teamIndex]);
			teamIndex += 1;

		}

		usedHealthBar[listOfCharacters[i].getName()] = listOfHealth[i];
	}

}

//=========================================================
//				Draw function of BattleUI
//=========================================================
void BattleUI::draw()
{
	actionBar.draw(graphicsNS::GRAY);
	for (int i = 0; i < usedHealthBar.size(); i++)
	{
		usedHealthBar[listOfCharactersInPlay[i].getName()].draw(graphicsNS::RED);
	}
	selectionArrow.draw(TRANSCOLOR);
	selectionFonts.print("Attack", actionBar.getCenterX() - selectionFonts.getWidth("Fight", selectionFonts.getFont()) / 2, actionBar.getCenterY() - selectionFonts.getHeight("Fight", selectionFonts.getFont()) * 1.5 - 10);
	selectionFonts.print("Block", actionBar.getCenterX() - selectionFonts.getWidth("Block", selectionFonts.getFont()) / 2, actionBar.getCenterY() - selectionFonts.getHeight("Block", selectionFonts.getFont()) / 2);
	selectionFonts.print("Run", actionBar.getCenterX() - selectionFonts.getWidth("Fight", selectionFonts.getFont()) / 2, actionBar.getCenterY() + selectionFonts.getHeight("Run", selectionFonts.getFont()) * 0.5 + 10);

}

//=========================================================
//		Set Up Y positions for HealthBars (Enemies)
//=========================================================
void BattleUI::setHpPosYEnemy()
{
	int numberOfEnemies = 0;
	for (int i = 0; i < listOfCharactersInPlay.size(); i++)
	{
		if (listOfCharactersInPlay[i].getClass() == "WoD")numberOfEnemies += 1;
	}

	for (int i = 0; i < numberOfEnemies; i++)
	{
		enemyHpPosY.push_back(actionBar.getY() + (i + 1) * (actionBar.getHeight()/(numberOfEnemies + 1) - HPBAR_HEIGHT / 2 + OFFSET * (i)) );
	}
}

//=========================================================
//		Set Up Y positions for HealthBars (Friendly)
//=========================================================
void BattleUI::setHpPosYTeam()
{
	int numberOfTeam = 0;
	for (int i = 0; i < listOfCharactersInPlay.size(); i++)
	{
		if(!(listOfCharactersInPlay[i].getClass() == "WoD"))numberOfTeam += 1;
	}

	for (int i = 0; i < numberOfTeam; i++)
	{
		teamHpPosY.push_back(actionBar.getY() + (i + 1) * (actionBar.getHeight() / (numberOfTeam + 1) - HPBAR_HEIGHT / 2 + OFFSET * (i) ) );
	}
}

//=========================================================
//			Update Function for BattleUI
//=========================================================
void BattleUI::update(Game* gameptr)
{
	
	if (gameptr->getInput()->wasKeyPressed(CURSOR_DOWN_KEY) && selectionY + 1 < 3)               // if move up
	{
		selectionY += 1;
		selectionArrow.setY(yValues[selectionY] + selectionArrow.getHeight() / 2);
	}
	if (gameptr->getInput()->wasKeyPressed(CURSOR_UP_KEY) && selectionY - 1 >= 0)               // if move up
	{
		selectionY -= 1;
		selectionArrow.setY(yValues[selectionY] + selectionArrow.getHeight() / 2);

	}
}

//======================================================================
//		Use to check for updates and update health bars if nessasary
//======================================================================
bool BattleUI::updateHpBars(Character character, float frameTime)
{
	//By default it will be set to done.
	animationDone = true;

	if (usedHealthBar[character.getName()].test() != round(character.getCurrentHealth() / character.getMaxHealth() * 100) ) {
		if (usedHealthBar[character.getName()].getScaleX() > 0) animationDone = false;
	}

	//For decrease in health
	if (character.getCurrentHealth() <= 0 && usedHealthBar[character.getName()].getScaleX() >= 0)
		usedHealthBar[character.getName()].setScaleX(usedHealthBar[character.getName()].getScaleX() - 0.1 * frameTime);
	else if (character.getCurrentHealth() >= 0 && usedHealthBar[character.getName()].getScaleX() >= (character.getCurrentHealth() / character.getMaxHealth())) {
		usedHealthBar[character.getName()].setScaleX(usedHealthBar[character.getName()].getScaleX() - 0.1 * frameTime);
	}

	//For Increase in Health
	if (character.getCurrentHealth() >= character.getMaxHealth() && usedHealthBar[character.getName()].getScaleX() <= 1) {
		usedHealthBar[character.getName()].setScaleX(usedHealthBar[character.getName()].getScaleX() + 0.1 * frameTime);
	}
	else if (character.getCurrentHealth() <= character.getMaxHealth() && usedHealthBar[character.getName()].getScaleX() <= character.getCurrentHealth() / character.getMaxHealth()) {
		usedHealthBar[character.getName()].setScaleX(usedHealthBar[character.getName()].getScaleX() + 0.1 * frameTime);
	}

	return animationDone;
}