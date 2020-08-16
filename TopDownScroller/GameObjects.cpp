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
    created = false;
    printf("Landmass initialized\n");
}

int limitToZero(int input){
    if(input < 1){
        return 0;
    } else {
        return input;
    }
}

int xTopLimit(int input)
{
    if(input > 78){
        return 79;
    } else {
        return input;
    }
}

int yTopLimit(int input)
{
    if(input > 41){
        return 42;
    } else {
        return input;
    }
}
void Landmass::updateOptions(int xPos, int yPos){
    int x = xPos;
    int y = yPos;
    int xUp = xTopLimit(x + 1);
    int xDown = limitToZero(x - 1);
    int yUp = yTopLimit(y + 1);
    int yDown = limitToZero(y - 1);
    Tile adjacentTiles[4];
    adjacentTiles[0] = memberTiles[x][yDown]; //top
    adjacentTiles[1] = memberTiles[xUp][y]; //right
    adjacentTiles[2] = memberTiles[x][yUp]; //bottom
    adjacentTiles[3] = memberTiles[xDown][y]; //left
    for(int i = 0; i < 4; i++){
        int xOpt = adjacentTiles[i].xPos;
        int yOpt = adjacentTiles[i].yPos;
        bool free = true;
        for(int n = 0; n < optionCount; n++){
            if((_optionTiles[n].xPos == xOpt) && (_optionTiles[n].yPos == yOpt)){
                free = false;
            }
        }
        for(int i = 0; i < memberCount; i++){
            if((_landMembers[i].xPos == xOpt)&&(_landMembers[i].yPos == yOpt)){
                free = false;
            }
        }
        if(free){
            int newX = adjacentTiles[i].xPos;
            int newY = adjacentTiles[i].yPos;
            _optionTiles[optionCount] = memberTiles[newX][newY];
            int set1 = adjacentOfType(_optionTiles[optionCount], 1);
            set1 += adjacentOfType(_optionTiles[optionCount], 2);
            int set2 = secondOrderOfType(_optionTiles[optionCount], 1);
            set2 += secondOrderOfType(_optionTiles[optionCount], 2);
            int weighted1 = set1 * 8;
            int weighted2 = set2 * 3;
            _optionTiles[optionCount].landWeight =  weighted1 + weighted2;
            optionCount++;
           
        }
    }
    printf("options updated\n");
}
void Landmass::placeFirstTile(Tile tileChoice, int texIndex){
    int xOrigin = tileChoice.xPos;
    int yOrigin = tileChoice.yPos;
    memberTiles[xOrigin][yOrigin].textureIndex = texIndex;
    memberTiles[xOrigin][yOrigin].isLand = true;
    _landMembers[memberCount] = memberTiles[xOrigin][yOrigin];
    updateOptions(xOrigin, yOrigin);
    printf("first tile placed\n");
}

