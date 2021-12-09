//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
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
	std::map<std::string, Var> globalMap; // global variables
public:
	GameState();
	~GameState();

	// Get the entire map
	std::map<std::string, Var> getMap();

	// Getter and check if map entry exist: globalMap

	// Template cannot be put in .cpp due to "inclusion model" rule
	template<typename  T> T getFloatFromState(std::string key)
	{
		if (globalMap[key].type == "float") // If float
		{
			return std::stof(globalMap[key].value);
		}
		return (globalMap[key].value);
	}
	bool isExistInState(std::string key);
	// Setter
	void setValueToState(std::string key, Var var);
	void setValueToState(std::string key, float value);
	// Clear map
	void resetState();
};

#endif 
