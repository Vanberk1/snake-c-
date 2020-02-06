#include "stateMachine.h"

void StateMachine::pushState(std::unique_ptr<State> state) {
	state->init();
	m_States.push_back(std::move(state));
}

void StateMachine::popState() {
	if(m_States.back() != nullptr)
		m_States.pop_back();
}

void StateMachine::input(SDL_Event event) {
	if(m_States.back() != nullptr)
		m_States.back()->input(event);
}

void StateMachine::update() {
	if(m_States.back() != nullptr)
		m_States.back()->update();
}

void StateMachine::draw(SDL_Renderer* renderer) {
	if(m_States.back() != nullptr)
		m_States.back()->draw(renderer);
}

void StateMachine::destroy() {
	while(!m_States.empty()) {
		m_States.back()->destroy();
		m_States.pop_back();
	}
}