int Landmass::adjacentOfType(Tile checkTile, int texIndex){
    int x = checkTile.xPos;
    int y = checkTile.yPos;
    int xUp = limitToZero(x + 1);
    int xDown = limitToZero(x - 1);
    int yUp = limitToZero(y + 1);
    int yDown = limitToZero(y - 1);
    int texture = texIndex;
    int typeCounter = 0;
    Tile adjacentTiles[4];
    adjacentTiles[0] = memberTiles[x][yDown]; //top
    adjacentTiles[1] = memberTiles[xUp][y]; //right
    adjacentTiles[2] = memberTiles[x][yUp]; //bottom
    adjacentTiles[3] = memberTiles[xDown][y]; //left
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
    int xUp = xTopLimit(x + 1);
    int xDown = limitToZero(x - 1);
    int yUp = yTopLimit(y + 1);
    int yDown = limitToZero(y - 1);
    Tile adjacentTiles[4];
    adjacentTiles[0] = memberTiles[x][yDown]; //top
    adjacentTiles[1] = memberTiles[xUp][y]; //right
    adjacentTiles[2] = memberTiles[x][yUp]; //bottom
    adjacentTiles[3] = memberTiles[xDown][y]; //left
    Tile secondOrderAdjacents[12];
    int xA = adjacentTiles[0].xPos;
    int yA = adjacentTiles[0].yPos;
    int xAUp = xTopLimit(xA + 1);
    int xADown = limitToZero(xA - 1);
    int yADown = limitToZero(yA - 1);
    secondOrderAdjacents[0] = memberTiles[xA][yADown]; //top.top
    secondOrderAdjacents[1] = memberTiles[xAUp][yA]; //top.right
    secondOrderAdjacents[2] = memberTiles[xADown][yA]; //top.left
    int xB = adjacentTiles[1].xPos;
    int yB = adjacentTiles[1].yPos;
    int xBUp = xTopLimit(xB + 1);
    int yBUp = yTopLimit(yB + 1);
    int yBDown = limitToZero(yB - 1);
    secondOrderAdjacents[3] = memberTiles[xB][yBDown]; //right.top
    secondOrderAdjacents[4] = memberTiles[xBUp][yB];// right.right
    secondOrderAdjacents[5] = memberTiles[xB][yBUp]; //right.bottom
    int xC = adjacentTiles[2].xPos;
    int yC = adjacentTiles[2].yPos;
    int xCUp = xTopLimit(xC + 1);
    int xCDown = limitToZero(xC - 1);
    int yCUp = yTopLimit(yC + 1);
    secondOrderAdjacents[6] = memberTiles[xCUp][yC];//bottom.right
    secondOrderAdjacents[7] = memberTiles[xC][yCUp]; //bottom.bottom
    secondOrderAdjacents[8] = memberTiles[xCDown][yC];
    int xD = adjacentTiles[3].xPos;
    int yD = adjacentTiles[3].yPos;
    int xDDown = limitToZero(xD - 1);
    int yDUp = yTopLimit(yD + 1);
    int yDDown = limitToZero(yD - 1);
    secondOrderAdjacents[9] = memberTiles[xD][yDDown];//left top
    secondOrderAdjacents[10] = memberTiles[xD][yDUp];//left bottom
    secondOrderAdjacents[11] = memberTiles[xDDown][yD];//left left
    int count = 0;
    for(int i = 0; i < 12; i++){
        if(secondOrderAdjacents[i].textureIndex != 0){
            secondOrderAdjacents[i].landWeight += 2;
        }
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

void Landmass::addWeights(){
    landWeightSum = 0;
    for(int i = 0; i < optionCount; i++){
        landWeightSum += _optionTiles[i].landWeight;
    }
}
int Landmass::randomIndex(int weightSum){
    printf("starting addTile\n");
    addWeights();
    bool weightedChoice = false;
    int indexChoice = 0;
    int proxySum = weightSum;
    int random = rand() % proxySum;
    for(int i = 0; i < optionCount; i++){
        if(random < _optionTiles[i].landWeight){
            indexChoice = random;
            weightedChoice = true;
        } else {
            random -= _optionTiles[i].landWeight;
        }
    }
    if(weightedChoice == false){
        indexChoice = rand() % optionCount;
    }
    return indexChoice;
}
void Landmass::addTile(){
    //printf("starting addTile\n");
    addWeights();
    int indexChoice = randomIndex(landWeightSum);
    int xChoice = _optionTiles[indexChoice].xPos;
    int yChoice = _optionTiles[indexChoice].yPos;
    bool chosen = false;
    int newRand;
    int failedLoops = 0;
    for(int i = 0; i < 1; i++){
        if(memberTiles[xChoice][yChoice].isLand){
            i--;
            printf("random choice invalid\n");
            printf("%d, %d\n", xChoice, yChoice);
            printf("optionCount: %d\n", optionCount);
            newRand = rand() % (failedLoops + 20);
            srand(newRand);
            indexChoice = 0;
            indexChoice = randomIndex(landWeightSum);
            printf("Chosen index: %d\n", indexChoice );
            xChoice = _optionTiles[indexChoice].xPos;
            yChoice = _optionTiles[indexChoice].yPos;
            addWeights();
            failedLoops++;
        } else {
            chosen = true;
        }
    }
    memberTiles[xChoice][yChoice].setIndex(1);
    map.assignTexture(memberTiles[xChoice][yChoice]);
    memberTiles[xChoice][yChoice].isLand = true;
    memberCount++;
    printf("Options: %d\n", optionCount);
    printf("Members: %d\n", memberCount);
    printf("addTile finished\n");
    updateOptions(xChoice, yChoice);
}

void Landmass::createLandmass(Tile firstTile, int firstTex, int numTiles){
    placeFirstTile(firstTile, firstTex);
    printf("Total tiles: %d\n", numTiles);
    for(int i = 1; i < numTiles; i++){
        addTile();
        printf("Tile number %d placed\n", i);
    }
    created = true;
    printf("landmass created\n");
}
