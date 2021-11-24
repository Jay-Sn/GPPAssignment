#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "image.h"
#include "constants.h"

using namespace std;

class Character 
{
protected:
	string charaName;
	string charaClass;

	Image charaSprite;

	float maxHealth;
	float currentHealth;
	char hpbuffer[100];
public:

	Character();
	~Character();

	string getHealthString();
	bool initialize(Graphics* g, int width, int height, int ncols, TextureManager* textureM, string charaName, string charaClass, float maxHealth);
	void setValues(string charaName, string charaClass, float maxHealth);
	Image* getImagePtr() { return &charaSprite; }

	float getX() {return charaSprite.getX();}
	void setX(float x) { return charaSprite.setX(x); }
	float getY() { return charaSprite.getY(); }
	void setY(float y) { return charaSprite.setY(y); }

	virtual void setScale(float scaleX, float scaleY) { charaSprite.setScaleX(scaleX); charaSprite.setScaleY(scaleY); }
	
	virtual float getScaleX() { return charaSprite.getScaleX(); }
	virtual void setScaleX(float scaleX) { charaSprite.setScaleX(scaleX); }

	virtual float getScaleY() { return charaSprite.getScaleY(); }
	virtual void setScaleY(float scaleY) { charaSprite.setScaleY(scaleY); }

	bool changeCharaSprite(Graphics* g, int width, int height, int ncols, TextureManager* textureM);

	double getCurrentHealth() { return currentHealth; }

	string getName() { return charaName; }
	string getClass() { return charaClass; }

	float getMaxHealth() { return maxHealth; }
	void setHealth(float newHealth) { maxHealth = newHealth; }
	void deductHealth(float health) { currentHealth -= health; }

};
#endif // !_CHARACTER_H_
