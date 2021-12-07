//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
#include "gameState.h"

GameState::GameState()
{

}

GameState::~GameState()
{

}

float GameState::getFloatFromState(std::string key)
{
	return std::stof(globalMap[key].value);
}

bool GameState::isFloatExist(std::string key)
{
	if (globalMap.count(key) == 0)
	{
		return false;
	}
	return true;
}

void GameState::setValueToState(std::string key, float value)
{
	Var var = { std::to_string(value), "float" };
	globalMap[key] = var;
}

void GameState::resetState()
{
	globalMap.clear();
}