//============================================================================
//  Module:             Gameplay Programming
//  Assignment 1:       PlaceHolder Fantasy?
//  Student Name:       William Wibisana Dumanauw
//  Student Number:     S10195561A
//============================================================================
#ifndef _SCENEMANAGER_H             // prevent multiple definitions if this 
#define _SCENEMANAGER_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <map>
#include <vector>
#include "game.h"
#include "scene.h"
#include "gameState.h"

class SceneManager: public Game
{
protected:
	Scene* currentScene;						// The scene the game is currently on
	GameState currentState;						// The state the game has, keeps data that is a global variable
	std::vector<Character> characterList;		// The list of characters
	std::map<std::string, Scene*> sceneMap;     // Map of scenes, used to switch scenes and keep scenes
	 
public:
	SceneManager();
	~SceneManager();

	// Switching Scene
	void switchScene(std::string scene);

	// When the character list is needed when switching scene
	void switchScene(std::string scene, std::vector<Character> characterList);

	void initialize(HWND hwnd);

	void reset();
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

	std::vector<Character>* getCharacterList() { return currentScene->getCharacterList(); }
	// Gets the game state
	GameState* getState() { return &currentState;  }
};
#endif
