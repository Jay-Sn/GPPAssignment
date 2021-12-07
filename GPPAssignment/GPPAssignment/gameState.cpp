#include "gameState.h"

GameState::GameState()
{

}

GameState::~GameState()
{

}

float GameState::getFloatFromState(std::string key)
{
	return floatMap[key];
}

bool GameState::isFloatExist(std::string key)
{
	if (floatMap.count(key) == 0)
	{
		return false;
	}
	return true;
}

void GameState::setValueToState(std::string key, float var)
{
	floatMap[key] = var;
}

void GameState::resetState()
{
	floatMap.clear();
}