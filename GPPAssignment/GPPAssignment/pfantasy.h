#ifndef _PFANTASY_H
#define _PFANTASY_H
#define WIN32_LEAN_AND_MEAN

#include "game.h"
//#include "TextureManager.h"
//#include "Image.h"

class PFantasy : public Game
{
private:

public:
	PFantasy();					//Constructor
	virtual ~PFantasy();		//Destructor

	void initialize(HWND hwnd);

	//Override virtual in from Game
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();
};
#endif // !_SPACEWAR_H
