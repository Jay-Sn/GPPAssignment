//============================================================================<<
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================<>
//  Description of GameState:
//  This is where the current state of the game is held. 
// The global map kept here is in charge of keeping the global variables such as
//		player coordinates.
//============================================================================>>
#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#define WIN32_LEAN_AND_MEAN

#include <map>
#include <string>
#include <iostream>

struct Var
{
	std::string value;
	std::string type;
};
// This is the game state, keep tracks of global variable.
class GameState
{
private:
	std::map<std::string, Var> globalMap; // global map for keeping global variables
public:
	GameState();
	~GameState();

	// Get the entire map
	std::map<std::string, Var> getMap();

	// Getter and check if map entry exist: globalMap

	// Template cannot be put in .cpp due to "inclusion model" rule
	float getFloatFromState(std::string key)
	{
		if (globalMap[key].type == "float") // If float
		{
			return std::stof(globalMap[key].value);
		}
	}
	bool isExistInState(std::string key);
	// Setter
	void setValueToState(std::string key, Var var);
	void setValueToState(std::string key, float value);
	// Clear map
	void resetState();
};

#endif 
