#pragma once

#include <SDL2/SDL.h> 
#include <stack>
#include <iostream>
#include "state.h"

class StateMachine {
private:
	std::stack<State*> m_States;

public:
	void addState(State* state);
	void input(SDL_Event event);
	void update();
	void draw(SDL_Renderer* renderer);
	void destroy();
};