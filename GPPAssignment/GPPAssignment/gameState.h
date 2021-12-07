#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#define WIN32_LEAN_AND_MEAN

#include <map>
#include <string>
#include <iostream>

class GameState
{
private:
	std::map<std::string, float> floatMap;
public:
	GameState();
	~GameState();

	float getFloatFromState(std::string key);
	bool isFloatExist(std::string key);
	void setValueToState(std::string key, float var);
	void resetState();
};

#endif 
