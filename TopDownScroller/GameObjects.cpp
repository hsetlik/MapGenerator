//
//  GameObjects.cpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#include "GameObjects.hpp"

Tile::Tile(){
}
Tile::~Tile(){
}
void Tile::init(int xSet, int ySet){
    xPos = xSet;
    yPos = ySet;
    isLand = false;
    landWeight = 3;
    numAdjacent = 0;
    numWithinThree = 0;
    setIndex(0);
}
void Tile::setIndex(int setting){
    textureIndex = setting;
}

void Tile::isClicked(){
    printf("Tile clicked at: %d, %d\n", xPos, yPos);
}
Tile memberTiles[80][43];

Map::Map(){
}
Map::~Map(){
}

void Map::initMemberTiles(){
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            memberTiles[x][y].init(x, y);
        }
    }
}
void Map::assignTexture(Tile tile){
    int x = tile.xPos;
    int y = tile.yPos;
            int texIndex = memberTiles[x][y].textureIndex;
            switch(texIndex){
                case 0:{
                    memberTiles[x][y].currentTexture = oceanBase;
                    break;
                }
                case 1:{
                    //printf("texture 1 assigned at: %d, %d\n", x, y);
                    memberTiles[x][y].currentTexture = grassBase;
                    //printf("grass texture assigned at: %d, %d\n", x, y);
                    break;
                }
                case 2:{
                    //printf("texture 2 assigned at: %d, %d\n", x, y);
                    memberTiles[x][y].currentTexture = desertBase;
                    break;
                }
            }
    if(texIndex != 0){
       // printf("Texture index is %d at: %d, %d\n", texIndex, x, y);
    }
        }

void Map::loadAllTextures(SDL_Renderer * renderer){
    SDL_Surface * tempSurface1 = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TopDownScroller/Tiles/Tile_0000_Ocean_Default.png");
    oceanBase = SDL_CreateTextureFromSurface(renderer, tempSurface1);
    SDL_FreeSurface(tempSurface1);
    SDL_Surface * tempSurface2 = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TopDownScroller/Tiles/Tile_0001_Grass_Default.png");
    grassBase = SDL_CreateTextureFromSurface(renderer, tempSurface2);
    SDL_FreeSurface(tempSurface2);
    SDL_Surface * tempSurface3 = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TopDownScroller/Tiles/Tile_0002_Sand_Default.png");
    desertBase = SDL_CreateTextureFromSurface(renderer, tempSurface3);
    SDL_FreeSurface(tempSurface3);
}

void Map::renderMap(SDL_Renderer *renderer){
    //printf("renderMap Started\n");
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            assignTexture(memberTiles[x][y]);
            SDL_Texture *texture = memberTiles[x][y].currentTexture;
            SDL_Rect destRect;
            destRect.w = 15;
            destRect.h = 15;
            destRect.x = 15 * x;
            destRect.y = 15 * y;
            SDL_RenderCopy(renderer, texture, NULL, &destRect);
            
        }
    }
}

void Map::sendClick(){
    double _clickX;
    double _clickY;
    int xClickPx;
    int yClickPx;
    SDL_GetMouseState(&xClickPx, &yClickPx);
    _clickX = xClickPx / 15;
    _clickY = yClickPx / 15;
    int clickX = round(_clickX);
    int clickY = round(_clickY);
    memberTiles[clickX][clickY].isClicked();
    
}

Tile Map::tileClicked(){
    //assignTextures();
    double _clickX;
    double _clickY;
    int xClickPx;
    int yClickPx;
    SDL_GetMouseState(&xClickPx, &yClickPx);
    _clickX = xClickPx / 15;
    _clickY = yClickPx / 15;
    int clickX = round(_clickX);
    int clickY = round(_clickY);
    return memberTiles[clickX][clickY];
}

void Map::printTextures(){
    printf("starting texture printing...\n");
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            int thisTexture = memberTiles[x][y].textureIndex;
            if(thisTexture != 0){
                printf("Texture is %d at: %d, %d\n", thisTexture, x, y);
            }
        }
    }
    printf("texture printing finished\n");
}

Landmass::Landmass(){
}
Landmass::~Landmass(){
}
void Landmass::init(Map chosenMap){
    map = chosenMap;
    memberCount = 0;
    optionCount = 0;
    printf("Landmass initialized\n");
}

int Landmass::xInLimits(int xIn){
    if(xIn < 78){
        return 79;
    } else if(xIn < 1){
        return 0;
    } else{
        return xIn;
    }
}
int Landmass::yInLimits(int yIn){
    if(yIn < 41){
        return 42;
    } else if(yIn < 1){
        return 0;
    } else{
        return yIn;
    }
}


