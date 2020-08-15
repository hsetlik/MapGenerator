//
//  GameObjects.hpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#ifndef GameObjects_hpp
#define GameObjects_hpp
#include "GameGlass.hpp"
#include <stdio.h>


class Tile {
public:
    Tile();
    ~Tile();
    void init(int xPos, int yPos);
    bool isLand;
    int grasslandWeight();
    int desertWeight();
    void assignTexture(SDL_Texture * texture);
    int textureIndex;
    SDL_Texture * textureChoice;
private:
    int _xPos;
    int _xpos;
};


class Map {
public:
    Map();
    ~Map();
    Tile memberTiles[80][43];
    void initMemberTiles();
};

#endif /* GameObjects_hpp */
