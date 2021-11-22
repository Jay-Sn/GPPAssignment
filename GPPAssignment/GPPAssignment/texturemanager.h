#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H
#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
#include "constants.h"

class TextureManager
{
private:
	UINT	width;			//width of texture by pixels
	UINT	height;			//height of texture in pixels
	LP_TEXTURE	texture;	//pointer to texture
	const char* file;		//name of file
	Graphics* graphics;		//save pointer to graphics
	bool	initialized;	//true when successfully initialized
	HRESULT hr;				//standard return type

public:
	//Constructor
	TextureManager();

	//Destructor
	~TextureManager();

	//Returns a pointer to the texture
	LP_TEXTURE getTexture() const { return texture; }

	//Return the texture width
	UINT getWidth() const { return width; }

	//Return the texture height
	UINT getHeight() const { return height; }

	//Initialize the textureManager
	// *g (pointer to the Graphics object)
	// *file (pointer to name of texture file to load)

	virtual bool initialize(Graphics* g, const char* file);

	virtual void onLostDevice();

	virtual void onResetDevice();

};
#endif // !_TEXTUREMANAGER_H
