#pragma once
#include <SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

class Window
{
public:
	// We always delete constructor, copy constructor and assignment operator if we wont need them.
	// Here we just need the constructor
	Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;

	bool initialize();
	void close();

	SDL_Window* getSDLWindow() const { return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	SDL_Window* SDLWindow;
	int width;
	int height;
};