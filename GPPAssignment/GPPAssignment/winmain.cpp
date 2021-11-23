// Programming 2D Games
// Copyright (c) 2011 by:
// Charles Kelly
// Chapter 2 "Hello World" Windows Style v1.0
// winmain.cpp

#define _CRTDBG_MAP_ALLOC   //For detecting memory loss
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "gameerror.h"
#include "constants.h"
#include "pfantasy.h"
#include "startingMenu.h"
#include "map.h"

// Function prototypes
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HWND&, HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);

//Game Pointer
Game *game = NULL;
HWND hwnd = NULL;

//=============================================================================
// Starting point for a Windows application
// Parameters are:
//   hInstance - handle to the current instance of the application
//   hPrevInstance - always NULL, obsolete parameter, maintained for backwards compatibilty
//   lpCmdLine - pointer to null-terminated string of command line arguments
//   nCmdShow - specifies how the window is to be shown
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    // Check for memory leak if debug build
#if defined(DEBUG)| defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif // defined(DEBUG| defined(_DEBUG)

    MSG	 msg;

    //Create the game, sets up message handler
    game = new Map;

    // Create the window
    if (!CreateMainWindow(hwnd, hInstance, nCmdShow))
        return false;
    try {
        game->initialize(hwnd);

        // main message loop
        int done = 0;
        while (!done)
        {
            // PeekMessage is a non-blocking method for checking for Windows messages.
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                //look for quit message
                if (msg.message == WM_QUIT)
                    done = 1;

                //decode and pass messages on to WinProc
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
            {
                game->run(hwnd);    //run game loop
            }
        }
        SAFE_DELETE(game); // free memory before exit
        return msg.wParam;
    }
    catch (const GameError& err)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, err.getMessage(), "Error", MB_OK);
    }
    catch (...)
    {
        game->deleteAll();
        DestroyWindow(hwnd);
        MessageBox(NULL, "Unknown error occured in game.", "Error", MB_OK);
    }
    SAFE_DELETE(game); // free memory before exit
    return 0;
}

//=============================================================================
// window event callback function
//=============================================================================
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return (game->messagehandler(hWnd, msg, wParam, lParam));
}

//=============================================================================
// Create the window
// Returns: false on error
//=============================================================================
bool CreateMainWindow(HWND& hwnd, HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wcx;

    // Fill in the window class structure with parameters 
    // that describe the main window. 
    wcx.cbSize = sizeof(wcx);           // size of structure 
    wcx.style = CS_HREDRAW | CS_VREDRAW;    // redraw if size changes 
    wcx.lpfnWndProc = WinProc;          // points to window procedure 
    wcx.cbClsExtra = 0;                 // no extra class memory 
    wcx.cbWndExtra = 0;                 // no extra window memory 
    wcx.hInstance = hInstance;          // handle to instance 
    wcx.hIcon = NULL;
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);   // predefined arrow 
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background brush 
    wcx.lpszMenuName = NULL;           // name of menu resource 
    wcx.lpszClassName = CLASS_NAME;     // name of window class 
    wcx.hIconSm = NULL;                 // small class icon 

    // Register the window class. 
    // RegisterClassEx returns 0 on error.
    if (RegisterClassEx(&wcx) == 0)    // if error
        return false;

    // Create window
    hwnd = CreateWindow(
        CLASS_NAME,             // name of the window class
        GAME_TITLE,            // title bar text
        WS_OVERLAPPEDWINDOW,    // window style
        CW_USEDEFAULT,          // default horizontal position of window
        CW_USEDEFAULT,          // default vertical position of window
        GAME_WIDTH,           // width of window
        GAME_HEIGHT,          // height of the window
        (HWND)NULL,            // no parent window
        (HMENU)NULL,           // no menu
        hInstance,              // handle to application instance
        (LPVOID)NULL);         // no window parameters

    // if there was an error creating the window
    if (!hwnd) {
        DWORD test = GetLastError();
        return false;
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);

    return true;
}
