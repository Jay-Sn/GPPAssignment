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

//===================================================
// Gets the map
//===================================================
std::map<std::string, Var> GameState::getMap()
{
	return globalMap;
}

//===================================================
// Checks whether the element exist in the state
//===================================================
bool GameState::isExistInState(std::string key)
{
	// if globalMap.count(key) returns 0, it is false. If it returns 1,  it is true.
	if (globalMap.count(key) == 0)
	{
		return false;
	}
	return true;
}


//===========================================
// Sets the var into the state
//===========================================
void GameState::setValueToState(std::string key, Var var)
{
	globalMap[key] = var;
}

//===========================================
// Sets the float into the state
//===========================================
void GameState::setValueToState(std::string key, float value)
{
	Var var = { std::to_string(value), "float" };
	globalMap[key] = var;
}

//===========================================
// Clears the globalMap
//===========================================
void GameState::resetState()
{
	globalMap.clear();
}