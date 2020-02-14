#pragma once

#include <SDL2/SDL.h>

extern bool IsRunning;

class State {
public:
	virtual ~State() {};
	virtual void init() = 0;
	virtual void input(SDL_Event event) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void draw() = 0; 
	virtual void destroy() = 0;
};