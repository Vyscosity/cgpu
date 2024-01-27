#pragma once

#include <SDL.h>

class BasicWindow
{

public:
	BasicWindow();

	void create();

	void close();

	void display();

	void clear();

	bool pollEvent(SDL_Event e);

	bool isOpen();

	SDL_Window& getWindow() { return *basicWindow; }

private:

	int width = 1280;
	int height = 720;

	SDL_Window* basicWindow = nullptr;

	bool open = false;

};