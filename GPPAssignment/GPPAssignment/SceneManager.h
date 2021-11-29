#ifndef _SCENEMANAGER_H             // prevent multiple definitions if this 
#define _SCENEMANAGER_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <map>
#include "game.h"
#include "constants.h"
#include "Scene.h"


class SceneManager: public Game
{
protected:
	Scene* currentScene;
	std::map<std::string, Scene*> sceneMap;

public:
	SceneManager();
	~SceneManager();
	void switchScene(std::string scene);
	void initialize(HWND hwnd);
	void reset();
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};
#endif
