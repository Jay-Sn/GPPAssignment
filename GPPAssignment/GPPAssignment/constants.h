#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
// Useful macros

// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
//Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr) {if(ptr){delete [](ptr); ptr = NULL}}
//Safely call onRestDevice
#define SAFE_ON_RESET_DEVICE(ptr) {if(ptr){ptr->onResetDevice();}}
#define TRANSCOLOR SETCOLOR_ARGB(0,255,0,255) // transparent color (magenta)

//Constants

// window
const char CLASS_NAME[] = "Placeholder Fantasy";
const char GAME_TITLE[] = "Placeholder Fantasy";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT  GAME_WIDTH = 1280;              // width of game in pixels
const UINT  GAME_HEIGHT = 720;              // height of game in pixels

//game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;					//the target frame rate (frame/sec)
const float MIN_FRAME_RATE = 10.0f;					//the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;		//minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; //Maximum time used in calculations

const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float ANIMATE_SPEED = 100.0f;             // pixels per second
const float CHARA_SCALE = 1.5f;                  // starting ship scale

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const BYTE ESC_KEY = VK_ESCAPE;					// escape key
const BYTE NAVI_RIGHT_KEY = VK_RIGHT;
const BYTE NAVI_LEFT_KEY = VK_LEFT;
const BYTE NAVI_UP_KEY = VK_UP;
const BYTE NAVI_DOWN_KEY = VK_DOWN;

#endif // !_CONSTANTS_H_
