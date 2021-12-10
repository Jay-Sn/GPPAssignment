//===========================================================================================
//	Module		: Game Programming
//	Assignment	: Placeholder Fantasy?	
//	Name		: Jason Teo Jun Hao
//	S/N			: S10194978
//	Description	: This header file is for the creation of character objects that are used
//				  throughout the game. Both the enemies and friendlys use the same object
//				  and are differentiated by the friendly tag. They also handle the containing
//				  of the health and can allow for change in sprites.
//===========================================================================================

#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#define WIN32_LEAN_AND_MEAN

#include <string>
#include "image.h"
#include "texturemanager.h"
#include "constants.h"
#include "game.h"
#include "image.h"

namespace characterNS
{
	enum COLLISION_TYPE { NONE, CIRCLE, BOX, ROTATED_BOX };
}
class Character : public Image
{
protected:
	std::string charaName;					// Name of the Character
	std::string charaClass;					// Class of the Character

	bool friendlyTag;						// To Check for Friendly

	//Image of the Characters
	Image charaSprite;						// Sprite of the Character

	//Actual Health Variables
	float maxHealth;
	float currentHealth;

	char hpbuffer[100];						// Used to generate health string for UI

	//=========================================================================
	//							Collision Variables
	//=========================================================================

	characterNS::COLLISION_TYPE collisionType;

	VECTOR2 center;
	float radius;

	VECTOR2 distSquared;
	float sumRadiiSquared;

	RECT edge;
	VECTOR2 corners[4];
	VECTOR2 edge01, edge03;
	float edge01Min, edge01Max, edge03Min, edge03Max;

	VECTOR2 velocity;
	VECTOR2 deltaV;

	float rr;
	HRESULT hr;
	bool active;
	bool collision;
	bool rotatedBoxReady;

	// --- The following functions are protected because they are not intended to be
	// --- called from outside the class.
	// Circular collision detection 
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	//virtual bool collideCircle(Character& ent, VECTOR2& collisionVector);
	// Axis aligned box collision detection
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	virtual bool collideBox(Character& ent, VECTOR2& collisionVector);
	// Separating axis collision detection between boxes
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	virtual bool collideRotatedBox(Character& ent, VECTOR2& collisionVector);
	// Separating axis collision detection between box and circle
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	//svirtual bool collideRotatedBoxCircle(Character& ent, VECTOR2& collisionVector);
	// Separating axis collision detection helper functions
	void computeRotatedBox();
	bool projectionsOverlap(Character& ent);
	//bool collideCornerCircle(VECTOR2 corner, Character& ent, VECTOR2& collisionVector);

public:
	
	// Constructor
	Character();

	// Destructor
	virtual ~Character();

	// Initialize Character Object
	bool initialize(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM, std::string charaName, std::string charaClass, float maxHealth = 100, bool friendly = false);

	// Override parent draw | By default set color to TRANSCOLOR
	void draw(COLOR_ARGB color = TRANSCOLOR);

	// Set Variables for the Character
	void setValues(std::string charaName, std::string charaClass, float maxHealth, bool friendly);

	// Generate string for Health
	std::string getHealthString();

	// Get the Image pointer to edit or access data
	Image* getImagePtr() { return &charaSprite; }

	// Get and set the X value of the Character
	float getX() {return getImagePtr()->getX();}
	void setX(float x) { return getImagePtr()->setX(x); }

	// Get and set the Y value of the Character
	float getY() { return getImagePtr()->getY(); }
	void setY(float y) { return getImagePtr()->setY(y); }

	int getWidth() { return getImagePtr()->getWidth(); }
	int getHeight() { return getImagePtr()->getHeight(); }

	// Get Center of Character
	const VECTOR2* getCenter()
	{
		center = VECTOR2(getCenterX(), getCenterY());
		return &center;
	}

	// Set the Scale of the Character
	void setScale(float scaleX, float scaleY) { getImagePtr()->setScaleX(scaleX); getImagePtr()->setScaleY(scaleY); }
	void setScale(float scale) { getImagePtr()->setScaleX(scale); getImagePtr()->setScaleY(scale); }

	// Get and Set the Scale of the Character for the X axis
	float getScaleX() { return getImagePtr()->getScaleX(); }
	void setScaleX(float scaleX) { getImagePtr()->setScaleX(scaleX); }

	// Get and Set the Scale of the Character for the Y axis
	float getScaleY() { return getImagePtr()->getScaleY(); }
	void setScaleY(float scaleY) { getImagePtr()->setScaleY(scaleY); }

	// Change the Character's sprite
	bool changeCharaSprite(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM);

	// Get the current Health of the character
	double getCurrentHealth() { return currentHealth; }

	// Get the name and class of the character
	std::string getName() { return charaName; }
	std::string getClass() { return charaClass; }

	// Get and set Max Health
	float getMaxHealth() { return maxHealth; }
	void setMaxHealth(float newHealth) { maxHealth = newHealth; }

	// Deduct Current Health | Used during battle
	void deductHealth(float health) { currentHealth -= health; }

	// Set the friendly tag manually
	void setFriendlyTag(bool newBool) { friendlyTag = newBool; }
	bool getFriendlyTag() { return friendlyTag; }

	//=========================================================================
	//							Collision Section
	//=========================================================================

	float getRadius() const { return radius; }

	const RECT& getEdge() const { return edge; }

	const VECTOR2* getCorner(UINT c) const
	{
		if (c >= 4) c = 0;
		return &corners[c];
	}

	const VECTOR2 getVelocity() const { return velocity; }

	bool getActive() const { return active; };

	characterNS::COLLISION_TYPE getCollisionType() { return collisionType; }

	virtual void  setVelocity(VECTOR2 v) { velocity = v; }

	//Set Functions
	// Set delta velocity. Added to velocity in update().
	virtual void  setDeltaV(VECTOR2 dv) { deltaV = dv; }

	// Set active.
	virtual void  setActive(bool a) { active = a; }

	// Set radius of collision circle.
	virtual void setCollisionRadius(float r) { radius = r; }

	bool collidesWith(Character& ent, VECTOR2& collisionVector);

	void activate();
};
#endif // !_CHARACTER_H_
