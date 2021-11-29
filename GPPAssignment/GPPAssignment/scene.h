#ifndef _SCENE_H            // prevent multiple definitions if this 
#define _SCENE_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "input.h"
#include "game.h"

class Scene;

class Scene
{
public:
	Scene() {}
	~Scene() {}
	virtual void initialize() = 0;
	virtual void reset() = 0;
	virtual void update(float frameTime) = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};
#endif
