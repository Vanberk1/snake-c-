#pragma once

#include <SDL2/SDL.h> 
#include <vector>
#include <memory>
#include <iostream>
#include "state.h"

class StateMachine {
private:
	std::vector<std::unique_ptr<State>> m_States;

public:
	void pushState(std::unique_ptr<State> state);
	void popState();
	void restart(std::unique_ptr<State> state);
	void input(SDL_Event event);
	void update();
	void draw();
	void destroy();
};