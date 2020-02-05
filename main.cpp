#include <SDL2/SDL.h>
#include <iostream>
#include "stateMachine.h"
#include "gameState.h"

const int GRID_X = 40;
const int GRID_Y = 30;

int main(int argc, char* args[]) { 
    bool isRunning = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL Failed!" << std::endl;
        return 1;
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
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer) {
        std::cout << "SDL renderer Failed!" << std::endl;
        return 1;
    }

    StateMachine stateMachine;

    // GameState* gameState = new GameState();
    // gameState->init();
    stateMachine.addState(new GameState());

    // int m_Score = 0;
	// int m_Timer = 0;
	// int m_SnakeSpeed = 50;
	// int m_Size = 20;
	// int m_PositionX = 4;
	// int m_PositionY = 5;

    // Snake m_Snake(m_PositionX, m_PositionY, m_Size, RIGHT);
	// Food m_Food(m_Size);

    while(isRunning) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isRunning = false;
            }
            
            stateMachine.input(event);
            // gameState->input(event);
            // if(!m_Snake.gameOver()) {
            //     if(event.type == SDL_KEYDOWN) {
            //         if(event.key.keysym.scancode == SDL_SCANCODE_W) {
            //             m_Snake.changeDirection(UP);
            //         }
            //         if(event.key.keysym.scancode == SDL_SCANCODE_A) {
            //             m_Snake.changeDirection(LEFT);
            //         }
            //         if(event.key.keysym.scancode == SDL_SCANCODE_S) {
            //             m_Snake.changeDirection(DOWN);
            //         }
            //         if(event.key.keysym.scancode == SDL_SCANCODE_D) {
            //             m_Snake.changeDirection(RIGHT);
            //         }

            //         if(event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
            //             // snake.addSegment();
            //             // food.respawn(snake);
            //         }
            //     }
            // }
        }

        stateMachine.update();
        // gameState->update();
        // if(!m_Snake.gameOver()) {
        //     m_Timer++;
        //     if(m_Timer > m_SnakeSpeed) {
        //         m_Snake.update();
                
        //         SDL_Rect headRect = m_Snake.getBody().front();
        //         SDL_Rect foodRect = m_Food.getBody();
        //         if(headRect.x == foodRect.x && headRect.y == foodRect.y) {
        //             m_Score++;
        //             m_Snake.addSegment();
        //             m_Food.respawn(m_Snake);
        //             std::cout << "Score: " << m_Score << std::endl;
        //         }
        //         m_Timer = 0;
        //     }
        // }

        stateMachine.draw(renderer);
        // gameState->draw(renderer);
        // if(!m_Snake.gameOver()) {
        //     SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        //     SDL_RenderClear(renderer);
        //     m_Food.draw(renderer);
        //     m_Snake.draw(renderer);
        //     SDL_RenderPresent(renderer);
        // }
    }

    stateMachine.destroy();
    // gameState->destroy();
    // delete m_Snake;
    // delete m_Food;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}