Tile* Landmass::adjacentTiles(Tile tile){
    Tile adjacents[4];
    int x = tile.xPos;
    int y = tile.yPos;
    if(y > 0){
    adjacents[0] = memberTiles[x][y - 1];//top
        tile.numAdjacent++;
    }
    if(x < 79){
    adjacents[1] = memberTiles[x + 1][y];//left
        tile.numAdjacent++;
    }
    if(y < 43){
    adjacents[2] = memberTiles[x][y + 1];//bottom
        tile.numAdjacent++;
    }
    if(x > 0){
    adjacents[3] = memberTiles[x - 1][y];//right
        tile.numAdjacent++;
    }
    return adjacents;
}

bool yInRange(int input){
    if(input < 0 || input > 42 ){
        return false;
    } else {
        return true;
    }
}

bool xInRange(int input){
    if(input < 0 || input > 79){
        return false;
    } else {
        return true;
    }
}


Tile* Landmass::withinThree(Tile tile){
    Tile* pNeighbors = adjacentTiles(tile);
    Tile neighbors[4];
    int maxNeighbors = tile.numAdjacent;
    for(int i = 0; i < maxNeighbors; i++){
        neighbors[i] = pNeighbors[i];
    }
    //4 in second order, 15 in third
    Tile inRange[20];
    int assignedInRange = 0;
    for(int i = 0; i < maxNeighbors; i++){
        Tile* pIterNeighbors = adjacentTiles(neighbors[i]);
        Tile iterNeighbors[4];
        int iterMax = neighbors[i].numAdjacent;
        for(int n = 0; n < iterMax; n++){
            iterNeighbors[i] = pIterNeighbors[i];
            int x = iterNeighbors[i].xPos;
            int y = iterNeighbors[i].yPos;
            if((yInRange(y))&&(xInRange(x))){
            if(assignedInRange == 0){
                inRange[0] = memberTiles[x][y];
                assignedInRange++;
                tile.numWithinThree++;
            } else{
                inRange[assignedInRange] = memberTiles[x][y];
                assignedInRange++;
                tile.numWithinThree++;
            }
            }}
    }
    return inRange;
}

int Landmass::numNeighbors(Tile tile){
    Tile* pTiles = adjacentTiles(tile);
    Tile tiles[4];
    int maxNumber = tile.numAdjacent;
    int neighborCount = 0;
    for(int i = 0; i < maxNumber; i++){
        tiles[i] = pTiles[i];
        int x = tiles[i].xPos;
        int y = tiles[i].xPos;
        if(memberTiles[x][y].isLand){
            neighborCount++;
        }
    }
    return neighborCount;
}

void Landmass::addOptionsFrom(Tile tile){
    Tile* pTiles = adjacentTiles(tile);
    Tile tiles[4];
    int maxNumber = tile.numAdjacent;
    for(int i = 0; i < maxNumber; i++){
        bool valid = true;
        tiles[i] = pTiles[i];
        int x = tiles[i].xPos;
        int y = tiles[i].yPos;
        if(memberTiles[x][y].isLand){
            valid = false;
        }
        for(int n = 0; n < optionCount; n++){
            int optX = _optionTiles[n].xPos;
            int optY = _optionTiles[n].yPos;
            if((optX ==x)&&(optY == y)){
                valid = false;
            }
        }
        if(valid){
            _optionTiles[optionCount] = tiles[i];
            updateLandWeight(_optionTiles[optionCount]);
            optionCount++;
        }
    }
}

void Landmass::updateLandWeight(Tile tile){
    int adjConstant = 8;
    Tile* pTileA = adjacentTiles(tile);
    Tile adjacentTiles[4];
    for(int i = 0; i < tile.numAdjacent; i++){
        adjacentTiles[i] = pTileA[i];
        int x = adjacentTiles[i].xPos;
        int y = adjacentTiles[i].yPos;
        if(adjacentTiles[i].isLand){
            memberTiles[x][y].landWeight += adjConstant;
        }
    }
    int inThreeConstant = 3;
    Tile* pTileB = withinThree(tile);
    Tile withinThree[20];
    for(int n = 0; n < tile.numWithinThree; n++){
        withinThree[n] = pTileB[n];
        int x = withinThree[n].xPos;
        int y = withinThree[n].yPos;
        if(withinThree[n].isLand){
            memberTiles[x][y].landWeight += inThreeConstant;
        }
    }
}
void Landmass::addMember(int xPos, int yPos, int texIndex){
    memberTiles[xPos][yPos].setIndex(texIndex);
    memberTiles[xPos][yPos].isLand = true;
    addOptionsFrom(memberTiles[xPos][yPos]);
}
