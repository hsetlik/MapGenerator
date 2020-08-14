//
//  main.cpp
//  SDL2_GameEngine
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#include <iostream>
#include "GameGlass.hpp"

Game *game= nullptr;
const int windowWidth = 1200;
const int windowHeight = 650;

int main(int argc, const char * argv[]) {
    game = new Game();
    //grid = new Grid();
    game-> init("Title", 600, 600, windowWidth, windowHeight, false);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}
