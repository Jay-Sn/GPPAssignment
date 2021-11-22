#include "graphics.h"

//Constructor
Graphics::Graphics()
{
	direct3d = NULL;
	device3d = NULL;
	fullscreen = false;

	//Below replaced in initialze()
	width = GAME_WIDTH;
	height = GAME_HEIGHT;

	backColor = SETCOLOR_ARGB(255, 0, 0, 128); //Dark blue
}

//Destructor
Graphics:: ~Graphics() {
	releaseAll();
}

//Release all
void Graphics::releaseAll() {
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(direct3d);
}

void Graphics::initD3Dpp()
{
	try {
		ZeroMemory(&d3dpp, sizeof(d3dpp)); // Fill the structure with 0

		// Fill in parameters needed (Seems like everything here is about the "animation" shown on the screen.
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullscreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = (!fullscreen);
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	catch (...)
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing D3D presentation parameters"));
	}
}

void Graphics::initialize(HWND hw, int w, int h, bool full)
{
	hwnd = hw;
	width = w;
	height = h;
	fullscreen = full;

	//initialize Direct3D
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3d == NULL)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Direct3D"));

	initD3Dpp(); // init D3D presentation parameters

	// Determine if graphics card supports hardware texturing and lighting and vertex shaders
	D3DCAPS9 caps;
	DWORD behaviour;
	result = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	//If shader does not support HW T&L or does not support 1.1 vertex shaders in hardware, then switch to software vertex processing.
	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 || caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behaviour = D3DCREATE_SOFTWARE_VERTEXPROCESSING; // Using software only processing
	else
		behaviour = D3DCREATE_HARDWARE_VERTEXPROCESSING; // Using hardware only processing

	//Create Direct3D device
	result = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		behaviour,
		&d3dpp,
		&device3d
	);

	if (FAILED(result))
		throw (GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));

	result = D3DXCreateSprite(device3d, &sprite);

	if (FAILED(result)) throw (GameError(gameErrorNS::FATAL_ERROR, "Error create Direct3D sprite "));


}

void Graphics::setBackColor(COLOR_ARGB c) {
	backColor = c;
}

HRESULT Graphics::showBackbuffer()
{
	result = E_FAIL; // default to fail, replace upon success

	//Display backbufffer to screen
	result = device3d->Present(NULL, NULL, NULL, NULL);
	return result;

}

//Test for lost device
HRESULT Graphics::getDeviceState() {
	result = E_FAIL;//Defaulted to fail, replace on success
	if (device3d == NULL) return result;
	result = device3d->TestCooperativeLevel();
	return result;
}

//Reset the graphics device
HRESULT Graphics::reset() {
	result = E_FAIL;
	initD3Dpp();							//init D3D presentation parameters
	result = device3d->Reset(&d3dpp);		//attempt to reset graphics device
	return result;
}

HRESULT Graphics::loadTexture(const char* filename, COLOR_ARGB transcolor, UINT& width, UINT& height, LP_TEXTURE& texture) {
	D3DXIMAGE_INFO info;

	try {
		if (filename == NULL) {
			texture = NULL;
			return D3DERR_INVALIDCALL;
		}

		//Get width and height from file
		result = D3DXGetImageInfoFromFileA(filename, &info);
		if (result != D3D_OK) return result;
		width = info.Width;
		height = info.Height;

		// Create the new Texture by loading from file
		result = D3DXCreateTextureFromFileExA(
			device3d,			// 3D device
			filename,			// image filename
			info.Width,			// texture width
			info.Height,		// texture height
			1,					// mip-map levels (1 for no chain)
			0,					// usage
			D3DFMT_UNKNOWN,		// surface format (default)
			D3DPOOL_DEFAULT,	// memory class for the texture
			D3DX_DEFAULT,		// image filter
			D3DX_DEFAULT,		// mip filter
			transcolor,			// color key for transparency
			&info,				// bitmap file info (from loaded file)
			NULL,				// color pallete
			&texture			//destinatin texture
		);
	}
	catch (...) {
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error in Graphics::loadTexture"));
	}

	return result;
}

void Graphics::drawSprite(const SpriteData& spriteData, COLOR_ARGB color) {
	if (spriteData.texture == NULL) return; // if there are no textures

	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(spriteData.width / 2 * spriteData.scale), (float)(spriteData.height / 2 * spriteData.scale));

	D3DXVECTOR2 translate = D3DXVECTOR2((float)spriteData.x, (float)spriteData.y); //scaling position of the sprite

	D3DXVECTOR2	scaling(spriteData.scale, spriteData.scale);

	if (spriteData.flipHorizontal) {
		scaling.x *= -1;

		spriteCenter.x -= (float)(spriteData.width * spriteData.scale);

		translate.x += (float)(spriteData.width * spriteData.scale);
	}
	if (spriteData.flipVertical) {
		scaling.y *= -1;

		spriteCenter.y -= (float)(spriteData.height * spriteData.scale);

		translate.y += (float)(spriteData.height * spriteData.scale);
	}

	D3DXMATRIX matrix;

	D3DXMatrixTransformation2D(
		&matrix,
		NULL,
		0.0f,
		&scaling,
		&spriteCenter,
		(float)(spriteData.angle),
		&translate
	);

	sprite->SetTransform(&matrix);

	sprite->Draw(spriteData.texture, &spriteData.rect, NULL, NULL, color);
}