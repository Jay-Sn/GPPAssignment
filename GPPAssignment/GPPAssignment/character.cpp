#include "character.h"

Character::Character(): charaSprite() {
	//By default no health
	currentHealth = 0;
	maxHealth = 0;

	//Enemy as default
	friendlyTag = false;
}

Character::~Character() {

}

//To Initialize Characters for Battle.
bool Character::initialize(
	Game* gamePtr, 
	int width, 
	int height, 
	int ncols, 
	TextureManager* textureM, 
	std::string newCharaName, 
	std::string newCharaClass, 
	float newMaxHealth, 
	bool friendly)
{
	charaSprite.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	charaName = newCharaName;
	charaClass = newCharaClass;
	friendlyTag = friendly;
	maxHealth = newMaxHealth;

	return true;
}

void Character::draw(COLOR_ARGB color)
{
		charaSprite.draw(color);
}

void Character::setValues(std::string CharaName, std::string CharaClass, float MaxHealth, bool friendly) {
		charaName = CharaName;
		charaClass = CharaClass;
		maxHealth = MaxHealth;
		currentHealth = maxHealth;
}

bool Character::changeCharaSprite(Graphics* g, int width, int height, int ncols, TextureManager* textureM) {
	//return getCharaImage().initialize(g, width, height, ncols, textureM);
	return true;
}

std::string Character::getHealthString() {
	sprintf_s(hpbuffer, 20, "%d / %d", (int)currentHealth, (int)maxHealth);
	return hpbuffer;
}
