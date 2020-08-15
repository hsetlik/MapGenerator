//
//  Landmass.hpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#ifndef Landmass_hpp
#define Landmass_hpp
#include "GameGlass.hpp"
#include "GameObjects.hpp"
#include <stdio.h>

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

#endif /* Landmass_hpp */
