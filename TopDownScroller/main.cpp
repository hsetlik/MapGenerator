//
//  main.cpp
//  SDL2_GameEngine
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#include <iostream>
#include "GameClass.hpp"

Game *game= nullptr;
const int windowWidth = 1200;
const int windowHeight = 645;
const int FPS = 60;
const int frameTime = 1000/FPS;

Uint32 frameStart;
int frameDelay;

int main(int argc, const char * argv[]) {
    game = new Game();
    //grid = new Grid();
    game-> init("Title", 600, 600, windowWidth, windowHeight, false);
    while(game->running()){
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();
        frameDelay = SDL_GetTicks() - frameStart;
        if(frameTime > frameDelay){
            SDL_Delay(frameTime-frameDelay);
        }
    }
    game->clean();
    return 0;
}
