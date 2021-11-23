#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_
#define WIN32_LEAN_AND_MEAN

#include "image.h"
#include "character.h"
#include "textDX.h"
#include "constants.h"
#include <list>

using namespace std;
class UserInterface{

protected:
	list<Image> imageQueue;

	Image enemyNameSection;
	Image actionSelection;

	Image infoSection;
	Image attackButton;
	Image blockButton;

	int numofChara;
	list<Image> listOfHealthBar;
	Image healthBar1;
	Image healthBar2;
	//Image healthBar3;
	//Image healthBar4;

	list<Image> listOfHealthData;
	TextDX healthData1;
	TextDX healthData2;
	//TextDX healthData3;
	//TextDX healthData4;

	list<Image> listOfCharaName;
	TextDX characterName1;
	TextDX characterName2;
	//TextDX characterName3;
	//TextDX characterName4;

public:
	UserInterface();
	~UserInterface();

	bool initializeQueue(int numofChara);

	void draw();

};
#endif // !_USER_INTERFACE_H_
