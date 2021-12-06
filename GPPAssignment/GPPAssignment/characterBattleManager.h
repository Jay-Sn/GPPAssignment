#ifndef _CHARACTER_BATTLE_H_
#define _CHARACTER_BATTLE_H_
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "character.h"

class CharacterBattleManager
{
private:
	std::vector<Character> listOfCharacters;

public:
	CharacterBattleManager();
	~CharacterBattleManager();

	std::vector<Character>* getCharacterList() { return &listOfCharacters; }

	void initializeCharacters();


};
#endif // !_CHARACTER_BATTLE_H_