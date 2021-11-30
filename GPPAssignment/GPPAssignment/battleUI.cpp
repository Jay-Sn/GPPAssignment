#include "battleUI.h"

BattleUI::BattleUI() 
{
}

BattleUI::~BattleUI() {}

bool BattleUI::initialize(Game* gameptr, std::vector<Character> listOfCharacters) 
{
	listOfCharactersInPlay = listOfCharacters;


	if (!UITexture.initialize(gameptr->getGraphics(), PLACEHOLDERRECT))throw(gameErrorNS::FATAL_ERROR, "Error initiating placeholder rect");
	
	if (!actionBar.initialize(gameptr->getGraphics(), GAME_WIDTH, GAME_HEIGHT/4, 0, &UITexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize Health Bars"));

	actionBar.setY(GAME_HEIGHT - actionBar.getHeight());

	setHpPosYEnemy();
	setHpPosYTeam();

	healthBarSetup(gameptr,listOfCharacters);
}

//Setting up health bars
void BattleUI::healthBarSetup(Game* gameptr, std::vector<Character> listOfCharacters)
{
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

		usedHealthBar[i] = listOfHealth[i];
	}

}

void BattleUI::draw()
{
	actionBar.draw(graphicsNS::GRAY);
	for (int i = 0; i < usedHealthBar.size(); i++)
	{
		usedHealthBar[i].draw(graphicsNS::RED);
	}
}

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