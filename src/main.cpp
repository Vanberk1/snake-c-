#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "stateMachine.h"
#include "gameState.h"
#include "menuState.h"

const int GRID_X = 40;
const int GRID_Y = 30;

bool IsRunning = true;

int main(int argc, char* args[]) { 
    int countedFrames = 0;
    int ticksLastFrame = SDL_GetTicks();

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL Failed!" << std::endl;
        return 0;
    }
    if(TTF_Init() != 0) {
        std::cout << "TTF Failed!" << std::endl;
        return 0;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Snake!", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        GRID_X * 20,
        GRID_Y * 20,
        SDL_WINDOW_SHOWN
    );
    if(!window) {
        std::cout << "SDL window Failed!" << std::endl;
        return 0;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        std::cout << "SDL renderer Failed!" << std::endl;
        return 0;
    }

    StateMachine stateMachine;
    stateMachine.pushState(std::make_unique<MenuState>(&stateMachine, renderer));

    float deltaTime = 0.16f;

    while(IsRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                IsRunning = false;
            }
            else {
                stateMachine.input(event);
            }
        }

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + (1000 / 60)));
        float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
        deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
        ticksLastFrame = SDL_GetTicks();

        float avgFPS = countedFrames / ( SDL_GetTicks() / 1000.f );
        if( avgFPS > 100000 ) {
            avgFPS = 0;
        }
        std::stringstream ss;
        ss << avgFPS;
        std::string windowTitle = "SNAKE - FPS: " + ss.str();
        SDL_SetWindowTitle(window, windowTitle.c_str());

        ++countedFrames;

        stateMachine.update(deltaTime);

		SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	    SDL_RenderClear(renderer);
        stateMachine.draw();
        SDL_RenderPresent(renderer);
    }

    stateMachine.destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}