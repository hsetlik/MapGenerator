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

Tile memberTiles[80][43];

Map::Map(){
}
Map::~Map(){
}

void Map::initMemberTiles(){
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            memberTiles[x][y].init(x, y);
            assignTextures();
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
                    printf("texture 1 assigned at: %d, %d\n", x, y);
                    memberTiles[x][y].currentTexture = grassBase;
                    printf("grass texture assigned at: %d, %d\n", x, y);
                    break;
                }
                case 2:{
                    printf("texture 2 assigned at: %d, %d\n", x, y);
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
    assignTextures();
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
void Landmass::init(int xStart, int yStart, Map chosenMap){
    xOrigin = xStart;
    yOrigin = yStart;
    map = chosenMap;
    memberCount = 0;
    optionCount = 0;
    created = false;
    printf("Landmass initialized\n");
}
void Landmass::updateOptions(int xPos, int yPos){
    int x = xPos;
    int y = yPos;
    Tile adjacentTiles[4];
    adjacentTiles[0] = memberTiles[x][y - 1]; //top
    adjacentTiles[1] = memberTiles[x + 1][y]; //right
    adjacentTiles[2] = memberTiles[x][y + 1]; //bottom
    adjacentTiles[3] = memberTiles[x - 1][y]; //left
    for(int i = 0; i < 4; i++){
        int xOpt = adjacentTiles[i].xPos;
        int yOpt = adjacentTiles[i].yPos;
        bool free = true;
        for(int n = 0; n < optionCount; n++){
            if((_optionTiles[n].xPos == xOpt) && (_optionTiles[n].yPos == yOpt)){
                free = false;
            }
            for(int i = 0; i < memberCount; i++){
                if((_landMembers[i].xPos == xOpt)&&(_landMembers[i].yPos == yOpt)){
                    free = false;
                }
            }
        }
        if(free){
            _optionTiles[optionCount] = adjacentTiles[i];
            optionCount++;
        }
    }
    printf("options updated\n");
}
void Landmass::placeFirstTile(Tile startingTile, int texIndex){
    xOrigin = startingTile.xPos;
    yOrigin = startingTile.yPos;
    map.memberTiles[xOrigin][yOrigin].textureIndex = texIndex;
    map.memberTiles[xOrigin][yOrigin].isLand = true;
    _landMembers[memberCount] = map.memberTiles[xOrigin][yOrigin];
    memberCount++;
    updateOptions(xOrigin, yOrigin);
    printf("first tile placed\n");
    map.assignTextures();
}

int Landmass::adjacentOfType(Tile checkTile, int texIndex){
    int x = checkTile.xPos;
    int y = checkTile.yPos;
    int texture = texIndex;
    int typeCounter = 0;
    Tile adjacentTiles[4];
    adjacentTiles[0] = memberTiles[x][y - 1]; //top
    adjacentTiles[1] = memberTiles[x + 1][y]; //right
    adjacentTiles[2] = memberTiles[x][y + 1]; //bottom
    adjacentTiles[3] = memberTiles[x - 1][y]; //left
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
    adjacentTiles[0] = memberTiles[x][y - 1]; //top
    adjacentTiles[1] = memberTiles[x + 1][y]; //right
    adjacentTiles[2] = memberTiles[x][y + 1]; //bottom
    adjacentTiles[3] = memberTiles[x - 1][y]; //left
    Tile secondOrderAdjacents[12];
    int xA = adjacentTiles[0].xPos;
    int yA = adjacentTiles[0].yPos;
    secondOrderAdjacents[0] = memberTiles[xA][yA -1]; //top.top
    secondOrderAdjacents[1] = memberTiles[xA + 1][yA]; //top.right
    secondOrderAdjacents[2] = memberTiles[xA - 1][yA]; //top.left
    int xB = adjacentTiles[1].xPos;
    int yB = adjacentTiles[1].yPos;
    secondOrderAdjacents[3] = memberTiles[xB][yB -1]; //right.top
    secondOrderAdjacents[4] = memberTiles[xB + 1][yB];// right.right
    secondOrderAdjacents[5] = memberTiles[xB][yB + 1]; //right.bottom
    int xC = adjacentTiles[2].xPos;
    int yC = adjacentTiles[2].yPos;
    secondOrderAdjacents[6] = memberTiles[xC + 1][yC];//bottom.right
    secondOrderAdjacents[7] = memberTiles[xC][yC + 1]; //bottom.bottom
    secondOrderAdjacents[8] = memberTiles[xC -1][yC];
    int xD = adjacentTiles[3].xPos;
    int yD = adjacentTiles[3].yPos;
    secondOrderAdjacents[9] = memberTiles[xD][yD -1];//left top
    secondOrderAdjacents[10] = memberTiles[xD][yD + 1];//left bottom
    secondOrderAdjacents[11] = memberTiles[xD - 1][yD];//left left
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
    weight += rand() % 10;
    return weight;
}

int Landmass::desertWeight(Tile checkTile){
    int weight  = 0;
    int adjacent1 = adjacentOfType(checkTile, 2);
    adjacent1 = adjacent1 * 3;
    int adjacent2 = secondOrderOfType(checkTile, 2);
    weight = adjacent1 + adjacent2;
    weight += rand() % 10;
    return weight;
}

void Landmass::addTile(){
    int chosenIndex = rand() % optionCount;
    Tile chosenTile = _optionTiles[chosenIndex];
    int gWeight = grassWeight(chosenTile);
    int dWeight = desertWeight(chosenTile);
    gWeight += rand() % 8;
    dWeight += rand() % 8;
    int texChoice;
    if(dWeight < gWeight){
        printf("Grass chosen\n");
        texChoice = 1;
    } else {
        printf("Sand chosen\n");
        texChoice = 2;
    }
    int cX = chosenTile.xPos;
    int cY = chosenTile.yPos;
    chosenTile.isLand = true;
    _landMembers[memberCount] = chosenTile;
    chosenTile.textureIndex = texChoice;
    map.memberTiles[cX][cY].textureIndex = texChoice;
    memberCount++;
    printf("Tile placed at: [%d][%d]\n", chosenTile.xPos, chosenTile.yPos);
    printf("Texture index: %d\n", chosenTile.textureIndex);
    printf("Map texture index: %d\n", map.memberTiles[cX][cY].textureIndex);
    updateOptions(chosenTile.xPos, chosenTile.yPos);
    map.assignTextures();
    printf("Assigned Map texture index: %d\n", map.memberTiles[cX][cY].textureIndex);
}

void Landmass::createLandmass(Tile firstTile, int firstTex, int numTiles){
    placeFirstTile(firstTile, firstTex);
    for(int i = 0; i < numTiles; i++){
        addTile();
    }
    created = true;
    printf("landmass created\n");
}
