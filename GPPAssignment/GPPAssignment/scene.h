//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
#ifndef _SCENE_H            // prevent multiple definitions if this 
#define _SCENE_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "graphics.h"
#include "input.h"
#include "game.h"
#include "character.h"

// ALL SCENES ARE A CHILD OF SCENE
class Scene;

class Scene
{
private:
	std::vector<Character> characterList;

public:
	Scene() {}
	~Scene() {}
	// Make sure all children of scene has these functions
	virtual void initialize() = 0;
	virtual void reset() = 0;
	virtual void update(float frameTime) = 0;
	virtual void ai() = 0;
	virtual void collisions() = 0;
	virtual void render() = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;

	void setCharacterList(std::vector<Character> newCharacterList) { characterList = newCharacterList; }
	std::vector<Character>* getCharacterList() { return &characterList; }

};
#endif
