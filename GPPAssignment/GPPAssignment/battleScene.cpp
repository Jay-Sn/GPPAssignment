//===============================================================================================
//	Author:			Jason Teo Jun Hao
//	Student ID:		S10194978B
//	Description:	This is the battle scene that is accessed by encountering an enemy in the
//					overworld.
//===============================================================================================

#include <time.h>
#include "battleScene.h"

//Constructor
BattleScene::BattleScene(SceneManager* manager) {
	dxManager = manager;
	dxMenuText = new TextDX();
	selectionY = 0;
	attackPhase = 1;
}

//Destructor
BattleScene::~BattleScene()
{
	releaseAll();			//call onLostDevice() for every dxManager->getGraphics() item

}

//Initialize the Scene
void BattleScene::initialize()
{
	//Allow for the randomizer for the damage to be always different
	srand(time(NULL));

	//Assign the totalCharacterScenes to the BattleScene CharacterList
	characterList = dxManager->getCharacterList();

	//Initialize the BattleUI
	battleUI.initialize(dxManager, &characterList);

	return;
}

// Reset
void BattleScene::reset()
{
	return;
}

//Update all game items
void BattleScene::update(float frameTime) {

	//Call BattleUI Update to update the UI
	battleUI.update(dxManager);
	
	//Check for the animation status of the healthBars
	animationDone = battleUI.updateHpBars(checkCharacterHealth, frameTime);

}

//Artificial Intelligence
void BattleScene::ai() {}

//Handle collisions
void BattleScene::collisions() {}

//Render game items
void BattleScene::render() {
	dxManager->getGraphics()->spriteBegin();

	battleUI.draw();

	dxManager->getGraphics()->spriteEnd();
}

//The dxManager->getGraphics() device was lost
//Release all reserved video memory to be resetted
void BattleScene::releaseAll() {
	mainCharaTexture.onLostDevice();
	placeholderRectTexture.onLostDevice();
	return;
}

//The dxManager->getGraphics() device has been reset.
//Recreate all reserved video memory to reset dxManager->getGraphics() device
void BattleScene::resetAll() {
	mainCharaTexture.onResetDevice();
	placeholderRectTexture.onResetDevice();
	return;
}
