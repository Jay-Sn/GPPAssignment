#ifndef _MENUOPTION_H             // prevent multiple definitions if this 
#define _MENUOPTION_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <list>
#include <string>

struct MenuOption {
	std::string option;
	int x;
	int y;
};
#endif
