#include "character.h"

Character::Character(): charaSprite() {
	currentHealth = 0;
	maxHealth = 0;

}

Character::~Character() {

}

void Character::setValues(std::string CharaName, std::string CharaClass, float MaxHealth) {
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
