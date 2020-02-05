#pragma once

#include <SDL2/SDL.h>

class State {
public:
	virtual ~State() {};
	virtual void init() = 0;
	virtual void input(SDL_Event event) = 0;
	virtual void update() = 0;
	virtual void draw(SDL_Renderer* renderer) = 0; 
	virtual void destroy() = 0;
};