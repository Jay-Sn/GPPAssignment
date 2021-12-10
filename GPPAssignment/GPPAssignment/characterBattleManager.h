//===========================================================================================
//	Module		: Game Programming
//	Assignment	: Placeholder Fantasy?	
//	Name		: Jason Teo Jun Hao
//	S/N			: S10194978
//	Description	: This header file is for the displaying of the different characters in the
//				  enemy team and the friendly teams. In the future this will also handle the
//				  animations, but as for now, this will just be used to draw the characters.
//===========================================================================================

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

	//Get the list of characters that are being used in the battle.
	void initialize(std::vector<Character>* newList);

	// Draw function
	void draw();

};
#endif // !_CHARACTER_BATTLE_H_