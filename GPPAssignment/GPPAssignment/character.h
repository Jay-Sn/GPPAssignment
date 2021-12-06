#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "image.h"
#include "texturemanager.h"
#include "constants.h"
#include "game.h"
#include "image.h"

class Character : public Image
{
protected:
	std::string charaName;
	std::string charaClass;

	bool friendlyTag;

	//Image of the Characters
	Image charaSprite;

	//Actual Health Variables
	float maxHealth;
	float currentHealth;

	//To store HealthString
	char hpbuffer[100];

public:

	Character();
	~Character();

	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM, std::string charaName, std::string charaClass, float maxHealth, bool friendly = false);

	void draw(COLOR_ARGB color = TRANSCOLOR);

	//Set Variables for the character
	void setValues(std::string charaName, std::string charaClass, float maxHealth, bool friendly);


	std::string getHealthString();
	Image* getImagePtr() { return &charaSprite; }

	float getX() {return getImagePtr()->getX();}
	void setX(float x) { return getImagePtr()->setX(x); }
	float getY() { return getImagePtr()->getY(); }
	void setY(float y) { return getImagePtr()->setY(y); }

	virtual void setScale(float scaleX, float scaleY) { getImagePtr()->setScaleX(scaleX); getImagePtr()->setScaleY(scaleY); }
	
	virtual float getScaleX() { return getImagePtr()->getScaleX(); }
	virtual void setScaleX(float scaleX) { getImagePtr()->setScaleX(scaleX); }

	virtual float getScaleY() { return getImagePtr()->getScaleY(); }
	virtual void setScaleY(float scaleY) { getImagePtr()->setScaleY(scaleY); }

	bool changeCharaSprite(Graphics* g, int width, int height, int ncols, TextureManager* textureM);

	double getCurrentHealth() { return currentHealth; }

	std::string getName() { return charaName; }
	std::string getClass() { return charaClass; }

	float getMaxHealth() { return maxHealth; }

	void setHealth(float newHealth) { maxHealth = newHealth; }
	void deductHealth(float health) { currentHealth -= health; }

	void setFriendlyTag(bool newBool) { friendlyTag = newBool; }
};
#endif // !_CHARACTER_H_
