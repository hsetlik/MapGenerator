//
//  GameObjects.hpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#ifndef GameObjects_hpp
#define GameObjects_hpp
#include "/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h"
#include "/Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include <stdio.h>
#include <cmath>


class Tile {
public:
    Tile();
    ~Tile();
    void init(int xPos, int yPos);
    bool isLand;
    int textureIndex;
    SDL_Texture * currentTexture;
    int xPos;
    int yPos;
    int numAdjacent;
    int numWithinThree;
    void setIndex(int index);
    void isClicked();
    int landWeight;
private:
    int _grassWeight;
    int _desertWeight;
 
};


class Map {
public:
    Map();
    ~Map();
    SDL_Texture * oceanBase;
    SDL_Texture * grassBase;
    SDL_Texture * desertBase;
    void loadAllTextures(SDL_Renderer* renderer);
    void assignTexture(Tile tile);
    void assignAllTextures();
    void initMemberTiles();
    void sendClick();
    Tile tileClicked();
    void printTextures();
    int runCount = 1;
    void renderMap(SDL_Renderer * renderer);
};


class Landmass{
public:
    Landmass();
    ~Landmass();
    void init(Map chosenMap);
    Map map;
    int optionCount;
    int memberCount;
    int xInLimits(int xIn);
    int yInLimits(int yIn);
    Tile* adjacentTiles(Tile tile);
    Tile* withinThree(Tile tile);
    int numNeighbors(Tile tile);
    void updateLandWeight(Tile tile);
    void addOptionsFrom(Tile tile);
    void addMember(int xPos, int yPos, int texIndex);
    
private:
    Tile _landMembers[3440];
    Tile _optionTiles[3440];
};

#endif /* GameObjects_hpp */
