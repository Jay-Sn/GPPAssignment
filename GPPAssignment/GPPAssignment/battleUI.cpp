#include "battleUI.h"

BattleUI::BattleUI() 
{
}

BattleUI::~BattleUI() {}

bool BattleUI::initialize(Game* gameptr, std::vector<Character>* listOfCharacters) 
{
	//Set List of Characters to be used in the Battle UI
	listOfCharactersInPlay = listOfCharacters;
	
	//Assign the characters to their own teams
	for (int i = 0; i < listOfCharactersInPlay->size(); i++)
	{
		if (listOfCharactersInPlay->at(i).getFriendlyTag()) friendlyTeam.push_back(listOfCharactersInPlay->at(i));

		else enemyTeam.push_back(listOfCharactersInPlay->at(i));

	}

	//Initialize Textures


	return true;
}

//Setting up health bars

//=========================================================
//				Draw function of BattleUI
//=========================================================
void BattleUI::draw()
{

}

//=========================================================
//		Set Up Y positions for HealthBars (Enemies)
//=========================================================
void BattleUI::setHpPosYEnemy()
{

}

//=========================================================
//		Set Up Y positions for HealthBars (Friendly)
//=========================================================
void BattleUI::setHpPosYTeam()
{

}

//=========================================================
//			Update Function for BattleUI
//=========================================================
void BattleUI::update(Game* gameptr)
{
	
}

//======================================================================
//		Use to check for updates and update health bars if nessasary
//======================================================================
bool BattleUI::updateHpBars(Character character, float frameTime)
{
	return true;

}