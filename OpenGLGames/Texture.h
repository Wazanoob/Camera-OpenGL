#pragma once
#include <string>
#include "RendererOGL.h"
using std::string;


class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool loadOGL(RendererOGL& rendererP, const string& filenameP);

	void updateInfo(int& widthOut, int& heightOut);
	void setActive() const;

	SDL_Texture* toSDLTexture() const { return SDLTexture; }

	int getWidth() const { return width; }
	int getHeight() const{ return height; }

private:
	unsigned int textureID;
	string filename;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};

