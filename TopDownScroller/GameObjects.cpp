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
    setIndex(0);
}
void Tile::setIndex(int setting){
    textureIndex = setting;
}

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
                    memberTiles[x][y].isLand = true;
                    memberTiles[x][y].textureIndex = 1;
                    memberTiles[x][y].currentTexture = grassBase;
                    printf("grass texture assigned at: %d, %d\n", x, y);
                    break;
                }
                case 2:{
                    memberTiles[x][y].isLand = true;
                    memberTiles[x][y].textureIndex = 2;
                    memberTiles[x][y].currentTexture = desertBase;
                    break;
                }
            }
    if(texIndex != 0){
        printf("Texture index is %d at: %d, %d\n", texIndex, x, y);
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
            if(memberTiles[x][y].textureIndex != 0){
                printf("Nonzero texture %d rendered at: %d, %d", memberTiles[x][y].textureIndex, x, y);
            }
            
        }
    }
}

Landmass::Landmass(){
}
Landmass::~Landmass(){
}
void Landmass::init(int xStart, int yStart, Map chosenMap){
    xOrigin = xStart;
    yOrigin = yStart;
    map = chosenMap;
    memberCount = 0;
    optionCount = 0;
}
void Landmass::updateOptions(int xPos, int yPos){
    int x = xPos;
    int y = yPos;
    Tile adjacentTiles[4];
    adjacentTiles[0] = map.memberTiles[x][y - 1]; //top
    adjacentTiles[1] = map.memberTiles[x + 1][y]; //right
    adjacentTiles[2] = map.memberTiles[x][y + 1]; //bottom
    adjacentTiles[3] = map.memberTiles[x - 1][y]; //left
    for(int i = 0; i < 4; i++){
        int xOpt = adjacentTiles[i].xPos;
        int yOpt = adjacentTiles[i].yPos;
        bool free = true;
        for(int n = 0; n < optionCount; n++){
            if((_optionTiles[n].xPos == xOpt) && (_optionTiles[n].yPos == yOpt)){
                free = false;
            }
        }
        if(free){
            _optionTiles[optionCount] = adjacentTiles[i];
            optionCount++;
        }
    }
}
void Landmass::placeFirstTile(int texIndex){
    map.memberTiles[xOrigin][yOrigin].setIndex(texIndex);
    map.memberTiles[xOrigin][yOrigin].isLand = true;
    _landMembers[memberCount] = map.memberTiles[xOrigin][yOrigin];
    memberCount++;
    updateOptions(xOrigin, yOrigin);
}

int Landmass::adjacentOfType(Tile checkTile, int texIndex){
    int x = checkTile.xPos;
    int y = checkTile.yPos;
    int texture = texIndex;
    int typeCounter = 0;
    Tile adjacentTiles[4];
    adjacentTiles[0] = map.memberTiles[x][y - 1]; //top
    adjacentTiles[1] = map.memberTiles[x + 1][y]; //right
    adjacentTiles[2] = map.memberTiles[x][y + 1]; //bottom
    adjacentTiles[3] = map.memberTiles[x - 1][y]; //left
    for(int i = 0; i < 4; i++){
        if(adjacentTiles[i].textureIndex == texture){
            typeCounter++;
        }
    }
    return typeCounter;
}

int Landmass::secondOrderOfType(Tile checkTile, int texIndex){
    int x = checkTile.xPos;
    int y = checkTile.yPos;
    Tile adjacentTiles[4];
    adjacentTiles[0] = map.memberTiles[x][y - 1]; //top
    adjacentTiles[1] = map.memberTiles[x + 1][y]; //right
    adjacentTiles[2] = map.memberTiles[x][y + 1]; //bottom
    adjacentTiles[3] = map.memberTiles[x - 1][y]; //left
    Tile secondOrderAdjacents[12];
    int xA = adjacentTiles[0].xPos;
    int yA = adjacentTiles[0].yPos;
    secondOrderAdjacents[0] = map.memberTiles[xA][yA -1]; //top.top
    secondOrderAdjacents[1] = map.memberTiles[xA + 1][yA]; //top.right
    secondOrderAdjacents[2] = map.memberTiles[xA - 1][yA]; //top.left
    int xB = adjacentTiles[1].xPos;
    int yB = adjacentTiles[1].yPos;
    secondOrderAdjacents[3] = map.memberTiles[xB][yB -1]; //right.top
    secondOrderAdjacents[4] = map.memberTiles[xB + 1][yB];// right.right
    secondOrderAdjacents[5] = map.memberTiles[xB][yB + 1]; //right.bottom
    int xC = adjacentTiles[2].xPos;
    int yC = adjacentTiles[2].yPos;
    secondOrderAdjacents[6] = map.memberTiles[xC + 1][yC];//bottom.right
    secondOrderAdjacents[7] = map.memberTiles[xC][yC + 1]; //bottom.bottom
    secondOrderAdjacents[8] = map.memberTiles[xC -1][yC];
    int xD = adjacentTiles[3].xPos;
    int yD = adjacentTiles[3].yPos;
    secondOrderAdjacents[9] = map.memberTiles[xD][yD -1];//left top
    secondOrderAdjacents[10] = map.memberTiles[xD][yD + 1];//left bottom
    secondOrderAdjacents[11] = map.memberTiles[xD - 1][yD];//left left
    int count = 0;
    for(int i = 0; i < 12; i++){
        if(secondOrderAdjacents[i].textureIndex == texIndex)
        {
            count++;
        }
    }
    return count;
}

int Landmass::grassWeight(Tile checkTile){
    int weight  = 0;
    int adjacent1 = adjacentOfType(checkTile, 1);
    adjacent1 = adjacent1 * 3;
    int adjacent2 = secondOrderOfType(checkTile, 1);
    weight = adjacent1 + adjacent2;
    return weight;
}

int Landmass::desertWeight(Tile checkTile){
    int weight  = 0;
    int adjacent1 = adjacentOfType(checkTile, 2);
    adjacent1 = adjacent1 * 3;
    int adjacent2 = secondOrderOfType(checkTile, 2);
    weight = adjacent1 + adjacent2;
    return weight;
}

void Landmass::testGraphic(){
    for(int i = 0; i < 20; i++){
        int randX = rand() % 80;
        int randY = rand() % 43;
        map.memberTiles[randX][randY].setIndex(1);
        int lastIndex = map.memberTiles[randX][randY].textureIndex;
        printf("Texture %d placed at: %d, %d\n", lastIndex, randX, randY);
        map.assignTexture(map.memberTiles[randX][randY]);
    }
    printf("Graphics test calculated\n");
}
