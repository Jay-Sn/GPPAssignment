//===============================================================================================
//	Module		: Game Programming
//	Assignment	: Placeholder Fantasy?	
//	Author		: Jason Teo Jun Hao
//	Student ID	: S10194978B
//	Description	: This is the Character Object cpp that is used to initialize Character objects
//				  and will be referenced to get data about the current character. This includes
//				  and animations and movement
//===============================================================================================


#include "character.h"

Character::Character(): charaSprite() {
	//By default no health
	currentHealth = 0;
	maxHealth = 0;

	//Enemy as default
	friendlyTag = false;

    radius = 1.0;
    edge.left = -1;
    edge.top = -1;
    edge.right = 1;
    edge.bottom = 1;

    velocity.x = 0.0;
    velocity.y = 0.0;
    deltaV.x = 0.0;
    deltaV.y = 0.0;
    active = false;                  // the entity is active
    rotatedBoxReady = false;
    collisionType = characterNS::BOX;

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
    currentHealth = maxHealth;

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

bool Character::changeCharaSprite(Game* gamePtr, int width, int height, int ncols, TextureManager* textureM) {

    charaSprite.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	return true;
}

std::string Character::getHealthString() {
	sprintf_s(hpbuffer, 20, "%d / %d", (int)currentHealth, (int)maxHealth);
	return hpbuffer;
}

bool Character::collidesWith(Character& ent, VECTOR2& collisionVector)
{
    // if either entity is not active then no collision may occcur
    if (!active || !ent.getActive())
        return false;

    // If both entities are BOX collision
    if (collisionType == characterNS::BOX && ent.getCollisionType() == characterNS::BOX)
        return collideBox(ent, collisionVector);

    return false;
}

//=============================================================================
// Axis aligned bounding box collision detection method
// Called by collision()
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Character::collideBox(Character& ent, VECTOR2& collisionVector)
{
    // if either entity is not active then no collision may occcur
    if (!active || !ent.getActive())
        return false;

    float test = getY() + getImagePtr()->getHeight();
    float test2 = ent.getY();

    // Check for collision using Axis Aligned Bounding Box.
    if ((getX() > ent.getX() + ent.getImagePtr()->getWidth()) ||
        (getX() + getImagePtr()->getWidth() < ent.getX()) ||
        (getY() + getImagePtr()->getHeight() < ent.getY()) ||
        (getY() > ent.getY() + ent.getImagePtr()->getHeight()))
    {
        return false;
    }

    // set collision vector
    collisionVector = *ent.getCenter() - *getCenter();

    return true;
}

bool Character::collideRotatedBox(Character& ent, VECTOR2& collisionVector)
{
    computeRotatedBox();                    // prepare rotated box
    ent.computeRotatedBox();                // prepare rotated box
    if (projectionsOverlap(ent) && ent.projectionsOverlap(*this))
    {
        // set collision vector
        collisionVector = *ent.getCenter() - *getCenter();
        return true;
    }
    return false;
}

//=============================================================================
// Projects other box onto this edge01 and edge03.
// Called by collideRotatedBox()
// Post: returns true if projections overlap, false otherwise
//=============================================================================
bool Character::projectionsOverlap(Character& ent)
{
    float projection, min01, max01, min03, max03;

    // project other box onto edge01
    projection = graphics->Vector2Dot(&edge01, ent.getCorner(0)); // project corner 0
    min01 = projection;
    max01 = projection;
    // for each remaining corner
    for (int c = 1; c < 4; c++)
    {
        // project corner onto edge01
        projection = graphics->Vector2Dot(&edge01, ent.getCorner(c));
        if (projection < min01)
            min01 = projection;
        else if (projection > max01)
            max01 = projection;
    }
    if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
        return false;                       // no collision is possible

    // project other box onto edge03
    projection = graphics->Vector2Dot(&edge03, ent.getCorner(0)); // project corner 0
    min03 = projection;
    max03 = projection;
    // for each remaining corner
    for (int c = 1; c < 4; c++)
    {
        // project corner onto edge03
        projection = graphics->Vector2Dot(&edge03, ent.getCorner(c));
        if (projection < min03)
            min03 = projection;
        else if (projection > max03)
            max03 = projection;
    }
    if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
        return false;                       // no collision is possible

    return true;                            // projections overlap
}

//=============================================================================
// Compute corners of rotated box, projection edges and min and max projections
// 0---1  corner numbers
// |   |
// 3---2
//=============================================================================
void Character::computeRotatedBox()
{
    if (rotatedBoxReady)
        return;
    float projection;

    VECTOR2 rotatedX(cos(spriteData.angle), sin(spriteData.angle));
    VECTOR2 rotatedY(-sin(spriteData.angle), cos(spriteData.angle));

    const VECTOR2* center = getCenter();
    corners[0] = *center + rotatedX * ((float)edge.left * getScaleX()) +
        rotatedY * ((float)edge.top * getScaleY());
    corners[1] = *center + rotatedX * ((float)edge.right * getScaleX()) +
        rotatedY * ((float)edge.top * getScaleY());
    corners[2] = *center + rotatedX * ((float)edge.right * getScaleX()) +
        rotatedY * ((float)edge.bottom * getScaleY());
    corners[3] = *center + rotatedX * ((float)edge.left * getScaleX()) +
        rotatedY * ((float)edge.bottom * getScaleY());

    // corners[0] is used as origin
    // The two edges connected to corners[0] are used as the projection lines
    edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
    graphics->Vector2Normalize(&edge01);
    edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
    graphics->Vector2Normalize(&edge03);

    // this entities min and max projection onto edges
    projection = graphics->Vector2Dot(&edge01, &corners[0]);
    edge01Min = projection;
    edge01Max = projection;
    // project onto edge01
    projection = graphics->Vector2Dot(&edge01, &corners[1]);
    if (projection < edge01Min)
        edge01Min = projection;
    else if (projection > edge01Max)
        edge01Max = projection;
    // project onto edge03
    projection = graphics->Vector2Dot(&edge03, &corners[0]);
    edge03Min = projection;
    edge03Max = projection;
    projection = graphics->Vector2Dot(&edge03, &corners[3]);
    if (projection < edge03Min)
        edge03Min = projection;
    else if (projection > edge03Max)
        edge03Max = projection;

    rotatedBoxReady = true;
}

