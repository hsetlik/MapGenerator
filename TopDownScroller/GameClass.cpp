//
//  GameGlass.cpp
//  SDL2_GameEngine
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#include "GameClass.hpp"

Map workingMap;
Landmass landmass;

Game::Game() {
    }
Game::~Game(){
    }
void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        IMG_Init(IMG_INIT_PNG);
        printf("SDL_Img initialized\n");
        //verifies that SDL started up correctly
        printf("SDL Initialized\n");
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window){
            //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Window Created\n");
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Renderer Created\n");
        }
        isRunning = true;
    }
    workingMap.initMemberTiles();
    workingMap.loadAllTextures(renderer);
    landmass.init(workingMap);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:{
            Tile clickedTile = workingMap.tileClicked();
            clickedTile.isClicked();
            workingMap.printTextures();
            landmass.createLandmass(clickedTile, 1, 45);
    }
    }
}


void Game::render(){
    SDL_RenderClear(renderer);
    workingMap.renderMap(renderer);
    SDL_RenderPresent(renderer);
}

void Game::update(){
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    printf("Game Cleaned\n");
}
