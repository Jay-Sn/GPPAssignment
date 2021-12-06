#include "SceneManager.h"

#include "StartingMenu.h"
#include "battleScene.h"
#include "overworld.h"
#include  "pauseMenu.h"

SceneManager::SceneManager()
{
    sceneMap["Title"] = new StartingMenu(this);
    sceneMap["Overworld"] = new Overworld(this);
    sceneMap["Battle"] = new BattleScene(this);
    sceneMap["PauseMenu"] = new PauseMenu(this);
}


SceneManager::~SceneManager()
{
	releaseAll();
}

void SceneManager::switchScene(std::string scene)
{
    currentScene = sceneMap[scene];
    currentScene->initialize();
}

void SceneManager::initialize(HWND hwnd)
{
    Game::initialize(hwnd);
    currentScene = sceneMap["Title"];
    currentScene->initialize();
}

void SceneManager::reset()
{
    currentScene->reset();
    return;
}

void SceneManager::update()
{
    currentScene->update(frameTime);
}

void SceneManager::ai()
{
    currentScene->ai();
}

void SceneManager::collisions()
{
    currentScene->collisions();
}

//=============================================================================
// render game items
//=============================================================================
void SceneManager::render()
{
    currentScene->render();
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void SceneManager::releaseAll()
{
    currentScene->releaseAll();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void SceneManager::resetAll()
{
    currentScene->resetAll();
    Game::resetAll();
    return;
}