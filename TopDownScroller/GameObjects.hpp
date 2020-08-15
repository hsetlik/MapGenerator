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
SDL_Texture * oceanBase;
SDL_Texture * grassBase;
SDL_Texture * desertBase;

class Tile {
public:
    Tile();
    ~Tile();
    void init(int xPos, int yPos);
    bool isLand;
    int textureIndex;
    void updateTexture();
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
    Tile memberTiles[80][43];
    void loadAllTextures(SDL_Renderer* renderer);
    void initMemberTiles();
    void renderMap(SDL_Renderer * renderer);
};

#endif /* GameObjects_hpp */
