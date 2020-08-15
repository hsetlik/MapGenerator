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


class Tile {
public:
    Tile();
    ~Tile();
    void init(int xPos, int yPos);
    bool isLand;
    int textureIndex;
    SDL_Texture * currentTexture;
private:
    int _grassWeight;
    int _desertWeight;
    int _xPos;
    int _yPos;
};


class Map {
public:
    Map();
    ~Map();
    SDL_Texture * oceanBase;
    SDL_Texture * grassBase;
    SDL_Texture * desertBase;
    Tile memberTiles[80][43];
    void loadAllTextures(SDL_Renderer* renderer);
    void assignTextures();
    void initMemberTiles();
    void renderMap(SDL_Renderer * renderer);
};


class Landmass{
public:
    Landmass();
    ~Landmass();
    void init(int xStart, int yStart, Map chosenMap);
    int xStart;
    int yStart;
    Tile mapTiles[80][43];
    Map map;
    int adjacentOfType(Tile checkTile, int textureIndex);
    void assignWeights(Tile tile);
    int grassWeight(Tile tile);
    int desertWeight(Tile tile);
    void populate(Tile startingTile, int numTiles);
    void updateOptions();
    int memberCount;
    int optionCount;
private:
    Tile _landMembers[128];
    int _optionCoords[256][256];
};

#endif /* GameObjects_hpp */
