#include "input.h"

Input::Input() {
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++) keysDown[i] = false; //setting bool for key down
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)keysPressed[i] = false; // setting bool for key pressed
	newLine = true;		//start new line
	textIn = "";		//clear textIn
	charIn = 0;			//clear charIn

	//mouse data
	mouseX = 0;					//screen X
	mouseY = 0;					//screen Y
	mouseRawX = 0;				//HD X
	mouseRawY = 0;				//HD y
	mouseLButton = false;		//true if left mouse button is down
	mouseMButton = false;		//true if middle mouse button is down
	mouseRButton = false;		//true if right mouse button is down
	mouseX1Button = false;		//true if X1 mouse button is down
	mouseX2Button = false;		//true if X2 mouse button is down

	for (int i = 0; i < MAX_CONTROLLERS; i++) {
		controllers[i].vibrateTimeLeft = 0;
		controllers[i].vibrateTimeRight = 0;

	}
}

Input::~Input() {
	if (mouseCaptured) ReleaseCapture();	//Release mouse

}

void Input::initialize(HWND hwnd, bool capture) {
	try {
		mouseCaptured = capture;

		// register high-definition mouse
		Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
		Rid[0].dwFlags = RIDEV_INPUTSINK;
		Rid[0].hwndTarget = hwnd;
		RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

		if (mouseCaptured)
			SetCapture(hwnd);           // capture mouse

		// Clear controllers state
		ZeroMemory(controllers, sizeof(ControllerState) * MAX_CONTROLLERS);

		checkControllers();             // check for connected controllers
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing input system"));
	}
}

void Input::keyDown(WPARAM wParam) {
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		keysDown[wParam] = true;
		keysPressed[wParam] = true;
	}
}

void Input::keyUp(WPARAM wParam) {
	if (wParam < inputNS::KEYS_ARRAY_LEN) {
		keysDown[wParam] = false;
	}
}

void Input::keyIn(WPARAM wParam)
{
	if (newLine)                            // if start of new line
	{
		textIn.clear();
		newLine = false;
	}

	if (wParam == '\b')                     // if backspace
	{
		if (textIn.length() > 0)             // if characters exist
			textIn.erase(textIn.size() - 1);  // erase last character entered
	}
	else
	{
		textIn += wParam;                   // add character to textIn
		charIn = wParam;                    // save last char entered
	}

	if ((char)wParam == '\r')               // if return    
		newLine = true;                     // start new line
}

bool Input::isKeyDown(UCHAR vkey) const
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
		return keysDown[vkey];
	else
		return false;
}

bool Input::wasKeyPressed(UCHAR vkey) const {
	if (vkey < inputNS::KEYS_ARRAY_LEN)return keysPressed[vkey];
	else return false;
}

bool Input::anyKeyPressed() const {
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++) {
		if (keysPressed[i] == true) return true;
	}
	return false;
}

void Input::clearKeyPress(UCHAR vkey) {
	if (vkey < inputNS::KEYS_ARRAY_LEN) keysPressed[vkey] = false;

}

void Input::clear(UCHAR what)
{
	if (what & inputNS::KEYS_DOWN)       // if clear keys down
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysDown[i] = false;
	}
	if (what & inputNS::KEYS_PRESSED)    // if clear keys pressed
	{
		for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
			keysPressed[i] = false;
	}
	if (what & inputNS::MOUSE)           // if clear mouse
	{
		mouseX = 0;
		mouseY = 0;
		mouseRawX = 0;
		mouseRawY = 0;
	}
	if (what & inputNS::TEXT_IN)
		clearTextIn();
}

void Input::mouseIn(LPARAM lParam) {
	mouseX = GET_X_LPARAM(lParam);
	mouseY = GET_Y_LPARAM(lParam);

}

void Input::mouseRawIn(LPARAM lParam)
{
	UINT dwSize = 40;
	static BYTE lpb[40];

	GetRawInputData((HRAWINPUT)lParam, RID_INPUT,
		lpb, &dwSize, sizeof(RAWINPUTHEADER));

	RAWINPUT* raw = (RAWINPUT*)lpb;

	if (raw->header.dwType == RIM_TYPEMOUSE)
	{
		mouseRawX = raw->data.mouse.lLastX;
		mouseRawY = raw->data.mouse.lLastY;
	}
}

void Input::checkControllers()
{
	DWORD result;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		result = XInputGetState(i, &controllers[i].state);
		if (result == ERROR_SUCCESS)
			controllers[i].connected = true;
		else
			controllers[i].connected = false;
	}
}


void Input::readControllers()
{
	DWORD result;
	for (DWORD i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			result = XInputGetState(i, &controllers[i].state);
			if (result == ERROR_DEVICE_NOT_CONNECTED)    // if controller disconnected
				controllers[i].connected = false;
		}
	}
}


void Input::vibrateControllers(float frameTime)
{
	for (int i = 0; i < MAX_CONTROLLERS; i++)
	{
		if (controllers[i].connected)
		{
			controllers[i].vibrateTimeLeft -= frameTime;
			if (controllers[i].vibrateTimeLeft < 0)
			{
				controllers[i].vibrateTimeLeft = 0;
				controllers[i].vibration.wLeftMotorSpeed = 0;
			}
			controllers[i].vibrateTimeRight -= frameTime;
			if (controllers[i].vibrateTimeRight < 0)
			{
				controllers[i].vibrateTimeRight = 0;
				controllers[i].vibration.wRightMotorSpeed = 0;
			}
			XInputSetState(i, &controllers[i].vibration);
		}
	}
}
