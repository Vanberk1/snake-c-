#include "stateMachine.h"

void StateMachine::addState(State* state) {
	state->init();
	m_States.push(state);
}

void StateMachine::input(SDL_Event event) {
	m_States.top()->input(event);
}

void StateMachine::update() {
	m_States.top()->update();
}

void StateMachine::draw(SDL_Renderer* renderer) {
	m_States.top()->draw(renderer);
}

void StateMachine::destroy() {
	while(!m_States.empty()) {
		m_States.top()->destroy();
		m_States.pop();
	}
}