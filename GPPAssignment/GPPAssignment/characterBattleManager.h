#ifndef _CHARACTER_BATTLE_H_
#define _CHARACTER_BATTLE_H_
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "character.h"

struct positions
{
	float x;
	float y;
};

class CharacterBattleManager
{
private:
	std::vector<Character>* listOfCharacters;

	int enemycount, friendcount;

	std::vector<positions> friendlyPositions;
	std::vector<positions> enemyPositions;


public:
	CharacterBattleManager();
	~CharacterBattleManager();

	//std::vector<Character>* getCharacterList() { return &listOfCharacters; }

	//Get the list of characters that are being used in the battle.
	void initialize(std::vector<Character>* newList);

	// Draw function
	void draw();

};
#endif // !_CHARACTER_BATTLE_H_