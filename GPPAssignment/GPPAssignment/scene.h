#ifndef _SCENE_H
#define _SCENE_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void initialize();
	void run();

	//Pure virtual function declarations
	//These functions MUST be written in any class that inherits from Game
	virtual void update() = 0;														//Update game items
	virtual void ai() = 0;															//Perform AI calculations
	virtual void collisions() = 0;													//Check for collisions
};
#endif